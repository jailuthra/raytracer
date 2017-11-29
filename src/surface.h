#ifndef __SURFACE_H
#define __SURFACE_H

#include "ray.h"
#include "material.h"

class HitRec;

class Surface {
public:
    Material *mat;
    Surface(Material *mat) : mat(mat)
    {}
    virtual bool hit(const Ray &ray, double t0, double t1, HitRec &hr) = 0;
    virtual glm::vec3 getNormal(glm::vec3 hitpoint) const = 0;
    virtual bool isMoving() { return false; };
};

#endif
