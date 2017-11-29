#ifndef __RENDERER_H
#define __RENDERER_H

#include "world.h"
#include "camera.h"
#include <cstdlib>

#define EPSILON 1e-3

class Renderer {
private:
	World *world;
	Camera *camera;
    glm::vec3 *pixmap;
	glm::vec3 shade(int i, int j);
    glm::vec3 raycolor(Ray ray, double t0, double t1);
    const int MAX_DEPTH = 6;
    float eps() { return static_cast <float> (rand())
                       / static_cast <float> (RAND_MAX);}
    bool antialiase;
public:
	Renderer(World *world, Camera *camera, bool aa = false)
                                           : world(world),
                                             camera(camera),
                                             antialiase(aa)
    {
        // srand (static_cast <unsigned> (time(0)));
        pixmap = new glm::vec3 [camera->width * camera->height];
    }
    ~Renderer() { delete pixmap; }
	void render(const char *fn);
};
#endif
