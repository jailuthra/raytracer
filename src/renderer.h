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
    glm::vec3 *pixmap; ///< Pixel map for output PPM image
	glm::vec3 shade(int i, int j); ///< Shade pixel
    glm::vec3 raycolor(Ray ray, double t0, double t1); ///< Raytracer recursive call
    const int MAX_DEPTH = 6; ///< Max recursion depth
    /** Random float from 0 to 1 (inclusive). */
    float eps() { return static_cast <float> (rand())
                       / static_cast <float> (RAND_MAX);}
    bool antialiase; ///< Boolean to turn AA off/on
public:
	Renderer(World *world, Camera *camera, bool aa = false)
                                           : world(world),
                                             camera(camera),
                                             antialiase(aa)
    {
        pixmap = new glm::vec3 [camera->width * camera->height];
    }
    ~Renderer() { delete pixmap; }
    /** Output pixmap to a PPM file. */
	void render(const char *fn);
};
#endif
