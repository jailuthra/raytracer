#include "src/renderer.h"
#include "src/world.h"
#include "src/camera.h"
#include "src/sphere.h"
#include "src/triangle.h"
#include "src/quad.h"
#include <glm/vec3.hpp>

int main(int argc, char **argv)
{
    int screen_width = 800, screen_height = 600;

    // Camera
    glm::vec3 camera_position(0, 10, 20);
    glm::vec3 camera_target(0, 0, 0); //Looking down -Z axis
    glm::vec3 camera_up(0, 1, 0);
    float camera_fovy =  45;
    Camera *camera = new Camera(camera_position, camera_target, camera_up, camera_fovy, screen_width, screen_height);

    // World
    World *world = new World;
    world->bgcol = glm::vec3(0.1f, 0.3f, 0.6f);
    
    Material *m = new Material;
    m->color = glm::vec3(0.2, 0.8, 0.0);
    m->km = 0;
    m->ks = 0.3;
    m->ka = 0.1;
    m->kd = 0.6;
    
    Surface *sphere = new Sphere(glm::vec3(0.5f, 0.1, 0), 1.5, m);
    //Object *triangle = new Triangle(Vector3D(2,0,0), Vector3D(-1,0,4), Vector3D(0,3,0), m);
    world->addObject(sphere);
    //world->addObject(triangle);

    Material *m2 = new Material;
    m2->color = glm::vec3(0.8, 0.1, 0.2);
    m2->km = 0;
    m2->ks = 0.4;
    m2->ka = 0.2;
    m2->kd = 0.6;

    Surface *sphere2 = new Sphere(glm::vec3(-2, 0.1, 2), 0.5, m2);
    world->addObject(sphere2);

    // Floor 
    Material *fm = new Material;
    fm->color = glm::vec3(0.2, 0.2, 0.2);
    fm->km = 0.2;
    fm->ks = 0.2;
    fm->ka = 0.1;
    fm->kd = 0.7;
    Surface *floorTriangle1 = new Triangle(glm::vec3(-10,-2,10),
                                  glm::vec3(-10,-2,-10),
                                  glm::vec3(10,-2,10), fm);

    Surface *floorTriangle2 = new Triangle(glm::vec3(10,-2,10),
                                  glm::vec3(-10,-2,-10),
                                  glm::vec3(10,-2,-10), fm);

    world->addObject(floorTriangle1);
    world->addObject(floorTriangle2);

    // Surface *floor = new Triangle(glm::vec3(800,-1.52,200),
    //                               glm::vec3(-800,-1.52,200),
    //                               glm::vec3(0,-1.52,-900), fm);

    // // world->addObject(floor);

/*    Material *wm = new Material;
    wm->color = glm::vec3(0.4, 0.4, 0.4);
    wm->km = 0.2;
    wm->ks = 0.2;
    wm->ka = 0.1;
    wm->kd = 0.7;

    Surface *leftface1 = new Triangle(glm::vec3(-20,20,10),
                                  glm::vec3(-20,-20,10),
                                  glm::vec3(-20,20,-10), wm);
    Surface *leftface2 = new Triangle(glm::vec3(-20,20,-10),
                                  glm::vec3(-20,-20,10),
                                  glm::vec3(-20,-20,-10), wm); 

    world->addObject(leftface1);
    world->addObject(leftface2);*/



    LightSrc *light = new LightSrc;
    light->pos = glm::vec3(10, 10, 10);
    light->intensity = glm::vec3(1, 1, 1);
    world->addSource(light);

    Renderer *engine = new Renderer(world, camera, true);
    char *fn = (char *) "out.ppm";
    if (argc > 1) {
        fn = argv[1];     
    }
    engine->render(fn);

    return 0;
}
