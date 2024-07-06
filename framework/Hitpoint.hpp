#ifndef HITPOINT_HPP
#define HITPOINT_HPP
#include <glm/vec3.hpp>
#include <string>
struct Hitpoint {
	bool hit{ false };
	float distance{ 0.0f };
	std::string name_obj{ "none" };
	std::shared_ptr<Material> color_obj;
	glm::vec3 hit_p{ 0.0f, 0.0f, 0.0f };
	glm::vec3 ray_dir{ 0.0f, 0.0f, 0.0f };
};
#endif