#include <glm/glm.hpp>

#include "material.h"
#include "object.h"
#include "light.h"

#ifndef __BEER_H__
#define __BEER_H__

class Beer : public Material {
    glm::vec3 m_absorptivity;
    float m_concentration;

public:
    Beer(glm::vec3 absorptivity, float concentration);
    glm::vec3 effect(Ray & ray, Object & scene, Light & light, hit & info, glm::vec3 background) override;
};

#endif
