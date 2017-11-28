#ifndef __LIGHTSOURCE_H
#define __LIGHTSOURCE_H

struct LightSrc {	
    glm::vec3 pos;
    glm::vec3 intensity;
    glm::vec3 a, b; // non-zero if area (parallelogram) light source
};

#endif
