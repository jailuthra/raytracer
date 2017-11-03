#include "renderer.h"
#include "utils.h"
#include <cfloat>
#include <glm/glm.hpp>

glm::vec3 Renderer::shade(int i, int j)
{
    glm::vec3 dir, col = glm::vec3(0);
    if (antialiase) {
        for (int p = 0; p < 3; p++) {
            for (int q = 0; q < 3; q++) {
                dir = camera->getRayDir(i + (p + eps())/3,
                                        j + (q + eps())/3);
                Ray ray(camera->getPos(), dir);
                col += raycolor(ray, EPSILON, FLT_MAX);
            }
        }
        col /= 9;
    } else {
        dir = camera->getRayDir(i, j);
        Ray ray(camera->getPos(), dir);
        col = raycolor(ray, EPSILON, FLT_MAX);
    }
    return col;
}

glm::vec3 Renderer::raycolor(Ray ray, double t0, double t1)
{
    HitRec rec;
    glm::vec3 col; // return color
    rec.r = &ray;
    if (world->hit(ray, t0, t1, rec)) {
        Material *m = rec.s->mat;
        rec.p = rec.getHitPoint(); // hit point
        rec.normal = glm::normalize(rec.s->getNormal(rec.p)); // normal
        glm::vec3 v = glm::normalize(ray.origin - rec.p); // view vector
        col = m->ka * m->color; // ambient
        for (LightSrc *l: world->sources) {
            glm::vec3 i = glm::normalize(l->pos - rec.p); // incident
            glm::vec3 h = glm::normalize(v + i);
            /* CHECK IF POINT ISN'T IN SHADOW */
            HitRec srec;
            if (!world->hit(Ray(rec.p, i), t0, t1, srec)) {
                float lambert = glm::max(0.f, glm::dot(rec.normal, i)); 
                float phong = glm::pow(glm::max(0.f, glm::dot(rec.normal, h)),
                                       32);
                col += (l->intensity * m->color) * m->kd * lambert;
                col += (l->intensity * m->color) * m->ks * phong;
            }
        }
        return col;
    } else {
        return world->bgcol;
    }
}

void Renderer::render(const char *filename)
{
    for (int j = 0; j < camera->height; j++) {
        for (int i = 0; i < camera->width; i++) {
            pixmap[i + j*camera->width] = shade(i, j);
        }
    }
    makePPM(filename, pixmap, camera->width, camera->height);
}
