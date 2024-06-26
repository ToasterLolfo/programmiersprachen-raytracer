#include "sphere.hpp"
#include <numbers>
#include <cmath>

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

float Sphere::volume()const {
	return abs((4.0f / 3.0f) * std::numbers::pi * rad * rad * rad);
}

float Sphere::area()const {
	return abs(4.0f * std::numbers::pi * rad * rad);
}