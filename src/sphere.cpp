#include "sphere.h"
#include "hitrec.h"
#include <glm/glm.hpp>

bool Sphere::hit(const Ray &ray, double t0, double t1, HitRec &hr) {

    glm::vec3 centerVec = ray.origin - pos;
    double A = 1.0; // glm::dot(ray.dir, ray.dir)
    double B = 2 * glm::dot(ray.dir, centerVec);
    double C = glm::dot(centerVec, centerVec) - radius*radius;
    double Discriminant = B*B - 4.0*A*C;

    bool stat = false;

    if(Discriminant == 0.0){
        double t;
        t = -B / (2.0 * A);

        if(t < t1 && t > t0){
            hr.hit = true;
            hr.t = t;
            hr.s = this;
        }
        stat = true;
    }

    else if(Discriminant > 0.0){
        double D = sqrt(Discriminant);
        double r0 = (-B + D) / (2.0 * A);
        double r1 = (-B - D) / (2.0 * A);

        double t = r0 < r1 ? r0 : r1;
        
        if(t < t1 && t > t0){
            hr.hit = true;
            hr.t = t;
            hr.s = this;
            stat = true;
        }
    }

    return stat;
}

glm::vec3 Sphere::getNormal(glm::vec3 hitpoint) const {
    glm::vec3 normal = glm::normalize(hitpoint - pos);
    return normal;
}
