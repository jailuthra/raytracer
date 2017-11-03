#ifndef __UTILS_H
#define __UTILS_H

#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>

void makePPM(const char *fname, glm::vec3 *pixmap, int w, int h);

#endif
