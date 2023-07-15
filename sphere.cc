#include "sphere.h"

Sphere::Sphere(glm::vec4 position, float radius) : m_position(position), m_radius(radius) {}

bool Sphere::intersect(Ray & ray) {
    glm::vec4 center_direction = ray.get_origin() - m_position;

    float a = glm::dot(ray.get_direction(), ray.get_direction());
    float half_b = glm::dot(center_direction, ray.get_direction());
    float c = glm::dot(center_direction, center_direction) - m_radius * m_radius;

    float descriminant = half_b * half_b - a * c; // doesn't matter that it isn't multiplied by 4, 4 factors out and descriminant being less than 0 is dependant on half_b, a, and c
    if (descriminant < 0) {
        return false;
    }

    float sqrt_descriminant = glm::sqrt(descriminant);
    float t = (-half_b - sqrt_descriminant) / a;
    if (t <= 0.0f) {
        t = (-half_b + sqrt_descriminant) / a;
        if (t <= 0.0f) {
            return false;
        }
    }

    return true;
}
