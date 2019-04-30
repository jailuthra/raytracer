#include "camera.h"
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <iostream>

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
    focalDistance = 1.0f/(2.0f * glm::tan(glm::radians(this->fov_y / 2.0f)));
}

Camera::Camera(const Camera &c, int width, int height) :
                    Camera(c.pos, c.target, c.up, c.fov_y, width, height)
{
}

glm::vec3 Camera::getRayDir(float i, float j) const
{
    float z = focalDistance;
    float x = aspect * (i - width/2.0 + 0.5) / width;
    float y = -(j - height/2.0 + 0.5) / height;
    return glm::normalize((x * u) + (y * v) + (z * (-w)));
}
