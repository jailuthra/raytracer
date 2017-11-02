#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <glm/vec3.hpp>

struct Material
{
    glm::vec3 color; ///< Base color
	double ka; ///< Ambient contribution
	double kd; ///< Diffuse constant
	double ks; ///< Specular constant
	double kr; ///< Contribution from reflection
	double kt; ///< Contribution from refraction
};

#endif
