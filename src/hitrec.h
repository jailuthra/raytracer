#ifndef __HITREC_H
#define __HITREC_H

#include "surface.h"
#include <glm/vec3.hpp>

class HitRec {
public:
    bool hit = false; ///> Did ray hit anything yet
    float t = -10; ///> Ray parameter of hit point
    Surface *s = NULL; ///> Closest surface it hit
    glm::vec3 normal = glm::vec3(0); ///> Object normal at hit pt.
    Ray *r = NULL; ///> Ray
    glm::vec3 p; ///> Hit point
    glm::vec3 getHitPoint() { return r->origin + t * r->dir; }
};

#endif
