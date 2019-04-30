#ifndef __FOVEA_H
#define __FOVEA_H

#include <cstdlib>
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

class Fovea
{
public:
    // eye position in [0,1]^2
    glm::vec2 eye;
    float r0; ///> fovea inner radius
    float r1; ///> fovea outer radius
    float p_min; ///> minimum sampling probability
    // constructor
    Fovea(glm::vec2 eye, float r0, float r1,
          float p_min) : eye(eye),
                         r0(r0), r1(r1), p_min(p_min)
    { }
    /** Random float from 0 to 1 (inclusive). */
    float eps() { return static_cast <float> (rand())
                       / static_cast <float> (RAND_MAX);}
    /** @return true/false if pixel should be sampled **/
    bool sample(const int i, const int j,
                const int width, const int height);
};

#endif
