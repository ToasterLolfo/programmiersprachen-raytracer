#include "shape.hpp"


Shape::Shape():
	name_{ "Quader" },
	color_{ 0.5f, 0.5f, 0.5f }
{}

Shape::Shape(std::string name, glm::vec3 color):
	name_(name),
	color_(color)
{}

std::ostream& Shape::print(std::ostream& os)const {
	return os << name_ << " " << color_.x << " " << color_.y << " " << color_.z << std::endl;
}

std::ostream& operator<<(std::ostream & os, Shape const& s)
{
	return s.print(os);
}

std::string Shape::get_name()const {
	return name_;
}

glm::vec3 Shape::get_color()const {
	return color_;
}