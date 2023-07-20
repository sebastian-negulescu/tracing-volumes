#include <glm/glm.hpp>

#include "image.h"
#include "sphere.h"
#include "ray.h"
#include "light.h"

#ifndef __TRACE_H__
#define __TRACE_H__

class Trace {
    Image & m_image;
    Sphere & m_scene; // considered scene for now since we're only going to have one
    Light & m_light;

public:
    Trace(Image & image, Sphere & scene, Light & light);

    glm::vec3 trace_ray(Ray & ray, unsigned int bounces);
    void cast_rays();
};

#endif
