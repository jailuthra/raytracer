#include "triangle.h"
#include "hitrec.h"
#include <glm/glm.hpp>
#include <iostream>

bool Triangle::hit(const Ray &ray, double t0, double t1, HitRec &hr){
    bool stat = false;

    glm::vec3 dir = ray.dir;
    glm::vec3 origin = ray.origin;

    glm::mat3 A_mat = glm::mat3(v1 - v2, v1- v3, dir);
    glm::mat3 beta_mat = glm::mat3(v1 - origin, v1 - v3, dir);
    glm::mat3 gamma_mat = glm::mat3(v1 - v2, v1 - origin, dir);
    glm::mat3 t_mat = glm::mat3(v1 - v2, v1 - v3, v1 - origin);

    double det_A = glm::determinant(A_mat);
    double beta = glm::determinant(beta_mat) / det_A;
    double gamma = glm::determinant(gamma_mat) / det_A;
    double t = glm::determinant(t_mat) / det_A;

    if(beta > 0 && gamma > 0){
        if(beta + gamma < 1){

            if(t < t1 && t > t0){
                hr.hit = true;
                hr.t = t;
                hr.s = this;    
                stat = true;
            }
        }
    }

    return stat;
}

glm::vec3 Triangle::getNormal(glm::vec3 hitpoint) const{
    glm::vec3 e1 = v2 - v1;
    glm::vec3 e2 = v1 - v3;
    glm::vec3 normal = glm::normalize(glm::cross(e1, e2));
    
    return normal;
}
