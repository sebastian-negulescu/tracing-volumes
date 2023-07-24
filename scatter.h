#include <glm/glm.hpp>

#include "light.h"
#include "object.h"
#include "material.h"
#include "phase.h"
#include "perlin.h"

#ifndef __SCATTER_H__
#define __SCATTER_H__

class Scatter : public Material {
    Phase & m_phase;
    Perlin & m_perlin;
    float m_absorbance;
    float m_scatter;
    float m_density;
    float m_termination;

public:
    Scatter(Phase & phase, Perlin & perlin, float absorbance, float scatter, float density);
    glm::vec3 effect(Ray & ray, Object & scene, Light & light, hit & info, glm::vec3 background) override;
};

#endif
