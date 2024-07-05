#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <ostream>
#include <glm/vec3.hpp>
#include "Hitpoint.hpp"
#include "Ray.hpp"

class Shape {
private:
	std::string name_;
	glm::vec3 color_;
public:
	virtual float area()const = 0;
	virtual float volume()const = 0;
	Shape();
	Shape(std::string name, glm::vec3 color);
	Shape(std::string name);
	~Shape();
	virtual std::ostream& print(std::ostream& os)const;
	virtual std::string get_name()const;
	virtual glm::vec3 get_color()const;
	virtual Hitpoint intersect(Ray const& ray) = 0;
};
std::ostream& operator<<(std::ostream& os, Shape const& s);
#endif