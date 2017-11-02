#ifndef __WORLD_H
#define __WORLD_H

#include <vector>
#include <glm/vec3.hpp>

#include "surface.h"
#include "lightsrc.h"

class World {
public:
    std::vector<Surface*> surfaces;
    std::vector<LightSrc*> sources;
    glm::vec3 bgcol;
    void addObject(Surface *s) { surfaces.push_back(s); }
    void addSource(LightSrc *s) { sources.push_back(s); }
    bool hit(const Ray &ray, double t0, double t1, HitRec &hr);
};

#endif
