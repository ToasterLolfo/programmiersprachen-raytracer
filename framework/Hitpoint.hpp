#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include <glm/vec3.hpp>
#include <string>
struct Hitpoint {
	bool hit;
	float distance;
	std::string name_obj;
	glm::vec3 color_obj;
	glm::vec3 hit_p;
	glm::vec3 ray_dir;
};
#endif