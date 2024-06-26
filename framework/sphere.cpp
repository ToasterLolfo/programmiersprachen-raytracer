#include "sphere.hpp"
#include <numbers>
#include <cmath>

Sphere::Sphere():
    rad{ 10.0f },
	point{ 100.0f, 100.0f, 100.0f }
{}

float Sphere::volume()const {
	return (4.0f / 3.0f) * std::numbers::pi * rad * rad * rad;
}

float Sphere::area()const {
	return 4.0f * std::numbers::pi * rad * rad;
}