#include <limits>
#include <iostream>
#include "scatter.h"

Scatter::Scatter(float absorbance, float scatter)
    : m_absorbance(absorbance), m_scatter(scatter) {}

glm::dvec3 Scatter::effect(Ray & ray, Object & scene, Light & light, hit & info, glm::dvec3 background) {
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
    float delta = 0.01;

    double acc_transmittance = 1.0;
    glm::dvec3 acc_colour(0.0);

    bool inside = true;
    while (inside) {
        glm::vec4 march_point = entry_point + (march_t + (delta / 2)) * ray.get_direction();
        Ray light_ray(march_point, (light.get_position() - march_point));

        double attenuation = glm::exp(-delta * (m_absorbance + m_scatter));

        acc_transmittance *= attenuation;

        hit light_info;
        if (scene.intersect(light_ray, 0.0001, std::numeric_limits<float>::infinity(), light_info) && light_info.exit) {
            float light_length = glm::length(light_info.point - march_point);
            double light_attenuation = glm::exp(-light_length * (m_absorbance + m_scatter));
            acc_colour += acc_transmittance * light.get_colour() * light_attenuation * double(m_scatter) * double(delta); 
        }

        march_t += delta;
        if (march_t >= info.t) {
            inside = false;
        }
    }

    return acc_transmittance * background + acc_colour;
}
