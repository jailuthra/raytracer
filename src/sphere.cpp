#include "sphere.h"
#include "hitrec.h"
#include <glm/glm.hpp>

bool Sphere::hit(const Ray &ray, double t0, double t1, HitRec &hr)
{
    if (this->velocity != glm::vec3(0.0f)) {
        movedPos = pos + ray.delT * velocity;
    } else {
        movedPos = pos;
    }

    glm::vec3 centerVec = ray.origin - movedPos;
    double A = glm::dot(ray.dir, ray.dir);
    double B = 2 * glm::dot(ray.dir, centerVec);
    double C = glm::dot(centerVec, centerVec) - radius*radius;
    double Discriminant = B*B - 4.0*A*C;

    bool ret = false;

    if(Discriminant == 0.0){
        double t;
        t = -B / (2.0 * A);

        if(t < t1 && t > t0){
            hr.hit = true;
            hr.t = t;
            hr.s = this;
        }
        ret = true;
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
            ret = true;
        }
    }

    return ret;
}

glm::vec3 Sphere::getNormal(glm::vec3 hitpoint) const {
    glm::vec3 normal = glm::normalize(hitpoint - movedPos);
    return normal;
}
