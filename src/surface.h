#ifndef __SURFACE_H
#define __SURFACE_H

#include "ray.h"

class Surface 
{
public:
    Material *mat;
    Surface(Material *mat) : material(mat)
    {}
    virtual bool hit(const Ray &ray, double t0, double t1, HitRec &hr) = 0;
};

#endif
