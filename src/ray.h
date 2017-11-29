#ifndef __RAY_H
#define __RAY_H

#include <glm/vec3.hpp>

class Ray
{
public:
    glm::vec3 origin;
    glm::vec3 dir; ///< Direction vector
    float delT; ///< Time interval for Motion Blur
    Ray(const glm::vec3 &o, const glm::vec3 &d, float delT = 0) : origin(o), dir(d), delT(delT)
    {}

};

#endif
