#ifndef __RAY_H
#define __RAY_H

#include <glm/vec3.hpp>

class Ray
{
public:
    glm::vec3 origin;
    glm::vec3 dir;
    Ray(const glm::vec3 &o, const glm::vec3 &d) : origin(o), dir(d)
    {}
};

#endif
