#include <glm/glm.hpp>

#include "ray.h"
#include "light.h"
#include "object.h"

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

class Material {
public:
    virtual glm::dvec3 effect(Ray & ray, Object & scene, Light & light, hit & info, glm::dvec3 background) = 0;
};

#endif
