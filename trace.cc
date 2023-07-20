#include <limits>
#include <iostream>
#include <glm/ext.hpp>
#include "trace.h"
#include "object.h"

Trace::Trace(Image & image, Sphere & scene, Light & light): m_image(image), m_scene(scene), m_light(light) {}

glm::vec3 Trace::trace_ray(Ray & ray, unsigned int bounces) {
    hit info;

    if (bounces == 0) {
        return glm::vec3(0.0f);
    }

    // std::cerr << ray.get_origin().z << std::endl;
    if (m_scene.intersect(ray, 0.001f, std::numeric_limits<float>::infinity(), info)) {
        Ray new_ray(info.point, ray.get_direction()); // same direction since we are going through material
        return m_scene.m_material.effect(ray, m_scene, m_light, info, trace_ray(new_ray, bounces - 1));
    }

    glm::vec3 normalized_direction = glm::normalize(glm::vec3(ray.get_direction()));
    double k = (normalized_direction.y + 1.0f) / 2.0f; 
    return (1.0f - k) * glm::dvec3(1.0f, 0.6f, 0.2f) + k * glm::dvec3(0.3f, 0.3f, 1.0f);
}

void Trace::cast_rays() {
    unsigned int width = m_image.get_width();
    unsigned int height = m_image.get_height();

    float aspect_ratio = float(width) / float(height);

    // camera
    float viewport_height = 2.0f;
    float viewport_width = aspect_ratio * viewport_height;
    float fov = 45.0f;
    float focal_length = glm::tan(glm::radians(fov));

    glm::vec3 origin(0.0f);
    glm::vec3 horizontal(viewport_width, 0.0f, 0.0f);
    glm::vec3 vertical(0.0f, viewport_height, 0.0f);
    glm::vec3 lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - glm::vec3(0.0f, 0.0f, focal_length);

    // render
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            // convert to u,v coords in [0,1]
            float u = float(x) / float(width - 1);
            float v = float(y) / float(height - 1);

            // construct ray
            Ray ray(
                glm::vec4(origin, 1.0f), // point has 1 appended to it
                glm::vec4(glm::normalize(lower_left_corner + u * horizontal + v * vertical - origin), 0.0f) // vector has 0 appended to it
            );

            // cast and colour the ray
            glm::vec3 colour = trace_ray(ray, 3);
            m_image.colour_pixel(colour, x, y);
        }
    }

    /*
    Ray debug(
        glm::vec4(origin, 1.0f),
        glm::vec4(lower_left_corner + 0.5f * horizontal + 0.5f * vertical - origin, 0.0f)
    );
    std::cerr << "tracing ray" << std::endl;
    trace_ray(debug, 3);
    */
}
