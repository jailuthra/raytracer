#ifndef __TRIANGLE_H
#define __TRIANGLE_H
    
#include "surface.h"
#include <glm/vec3.hpp>

class Triangle : public Surface {
public: 
    glm::vec3 v1, v2, v3; 

    Triangle(glm::vec3 _v1, glm::vec3 _v2, glm::vec3 _v3, Material *mat):
        Surface(mat), v1(_v1), v2(_v2), v3(_v3)
    {}

    virtual bool hit(const Ray &ray, double t0, double t1, HitRec &hr);
    virtual glm::vec3 getNormal(glm::vec3 hitpoint) const;
};

#endif