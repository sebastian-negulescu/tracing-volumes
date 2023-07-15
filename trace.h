#include <glm/glm.hpp>

#include "image.h"
#include "sphere.h"
#include "ray.h"

#ifndef __TRACE_H__
#define __TRACE_H__

class Trace {
    Image & m_image;
    Sphere & m_scene; // considered scene for now since we're only going to have one

public:
    Trace(Image & image, Sphere & scene);

    glm::dvec3 trace_ray(Ray & ray);
    void cast_rays();
};

#endif
