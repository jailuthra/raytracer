#ifndef __SPHERE_H_
#define __SPHERE_H_

#include "surface.h"
#include <glm/vec3.hpp>

class Sphere : public Surface {

public:
    glm::vec3 pos; ///< center
    double radius;
    glm::vec3 velocity; ///< for motion blur
    glm::vec3 movedPos; ///< new pos after moving

    Sphere(glm::vec3 _pos, double _rad, Material* mat, glm::vec3 _vel = glm::vec3(0.0f)):
        Surface(mat), pos(_pos), radius(_rad), velocity(_vel)
    {}

    virtual bool hit(const Ray &ray, double t0, double t1, HitRec &hr);
    virtual glm::vec3 getNormal(glm::vec3 hitpoint) const;
};

#endif
