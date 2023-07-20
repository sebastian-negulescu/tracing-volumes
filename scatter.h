#include <glm/glm.hpp>

#include "light.h"
#include "object.h"
#include "material.h"

#ifndef __SCATTER_H__
#define __SCATTER_H__

class Scatter : public Material {
public:
    float m_absorbance;
    float m_scatter;
    Scatter(float absorbance, float scatter);
    glm::dvec3 effect(Ray & ray, Object & scene, Light & light, hit & info, glm::dvec3 background) override;
};

#endif
