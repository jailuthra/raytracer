#include "renderer.h"
#include "utils.h"
#include <cfloat>
#include <glm/glm.hpp>
#include <iostream>

glm::vec3 Renderer::shade(int i, int j)
{
    glm::vec3 dir, col = glm::vec3(0);
    float delT;
    if (antialiase) {
        for (int p = 0; p < 3; p++) {
            for (int q = 0; q < 3; q++) {
                dir = camera->getRayDir(i + (p + eps())/3,
                                        j + (q + eps())/3); // direction of ray for AA
                for (int r = 0; r < 2; r++) {
                    delT = eps(); // time interval of ray for Motion Blur
                    Ray ray(camera->getPos(), dir, delT);
                    col += raycolor(ray, EPSILON, FLT_MAX);
                }
            }
        }
        col /= 18;
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
    static int refract_depth = 0; // used for refractions

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
            for(int p = 0; p < 2; p++){
                for(int q = 0; q < 2; q++){
                    // take a random point in the area light source
                    glm::vec3 subLightSrc = l->pos + l->a * ((p + eps())/2) + l->b * ((q + eps())/2);
                    glm::vec3 i = glm::normalize(subLightSrc - rec.p); // incident ray
                    glm::vec3 h = glm::normalize(v + i); // half view ray for phong
                    HitRec srec;
                    if (!world->hit(Ray(rec.p, i), t0, t1, srec)) { // if point isn't in shadow
                        float lambert = glm::max(0.f, glm::dot(rec.normal, i)); 
                        float phong = glm::pow(glm::max(0.f, glm::dot(rec.normal, h)),
                                               32);
                        shadowCol += (l->intensity * m->color) * m->kd * lambert;
                        shadowCol += (l->intensity * m->color) * m->ks * phong;
                    }
                }
            }
            shadowCol /= 4; // Divide total shadow color by number of light sources
            col += shadowCol;
        }

        // reflect if needed
        if (m->km == 0 || depth == MAX_DEPTH) {
            depth = 0;
        } else {
            depth++;
            glm::vec3 reflectedDir = glm::reflect(-v, rec.normal); //Reflected ray direction

            /*Create orthonormal basis with w = reflected ray*/
            glm::vec3 w = glm::normalize(reflectedDir);
            glm::vec3 t = glm::vec3(w.x, w.y, w.z + 1.0f); //Pick random vector not collinear with w
            glm::vec3 u = glm::normalize(glm::cross(t, w));
            glm::vec3 v = glm::normalize(glm::cross(w, u));

            // float a = 0.10; //Sampling on square of width a units

            /*Choose random point (sampleX,sampleY) on square*/
            float sampleX = -(m->a/2) + (eps() * m->a);
            float sampleY = -(m->a/2) + (eps() * m->a);

            /*Calculate perturbed reflected ray direction*/
            glm::vec3 perturbReflectedDir = glm::normalize(reflectedDir + (u * sampleX) + (v * sampleY));

            /*Check if new reflected ray is above surface and calculate the color*/
            if(glm::dot(perturbReflectedDir, rec.normal) >= 0){
                col += m->km * raycolor(Ray(rec.p, perturbReflectedDir, eps()),
                                    1e-2, FLT_MAX);
            }
        }

        if(m->kt == 0 || refract_depth == MAX_DEPTH) {
            refract_depth = 0;
        } else {
            refract_depth++; 
            glm::vec3 d = glm::normalize(rec.p - ray.origin); //Calculate ray direction
            glm::vec3 n = rec.normal;

            glm::vec3 reflectDir = glm::reflect(d, n); //Get reflected component's direction

            glm::vec3 transmitDir(0.0);

            /* Check if dielectric is entered */
            if(glm::dot(d, n) < 0){
                transmitDir = glm::refract(d, n, 1.0f/m->eta); //Calculate transmitted ray direction
            }
            /*Check if dieletric is exited*/
            else{
                transmitDir = glm::refract(d, -n, m->eta); //Calculate transmitted ray direction while exiting
                
                /* Check for Total Internal Reflection 
                * TIR if transmitted ray = 0
                */
                if (transmitDir == glm::vec3(0.0f)) { 
                    //TIR detected --> shoot ray in reflected ray direction
                    col = raycolor(Ray(rec.p, reflectDir), 1e-2, FLT_MAX); 
                    return glm::clamp(col, 0.0f, 1.0f);
                }
            }

            col = raycolor(Ray(rec.p, transmitDir, eps()), 1e-2, FLT_MAX);
        }

        return glm::clamp(col, 0.0f, 1.0f);
    }
    else {
        refract_depth = 0;
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
