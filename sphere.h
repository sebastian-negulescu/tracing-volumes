#include <glm/glm.hpp>

#include "object.h"
#include "ray.h"
#include "material.h"

#ifndef __SPHERE_H__
#define __SPHERE_H__

class Sphere : public Object {
    glm::vec4 m_position;
    float m_radius;

public:
    Material & m_material;

    Sphere(glm::vec4 position, float radius, Material & material);
    bool intersect(Ray & ray, float t_min, float t_max, hit & info) override;
};

#endif
