#include "src/renderer.h"
#include "src/world.h"
#include "src/camera.h"
#include "src/sphere.h"
#include "src/triangle.h"
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
    world->bgcol = glm::vec3(0.8f, 0.8f, 0.8f);
    
    Material *m = new Material;
    m->color = glm::vec3(1.0, 1.0, 1.0);
    m->km = 0;
    m->ks = 0.3;
    m->ka = 0.1;
    m->kd = 0.6;

    m->kt = 1.0;
    m->eta = 1.15;
    
    Surface *sphere = new Sphere(glm::vec3(0.5f, -0.5, 0), 1.5, m);
    //Object *triangle = new Triangle(Vector3D(2,0,0), Vector3D(-1,0,4), Vector3D(0,3,0), m);
    world->addObject(sphere);
    //world->addObject(triangle);

    Material *m2 = new Material;
    m2->color = glm::vec3(0.8, 0.1, 0.2);
    m2->km = 0;
    m2->ks = 0.3;
    m2->ka = 0.3;
    m2->kd = 0.4;

    Surface *sphere2 = new Sphere(glm::vec3(-2, -1.5, 2), 0.5, m2);
    world->addObject(sphere2);

    Material *m3 = new Material;
    m3->color = glm::vec3(0.1, 0.5, 0.1);
    m3->km = 0;
    m3->ks = 0.3;
    m3->ka = 0.3;
    m3->kd = 0.4;

    Surface *sphere3 = new Sphere(glm::vec3(-0.5f, -1.0, -3), 1, m3);
    world->addObject(sphere3);

    // Floor 
    Material *fm = new Material;
    fm->color = glm::vec3(0.2, 0.2, 0.2);
    fm->km = 0.3;
    fm->ks = 0.2;
    fm->ka = 0.1;
    fm->kd = 0.7;
    fm->a = 0.05;
    Surface *floorTriangle1 = new Triangle(glm::vec3(-20,-2,40),
                                  glm::vec3(-20,-2,-40),
                                  glm::vec3(20,-2,40), fm);

    Surface *floorTriangle2 = new Triangle(glm::vec3(20,-2,40),
                                  glm::vec3(-20,-2,-40),
                                  glm::vec3(20,-2,-40), fm);

    world->addObject(floorTriangle1);
    world->addObject(floorTriangle2);

/*    Material *wm1 = new Material;
    wm1->color = glm::vec3(0.4, 0.4, 0.4);
    wm1->km = 0;
    wm1->ks = 0.0;
    wm1->ka = 0.3;
    wm1->kd = 0.7;
    wm1->a = 0;

    Material *wm2 = new Material;
    wm2->color = glm::vec3(0.7, 0.7, 0.2);
    wm2->km = 0.5;
    wm2->ks = 0.2;
    wm2->ka = 0.1;
    wm2->kd = 0.7;
    wm2->a = 0.10;*/

/*    Surface *leftface1 = new Triangle(glm::vec3(-20,10,40),
                                  glm::vec3(-20,10,-10),
                                  glm::vec3(-20,-2,40), wm1);
    Surface *leftface2 = new Triangle(glm::vec3(-20,10,-10),
                                  glm::vec3(-20,-2,-10),
                                  glm::vec3(-20,-2,40), wm1); 

    world->addObject(leftface1);
    world->addObject(leftface2);

    Surface *rightface1 = new Triangle(glm::vec3(20,10,-10),
                                  glm::vec3(20,-2,40),
                                  glm::vec3(20,-2,-10), wm1);
    Surface *rightface2 = new Triangle(glm::vec3(20,10,-10),
                                  glm::vec3(20,10,40),
                                  glm::vec3(20,-2,40), wm1); 

    world->addObject(rightface1);
    world->addObject(rightface2);*/

/*    Surface *topface1 = new Triangle(glm::vec3(10,10,-10),
                                  glm::vec3(-10,10,40),
                                  glm::vec3(10,10,40), wm1);
    Surface *topface2 = new Triangle(glm::vec3(-10,10,40),
                                  glm::vec3(10,10,-10),
                                  glm::vec3(-10,10,-10), wm1);


    world->addObject(topface1);
    world->addObject(topface2);

    Surface *frontface1 = new Triangle(glm::vec3(-10,10,-10),
                                  glm::vec3(10,10,-10),
                                  glm::vec3(10,-2,-10), wm2);
    Surface *frontface2 = new Triangle(glm::vec3(-10,10,-10),
                                  glm::vec3(10,-2,-10),
                                  glm::vec3(-10,-2,-10), wm2);


    world->addObject(frontface1);
    world->addObject(frontface2);*/



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

    Renderer *engine = new Renderer(world, camera, true);
    char *fn = (char *) "out.ppm";
    if (argc > 1) {
        fn = argv[1];     
    }
    engine->render(fn);

    return 0;
}
