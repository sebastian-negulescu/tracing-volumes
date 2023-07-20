#include <limits>
#include <iostream>
#include <math.h>
#include "scatter.h"

Scatter::Scatter(float absorbance, float scatter)
    : m_absorbance(absorbance), m_scatter(scatter) {}

float Scatter::simple_phase() {
    return 1 / (4 * M_PI);
}

float Scatter::hg_phase(glm::vec4 & light, glm::vec4 & eye, float g) {
    float denom = 1 + g * g - 2 * g * glm::dot(eye, light);
    return simple_phase() * (1 - g * g) / (denom * glm::sqrt(denom));
}

glm::vec3 Scatter::effect(Ray & ray, Object & scene, Light & light, hit & info, glm::vec3 background) {
    if (!info.exit) {
        return background;
    }
    glm::vec4 entry_point = ray.get_origin();
    glm::vec4 exit_point = info.point;

    /*
    std::cerr << "POINT INFO" << std::endl;
    std::cerr << glm::length(entry_point - glm::vec4(0.0f, 0.0f, -10.0f, 1.0f)) << std::endl; 
    std::cerr << glm::length(exit_point - glm::vec4(0.0f, 0.0f, -10.0f, 1.0f)) << std::endl;
    */

    float march_t = 0;
    float delta = 0.1;
    float density = 0.25;

    float acc_transmittance = 1.0;
    glm::vec3 acc_colour(0.0);

    glm::vec4 eye_dir = glm::normalize(ray.get_direction());

    bool inside = true;
    while (inside) {
        glm::vec4 march_point = entry_point + (march_t + (delta / 2)) * ray.get_direction();
        Ray light_ray(march_point, glm::normalize(light.get_position() - march_point));

        double attenuation = glm::exp(-delta * density * (m_absorbance + m_scatter));
        acc_transmittance *= attenuation;

        hit light_info;
        if (scene.intersect(light_ray, 0.0001, std::numeric_limits<float>::infinity(), light_info) 
            && light_info.exit) {
            float light_length = glm::length(light_info.point - march_point);
            float light_attenuation = glm::exp(-light_length * density * (m_absorbance + m_scatter));
            glm::vec4 light_dir = light_ray.get_direction();

            acc_colour += acc_transmittance * light.get_colour() * light_attenuation 
                * density * m_scatter * hg_phase(light_dir, eye_dir, 0.8) * delta;
        }

        march_t += delta;
        if (march_t >= info.t) {
            inside = false;
        }
    }

    return acc_transmittance * background + acc_colour;
}
