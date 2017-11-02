#ifndef __RENDERER_H
#define __RENDERER_H

#include "world.h"
#include "camera.h"

#define EPSILON 1e-5

class Renderer {
private:
	World *world;
	Camera *camera;
    glm::vec3 *pixmap;
	glm::vec3 shade(int i, int j);
    glm::vec3 raycolor(Ray ray, double t0, double t1);

public:
	Renderer(World *world, Camera *camera) : world(world),
                                             camera(camera)
    {
        pixmap = new glm::vec3 [camera->width * camera->height];
    }
    ~Renderer() { delete pixmap; }
	bool renderLoop();
};
#endif
