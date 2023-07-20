#include <glm/glm.hpp>
#include <vector>

#include "ray.h"

#ifndef __OBJECT_H__
#define __OBJECT_H__

struct hit {
    glm::vec4 point;
    glm::vec3 normal;
    float t;
    bool exit = false;
};

class Object {
public:
    virtual bool intersect(Ray & ray, float t_min, float t_max, hit & info) = 0;
};

#endif
