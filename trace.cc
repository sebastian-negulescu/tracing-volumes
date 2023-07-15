#include "trace.h"

Trace::Trace(Image & image, Sphere & scene): m_image(image), m_scene(scene) {}

glm::dvec3 Trace::trace_ray(Ray & ray) {
    glm::dvec3 colour;

    if (m_scene.intersect(ray)) {
        return glm::dvec3(1.0);
    }

    glm::vec3 normalized_direction = glm::normalize(glm::vec3(ray.get_direction()));
    double k = (normalized_direction.y + 1.0) / 2.0; 
    return (1.0 - k) * glm::dvec3(1.0, 0.6, 0.2) + k * glm::dvec3(0.3, 0.3, 1.0);
}

void Trace::cast_rays() {
    unsigned int width = m_image.get_width();
    unsigned int height = m_image.get_height();

    float aspect_ratio = float(width) / float(height);

    // camera
    float viewport_height = 2.0f;
    float viewport_width = aspect_ratio * viewport_height;
    float focal_length = 1.0f;

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
                glm::vec4(origin, 1.0f), 
                glm::vec4(lower_left_corner + u * horizontal + v * vertical - origin, 0.0f)
            );

            // cast and colour the ray
            glm::dvec3 colour = trace_ray(ray);
            m_image.colour_pixel(colour, x, y);
        }
    }
}
