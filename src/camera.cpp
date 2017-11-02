#include "camera.h"
#include <glm/geometry.hpp>
#include <glm/trignometric.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 target, glm::vec3 up,
               float fov_y, int width,
               int height) : pos(pos), target(target),
                             fov_y(fov_y), width(width), height(height)
{
    this->up = glm::normalize(up);
    lookAt = target - pos;
    w = glm::normalize(-lookAt);
    u = glm::normalize(glm::cross(up, w));
    v = glm::normalize(glm::cross(w, u));
    aspect = ((float) width) / ((float) height);
    focalDistance = 1.0f/(2.0f * glm::tan(glm::radians(fov_y / 2.0f)));
}

glm::vec3 Camera::getRayDir(int i, int j) const
{
    double z = focalDistance;
    double x = aspect * (i - width/2.0 + 0.5) / width;
    double y = (j - height/2.0 + 0.5) / height;
    return glm::normalize(glm::vec3(x * u, y * v, z * (-w)));
}
