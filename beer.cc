#include "beer.h"

Beer::Beer(glm::vec3 absorptivity, float concentration)
    : m_absorptivity(absorptivity), m_concentration(concentration) {}

glm::vec3 Beer::effect(Ray & ray, Object & scene, Light & light, hit & info, glm::vec3 background) {
    if (!info.exit) {
        return background;
    }
    glm::vec4 entry_point = ray.get_origin();
    glm::vec4 exit_point = info.point;

    float length = glm::length(exit_point - entry_point);
    glm::vec3 absorbance = length * m_concentration * m_absorptivity;
    glm::vec3 absorbed_light = glm::exp(-absorbance);

    return absorbed_light * background;
}
