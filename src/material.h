#ifndef __MATERIAL_H
#define __MATERIAL_H

#include <glm/vec3.hpp>

struct Material
{
    glm::vec3 color; ///< Base color
	float ka; ///< Ambient contribution
	float kd; ///< Diffuse constant
	float ks; ///< Specular constant
	float km; ///< Contribution from reflection
	float kt; ///< Contribution from refraction

	float a; ///< glossy reflections sample square width
	float eta; ///< refractive index of material
};

#endif
