#include "fovea.h"
#include <iostream>

bool Fovea::sample(const int i, const int j,
                   const int width, const int height)
{
    glm::vec2 pix(i/((float)width), j/((float)height));
    float dis = glm::distance(pix, eye);
    float p = p_min; // sampling probability default p_min
    if (dis <= r0) {
        // within foveal inner region
        return true;
    } else {
        if (dis <= r1) {
            // within foveal outer region
            p = 1 - (1 - p_min)*(dis - r0)/(r1 - r0);
        } else {
            //std::cout << i << " " << j << " " << "in r1+" << std::endl;
        }
        // return true/false w.r.t sampling probability
        return (eps() <= p);
    }
}
