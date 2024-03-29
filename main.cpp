#include "src/renderer.h"
#include "src/world.h"
#include "src/camera.h"
#include "src/sphere.h"
#include "src/triangle.h"
#include "src/fovea.h"
#include <glm/vec3.hpp>

int main(int argc, char **argv)
{
    int screen_width = 800, screen_height = 800;
    // Fovea
    glm::vec2 eye_pos = glm::vec2(0.5, 0.5);
    Fovea *fovea = new Fovea(eye_pos, 0.1, 0.3, 0.1);

    // Camera
    glm::vec3 camera_position(0, 10, 20);
    glm::vec3 camera_target(0, 0, 0); //Looking down -Z axis
    glm::vec3 camera_up(0, 1, 0);
    float camera_fovy =  45;
    Camera *camera = new Camera(camera_position, camera_target, camera_up, camera_fovy, screen_width, screen_height);

    // World
    World *world = new World;
    world->bgcol = glm::vec3(0.8f, 0.8f, 0.8f);

    // Objects
    Material *m = new Material;
    m->color = glm::vec3(1.0, 1.0, 1.0);
    m->km = 0.0;
    m->ks = 0.3;
    m->ka = 0.1;
    m->kd = 0.6;
    m->a = 0.05;
    m->kt = 0.6;
    m->eta = 1.15;
    
    Surface *sphere = new Sphere(glm::vec3(2, 1, 5), 3, m);
    world->addObject(sphere);

    Material *m2 = new Material;
    m2->color = glm::vec3(0.8, 0.1, 0.2);
    m2->km = 0;
    m2->ks = 0.3;
    m2->ka = 0.3;
    m2->kd = 0.4;
    m2->a = 0;
    m2->kt = 0;
    m2->eta = 1.0;

    Surface *sphere2 = new Sphere(glm::vec3(-4, 2, -3), 4, m2, glm::vec3(-0.5, 0, 0));
    world->addObject(sphere2);

    Material *m3 = new Material;
    m3->color = glm::vec3(0.1, 0.5, 0.6);
    m3->km = 0.2;
    m3->ks = 0.3;
    m3->ka = 0.3;
    m3->kd = 0.4;
    m3->a = 0.05;
    m3->kt = 0;
    m3->eta = 1.00;

    Surface *sphere3 = new Sphere(glm::vec3(5, 3, -2), 5, m3);
    world->addObject(sphere3);

    // Floor 
    Material *fm = new Material;
    fm->color = glm::vec3(0.2, 0.2, 0.2);
    fm->km = 0.3;
    fm->ks = 0.2;
    fm->ka = 0.1;
    fm->kd = 0.7;
    fm->a = 0.05;
    Surface *floorTriangle1 = new Triangle(glm::vec3(-200,-2,800),
                                  glm::vec3(-200,-2,-800),
                                  glm::vec3(200,-2,800), fm);

    Surface *floorTriangle2 = new Triangle(glm::vec3(200,-2,800),
                                  glm::vec3(-200,-2,-800),
                                  glm::vec3(200,-2,-800), fm);

    world->addObject(floorTriangle1);
    world->addObject(floorTriangle2);

    /* LIGHT SOURCES */

    LightSrc *light = new LightSrc;
    light->pos = glm::vec3(6, 8, 10);
    light->intensity = glm::vec3(1, 1, 1);
    light->a = glm::vec3(2, 0, -2);
    light->b = glm::vec3(0, -2, 0);
    world->addSource(light);

    LightSrc *light2 = new LightSrc;
    light2->pos = glm::vec3(-8,6,-8);
    light2->intensity = glm::vec3(1,1,1);
    light2->a = glm::vec3(2, 0, 2);
    light2->b = glm::vec3(0, 2, 0);
    world->addSource(light2);

    /* Render */
    Renderer *engine = new Renderer(world, camera, fovea, true);
    char *fn = (char *) "out.ppm";
    if (argc > 1) {
        fn = argv[1];     
    }
    engine->render(fn);

    return 0;
}
