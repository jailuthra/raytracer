#ifndef __RENDERER_H
#define __RENDERER_H

#include "world.h"
#include "camera.h"
#include "fovea.h"
#include <cstdlib>

#define EPSILON 1e-3

class Renderer {
private:
	World *world;
	Camera *camera;
    Fovea *fovea;  ///< Eye tracking for foveated RT
    bool *shademap; ///< Is pixel shaded in foveated RT
    glm::vec3 *pixmap; ///< Pixel map for output PPM image
	glm::vec3 shade(int i, int j); ///< Shade pixel
    glm::vec3 raycolor(Ray ray, double t0, double t1); ///< Raytracer recursive call
    void shader(); ///< Shade all pixels and update pixmap
    const int MAX_DEPTH = 6; ///< Max recursion depth
    /** Random float from 0 to 1 (inclusive). */
    float eps() { return static_cast <float> (rand())
                       / static_cast <float> (RAND_MAX);}
    bool antialiase; ///< Boolean to turn AA off/on
public:
	Renderer(World *world, Camera *camera, Fovea *fovea, bool aa = false)
                                           : world(world),
                                             camera(camera),
                                             fovea(fovea),
                                             antialiase(aa)
    {
        pixmap = new glm::vec3 [camera->width * camera->height];
        shademap = new bool [camera->width * camera->height];
    }
    ~Renderer()
    {
        delete pixmap;
        delete shademap;
    }
    glm::vec3 * getPixMap() { return pixmap; };
    /** Output pixmap to a PPM file. */
	void render(const char *fn);
};
#endif
