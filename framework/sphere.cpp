#include "sphere.hpp"
#include <numbers>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

Sphere::Sphere():
	Shape::Shape{},
    rad{ 10.0f },
	point{ 100.0f, 100.0f, 100.0f }
{}

Sphere::Sphere(float r, glm::vec3 p) :
	Shape::Shape{},
	rad(r),
	point(p)
{}

Sphere::Sphere(float r, glm::vec3 p, std::string name, glm::vec3 color): 
	Shape::Shape{name, color},
	rad(r),
	point(p)
{}

float Sphere::volume()const {
	return abs((4.0f / 3.0f) * std::numbers::pi * rad * rad * rad);
}

float Sphere::area()const {
	return abs(4.0f * std::numbers::pi * rad * rad);
}

std::ostream& Sphere::print(std::ostream& os)const {
	Shape::print(os);
	return os << rad << " " << point.x << " " << point.y << " " << point.z << std::endl;
}

Hitpoint Sphere::intersect(Ray r) {
	glm::intersectRaySphere(r.origin, glm::normalize(r.direction), point, rad * rad);
}