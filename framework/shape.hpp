#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <string>
#include <ostream>
#include <glm/vec3.hpp>
#include "Hitpoint.hpp"
#include "Ray.hpp"
#include "Material.hpp"

class Shape {
private:
	std::string name_;
	std::shared_ptr<Material> color_;
public:
	virtual float area()const = 0;
	virtual float volume()const = 0;
	Shape();
	Shape(std::string name, std::shared_ptr<Material> color);
	Shape(std::string name);
	~Shape();
	virtual std::ostream& print(std::ostream& os)const;
	virtual std::string get_name()const;
	virtual std::shared_ptr<Material> get_color()const;
	virtual Hitpoint intersect(Ray const& ray) = 0;
};
std::ostream& operator<<(std::ostream& os, Shape const& s);
#endif