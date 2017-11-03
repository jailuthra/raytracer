#include "triangle.h"
#include "hitrec.h"
#include <glm/glm.hpp>
#include <iostream>

bool Triangle::hit(const Ray &ray, double t0, double t1, HitRec &hr){
    bool stat = false;

    glm::vec3 dir = ray.dir;
    glm::vec3 origin = ray.origin;

    double det_A = glm::determinant(glm::mat3(v1 - v2, v1 - v3, dir));
    double t = glm::determinant(glm::mat3(v1 - v2, v1 - v3, v1 - origin)) / det_A;

    if(t > t1 || t < t0)
        return false;

    double gamma = glm::determinant(glm::mat3(v1 - v2, v1 - origin, dir)) / det_A;

    if(gamma < 0 || gamma > 1)
        return false;
    
    double beta = glm::determinant(glm::mat3(v1 - origin, v1 - v3, dir)) / det_A;

    if(beta < 0 || beta > (1 - gamma))
        return false;

    hr.hit = true;
    hr.t = t;
    hr.s = this;

    return true;
}

glm::vec3 Triangle::getNormal(glm::vec3 hitpoint) const{    
    return normal;
}
