#include "box.hpp"
#include "cmath"

Box::Box():
	Shape::Shape{},
	min_{ 0.0f, 0.0f , 0.0f },
	max_{ 100.0f, 100.0f, 100.0f }
{}

Box::Box(glm::vec3 min, glm::vec3 max) :
	Shape::Shape{},
	min_(min),
	max_(max)
{}

Box::Box(glm::vec3 min, glm::vec3 max, std::string name, glm::vec3 color) :
	Shape::Shape{name, color},
	min_(min),
	max_(max)
{}

float Box::area()const {
	float a = abs(max_.x - min_.x);
	float b = abs(max_.y - min_.y);
	float c = abs(max_.z - min_.z);
	return 2 * a * b + 2 * a * c + 2 * b * c;
}

float Box::volume()const {
	return abs(max_.x - min_.x) * abs(max_.y - min_.y) * abs(max_.z - min_.z);
}

std::ostream& Box::print(std::ostream& os)const {
	Shape::print(os);
	return os << min_.x << " " << min_.y << " " << min_.z << " " << max_.x << " " << max_.y << " " << max_.z << std::endl;
}
