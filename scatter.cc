#include <limits>
#include <iostream>
#include <random>
#include "scatter.h"

Scatter::Scatter(Phase & phase, Perlin & perlin, float absorbance, float scatter, float density)
    : m_phase(phase), m_perlin(perlin), m_absorbance(absorbance), m_scatter(scatter), m_density(density), m_termination(scatter + density) {}

glm::vec3 Scatter::effect(Ray & ray, Object & scene, Light & light, hit & info, glm::vec3 background) {
    if (!info.exit) {
        return background;
    }
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0.0f,1.0f);

    glm::vec4 entry_point = ray.get_origin();
    glm::vec4 exit_point = info.point;

    float march_t = 0.0f;
    float delta = 0.1f;

    float acc_transparancy = 1.0f;
    glm::vec3 acc_colour(0.0f);

    glm::vec4 eye_dir = glm::normalize(ray.get_direction());

    while (true) {
        if (march_t >= info.t) {
            break;
        }

        glm::vec4 march_point = entry_point + (march_t + (delta * distribution(generator))) * ray.get_direction();
        // float density = (m_perlin.noise(march_point) + 1.0f) / 2.0f;
        float density = m_perlin.noise(march_point);
        if (density <= 0.0f) density *= -1.0f;

        double volume_attenuation = glm::exp(-delta * density * (m_termination));
        acc_transparancy *= volume_attenuation;

        Ray light_ray(march_point, glm::normalize(light.get_position() - march_point));
        hit light_info;
        if (scene.intersect(light_ray, 0.0001f, std::numeric_limits<float>::infinity(), light_info) && light_info.exit) {
            float light_t = 0.0f;
            float light_exp = 0.0f;

            while (true) {
                if (light_t >= light_info.t) {
                    break;
                }

                glm::vec4 light_point = march_point + (light_t * delta / 2.0f) * light_ray.get_direction();
                float light_density = (m_perlin.noise(light_point) + 1.0f) / 2.0f;
                light_exp += -delta * light_density * (m_termination);

                light_t += delta;
            }
            glm::vec4 light_dir = light_ray.get_direction();

            float acc_light_transparency = glm::exp(light_exp);
            acc_colour += acc_transparancy * light.get_colour() * acc_light_transparency * density * m_scatter * m_phase.evaluate(light_dir, eye_dir) * delta;
        }

        march_t += delta;
    }

    return acc_transparancy * background + acc_colour;
}
