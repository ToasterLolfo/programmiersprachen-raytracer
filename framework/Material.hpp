#ifndef MATERIAL_HPP
#define MATERIAL_HPP
#include "color.hpp"
#include <string>
struct Material {
	std::string name{ "material1" };
	Color ka{ 0.5f, 0.5f, 0.5f };
	Color kd{ 0.7f, 0.7f, 0.7f };
	Color ks{ 0.2f, 0.2f, 0.2f };
	
	//hinzugef�gt
	float m{ 10.0f }; // Glanzgrad
	float refraction_index{ 1.5f }; // Brechungsindex
	//z.B. f�r Glas 1.5f

	// Konstruktor
	Material(
		std::string name = "material1",
		Color ka = Color(0.5f, 0.5f, 0.5f),
		Color kd = Color(0.7f, 0.7f, 0.7f),
		Color ks = Color(0.2f, 0.2f, 0.2f),
		float m = 10.0f,
		float refraction_index = 1.5f
	) : name(name), kd(kd), ka(ka), ks(ks), m(m), refraction_index(refraction_index) {}
	//hinzugef�gt ende
	
	
	// Ausgabe-Operator
	/*friend std::ostream& operator<<(std::ostream& os, Material const& mat) {
		os << mat.name << " " << mat.kd << mat.ka << mat.ks << " " << mat.m << std::endl;
	}*/

	friend std::ostream& operator<<(std::ostream& os, Material const& mat) {
		os << mat.name << " " << mat.kd << " " << mat.ka << " " << mat.ks << " " << mat.m << " " << mat.refraction_index << std::endl;
		return os;
	}
};
#endif