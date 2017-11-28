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
    static int depth = 0; // used for reflections
    HitRec rec;
    glm::vec3 col(0); // return color
    rec.r = &ray;
    if (world->hit(ray, t0, t1, rec)) {
        Material *m = rec.s->mat;
        rec.p = rec.getHitPoint(); // hit point
        rec.normal = glm::normalize(rec.s->getNormal(rec.p)); // normal
        glm::vec3 v = glm::normalize(ray.origin - rec.p); // view vector
        col += m->ka * m->color; // ambient
        for (LightSrc *l: world->sources) {

            /* SOFT SHADOWS */
            glm::vec3 shadowCol(0);
            for(int p = 0; p < 3; p++){
                for(int q = 0; q < 3; q++){
                    glm::vec3 subLightSrc = glm::vec3(
                                                        (l->pos).x - 1.5 + (p + eps()), 
                                                        (l->pos).y, 
                                                        (l->pos).z - 1.5 + (q + eps())
                                                        );

                    glm::vec3 i = glm::normalize(subLightSrc - rec.p);
                    glm::vec3 h = glm::normalize(v + i);

                    HitRec srec;
                    if (!world->hit(Ray(rec.p, i), t0, t1, srec)) {
                        float lambert = glm::max(0.f, glm::dot(rec.normal, i)); 
                        float phong = glm::pow(glm::max(0.f, glm::dot(rec.normal, h)),
                                               32);
                        shadowCol += (l->intensity * m->color) * m->kd * lambert;
                        shadowCol += (l->intensity * m->color) * m->ks * phong;
                    }
                }
            }

            shadowCol /= 9; // Divide total shadow color by number of light sources
            col += shadowCol;

            // glm::vec3 i = glm::normalize(l->pos - rec.p); // incident
            // glm::vec3 h = glm::normalize(v + i);
            // /* CHECK IF POINT ISN'T IN SHADOW */
            // HitRec srec;
            // if (!world->hit(Ray(rec.p, i), t0, t1, srec)) {
            //     float lambert = glm::max(0.f, glm::dot(rec.normal, i)); 
            //     float phong = glm::pow(glm::max(0.f, glm::dot(rec.normal, h)),
            //                            32);
            //     col += (l->intensity * m->color) * m->kd * lambert;
            //     col += (l->intensity * m->color) * m->ks * phong;
            // }
        }
        // reflect if needed
        if (m->km == 0 || depth == MAX_DEPTH) {
            depth = 0;
        } else {
            glm::vec3 reflectedDir = glm::reflect(-v, rec.normal); //Reflected ray direction

            /*Create orthonormal basis with w = reflected ray*/
            glm::vec3 w = glm::normalize(reflectedDir);
            glm::vec3 t = glm::vec3(w.x, w.y, w.z + 1.0f); //Pick random vector not collinear with w
            glm::vec3 u = glm::normalize(glm::cross(t, w));
            glm::vec3 v = glm::normalize(glm::cross(w, u));

            float a = 0.10; //Sampling on square of width a units

            /*Choose random point (sampleX,sampleY) on square*/
            float sampleX = -(a/2) + (eps() * a);
            float sampleY = -(a/2) + (eps() * a);

            /*Calculate perturbed reflected ray direction*/
            glm::vec3 perturbReflectedDir = glm::normalize(reflectedDir + (u * sampleX) + (v * sampleY));

            /*Check if new reflected ray is above surface and calculate the color*/
            if(glm::dot(perturbReflectedDir, rec.normal) >= 0){
                col += m->km * raycolor(Ray(rec.p, perturbReflectedDir),
                                    1e-2, FLT_MAX);
            }
        }
        depth++;
        return glm::clamp(col, 0.0f, 1.0f);
    } else {
        depth = 0;
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
