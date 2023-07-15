#include <glm/glm.hpp>

#include "ray.h"

#ifndef __SPHERE_H__
#define __SPHERE_H__

class Sphere {
    glm::vec4 m_position;
    float m_radius;

public:
    Sphere(glm::vec4 position, float radius);
    bool intersect(Ray & ray);
};

#endif
