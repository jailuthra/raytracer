#ifndef __CAMERA_H
#define __CAMERA_H

#include <glm/vec3.hpp>

class Camera {
private:
    glm::vec3 pos, target, up;
    glm::vec3 lookAt;
    glm::vec3 u, v, w; ///< camera basis vectors

    float fov_y; ///< Y-axis field of view (degrees)
    float focalDistance; ///< Distance of camera from screen
    float aspect; ///< width/height
public:
    const int height, width;
    Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up,
           float fov_y, int width, int height);
    glm::vec3 getRayDir(int i, int j) const;
    glm::vec3 getPos() { return pos; }
};

#endif
