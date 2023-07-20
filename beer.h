#include <glm/glm.hpp>

#include "material.h"
#include "object.h"
#include "light.h"

#ifndef __BEER_H__
#define __BEER_H__

class Beer : public Material {
public:
    glm::dvec3 m_absorptivity;
    float m_concentration;
    Beer(glm::dvec3 absorptivity, float concentration);
    glm::dvec3 effect(Ray & ray, Object & scene, Light & light, hit & info, glm::dvec3 background) override;
};

#endif
