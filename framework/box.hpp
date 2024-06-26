#ifndef BOX_HPP
#define BOX_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {
private:
	glm::vec3 min_{ 0.0f, 0.0f, 0.0f };
	glm::vec3 max_{ 100.0f, 100.0f, 100.0f };
public:
	Box();
	Box(glm::vec3 min, glm::vec3 max);
	float area()const;
	float volume()const;
};

#endif