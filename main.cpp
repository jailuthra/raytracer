#include "src/renderer.h"
#include "src/world.h"
#include "src/camera.h"
#include "src/sphere.h"
#include <glm/vec3.hpp>

int main()
{
    int screen_width = 800, screen_height = 600;

    // Camera
    glm::vec3 camera_position(0, 0, 10);
    glm::vec3 camera_target(0, 0, 0); //Looking down -Z axis
    glm::vec3 camera_up(0, 1, 0);
	float camera_fovy =  45;
	Camera *camera = new Camera(camera_position, camera_target, camera_up, camera_fovy, screen_width, screen_height);

	// World
	World *world = new World;
    world->bgcol = glm::vec3(0.1f, 0.3f, 0.6f);
	
	Material *m = new Material;
	m->color = glm::vec3(0.2, 0.8, 0.0);
    m->ks = 0.3;
	m->ka = 0.1;
	m->kd = 0.6;
	
	Surface *sphere = new Sphere(glm::vec3(0.5f, 0, 0), 1.5, m);
    //Object *triangle = new Triangle(Vector3D(2,0,0), Vector3D(-1,0,4), Vector3D(0,3,0), m);
    world->addObject(sphere);
    //world->addObject(triangle);

	LightSrc *light = new LightSrc;
    light->pos = glm::vec3(10, 10, 10);
    light->intensity = glm::vec3(1, 1, 1);
	world->addSource(light);

	Renderer *engine = new Renderer(world, camera);
    engine->render("out.pbm");

    return 0;
}
