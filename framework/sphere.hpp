#ifndef SPHERE_HPP
#define SPHERE_HPP
#include "shape.hpp"
#include <glm/vec3.hpp>
#include "Hitpoint.hpp"
#include "Ray.hpp"

class Sphere : public Shape {
private:
	float rad{ 10.0f };
	glm::vec3 point{ 100.0f, 100.0f, 100.0f };
public:
	Sphere();
	Sphere(float r, glm::vec3 p);
	Sphere(float r, glm::vec3 p, std::string name, glm::vec3 color);
	float Shape::area()const;
	float Shape::volume()const;
	std::ostream& print(std::ostream& os)const;
	HitPoint intersect(Ray )
};
#endif