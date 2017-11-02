#include "world.cpp"

bool World::hit(const Ray &ray, double t0, double t1, HitRec &hr)
{
    bool hit = false;
    for (Surface *s: surfaces) {
        if (s->hit(ray, t0, t1, hr)) {
            hit = true;
            t1 = hr.t;
        }
    }
    return hit;
}
