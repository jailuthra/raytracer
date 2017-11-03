#include "utils.h"
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <glm/gtc/type_ptr.hpp>

void makePPM(const char *fname, glm::vec3 *pixmap, int w, int h)
{
    std::fstream f(fname, std::fstream::out|std::fstream::binary);
    std::stringstream header;
    header << "P6\n";
    header << w << " " << h << "\n";
    header << "255\n";
    f.write(header.str().c_str(), header.str().length());  
    glm::vec3 p;
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            p = pixmap[i + j*w];
            const uint8_t rgb[3] = {uint8_t(p.x * 255), uint8_t(p.y * 255),
                              uint8_t(p.z * 255)};
            f.write((char *) rgb, sizeof(uint8_t) * 3);
        }
    }
    f.close();
}
