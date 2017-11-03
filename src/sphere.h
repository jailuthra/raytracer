#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "surface.h"
#include <glm/vec3.hpp>

class Sphere : public Surface {

public:
    glm::vec3 pos;
    double radius;

    Sphere(glm::vec3 _pos, double _rad, Material* mat):
        Surface(mat), pos(_pos), radius(_rad)
    {}

    virtual bool hit(const Ray &ray, double t0, double t1, HitRec &hr);
    virtual glm::vec3 getNormal(glm::vec3 hitpoint) const;
};

#endif