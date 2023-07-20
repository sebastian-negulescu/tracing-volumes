#include "sphere.h"

Sphere::Sphere(glm::vec4 position, float radius, Material & material) 
    : m_position(position), m_radius(radius), m_material(material) {}

bool Sphere::intersect(Ray & ray, float t_min, float t_max, hit & info) {
    glm::vec3 center_direction(ray.get_origin() - m_position);
    glm::vec3 ray_direction(ray.get_direction());
    glm::vec3 ray_origin(ray.get_origin());

    float a = glm::dot(ray_direction, ray_direction);
    float half_b = glm::dot(center_direction, ray_direction);
    float c = glm::dot(center_direction, center_direction) - m_radius * m_radius;

    float descriminant = half_b * half_b - a * c; // doesn't matter that it isn't multiplied by 4, 4 factors out and descriminant being less than 0 is dependant on half_b, a, and c
    if (descriminant < 0) {
        return false;
    }

    float sqrt_descriminant = glm::sqrt(descriminant);
    float t = (-half_b - sqrt_descriminant) / a;
    if (t <= 0.0f || t <= t_min) {
        t = (-half_b + sqrt_descriminant) / a;
        if (t <= 0.0f || t <= t_min) {
            return false;
        }
        info.exit = true;
    } 

    info.t = t;
    info.point = ray.get_origin() + info.t * ray.get_direction();
    info.normal = glm::vec3(info.point) - glm::vec3(m_position);
    return true;
}
