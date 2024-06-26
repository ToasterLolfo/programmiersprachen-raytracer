#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <ostream>
#include <glm/vec3.hpp>

class Shape {
private:
	std::string name_;
	glm::vec3 color_;
public:
	virtual float area()const = 0;
	virtual float volume()const = 0;
	Shape();
	Shape(std::string name, glm::vec3 color);
	virtual std::ostream& print(std::ostream& os)const;
};
std::ostream& operator<<(std::ostream& os, Shape const& s);
#endif