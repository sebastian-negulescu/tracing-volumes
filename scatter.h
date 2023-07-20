#include <glm/glm.hpp>

#include "light.h"
#include "object.h"
#include "material.h"

#ifndef __SCATTER_H__
#define __SCATTER_H__

class Scatter : public Material {
    float m_absorbance;
    float m_scatter;

    float simple_phase();
    float hg_phase(glm::vec4 & light, glm::vec4 & eye, float g);

public:
    Scatter(float absorbance, float scatter);
    glm::vec3 effect(Ray & ray, Object & scene, Light & light, hit & info, glm::vec3 background) override;
};

#endif
