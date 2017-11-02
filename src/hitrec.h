#ifndef __HITREC_H
#define __HITREC_H

#include "surface.h"
#include <glm/vec3.hpp>

class HitRec {
    bool hit; ///> Did ray it anything yet
    double t; ///> Ray parameter of hit point
    Surface *s; ///> Closest surface it hit
    glm::vec3 normal; ///> Object normal at hit pt.
    Ray *r; ///> Ray (optional)
    glm::vec3 p; ///> Hit point (optional)
};

#endif
