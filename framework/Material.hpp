#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <string>
struct Material {
	std::string name{ "material" };
	Color kd{ 0.0f, 0.0f, 0.0f };
	Color ka{ 0.0f, 0.0f, 0.0f };
	Color ks{ 0.0f, 0.0f, 0.0f };
	float m{ 0.0f };

	friend std::ostream& operator<<(std::ostream& os, Material const& mat) {
		os << mat.name << " " << mat.kd << mat.ka << mat.ks << " " << mat.m << std::endl;
	}
};
#endif