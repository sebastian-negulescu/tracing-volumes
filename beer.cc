#include "beer.h"

Beer::Beer(glm::dvec3 absorptivity, float concentration)
    : m_absorptivity(absorptivity), m_concentration(concentration) {}

glm::dvec3 Beer::effect(Ray & ray, Object & scene, Light & light, hit & info, glm::dvec3 background) {
    if (!info.exit) {
        return background;
    }
    glm::vec4 entry_point = ray.get_origin();
    glm::vec4 exit_point = info.point;

    float length = glm::length(exit_point - entry_point);
    glm::dvec3 absorbance = double(length) * double(m_concentration) * m_absorptivity;
    glm::dvec3 absorbed_light = glm::exp(-absorbance);

    return absorbed_light * background;
}
