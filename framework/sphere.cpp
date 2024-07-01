#include "sphere.hpp"
#include <numbers>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>

Sphere::Sphere():
	Shape::Shape{"Kugel"},
    rad{ 10.0f },
	point{ 100.0f, 100.0f, 100.0f }
{std::cout << "Sphere ctor" << std::endl; }

Sphere::~Sphere()
{
	std::cout << "Sphere dtor" << std::endl;
}

Sphere::Sphere(float r, glm::vec3 p) :
	Shape::Shape{"Kugel"},
	rad(r),
	point(p)
{
	std::cout << "Sphere ctor" << std::endl;
}

Sphere::Sphere(float r, glm::vec3 p, std::string name, glm::vec3 color): 
	Shape::Shape{name, color},
	rad(r),
	point(p)
{
	std::cout << "Sphere ctor" << std::endl;
}


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

Hitpoint Sphere::intersect(Ray r)const {
	auto v = glm::normalize(r.direction);
	float dist = 0.0f;
	if( glm::intersectRaySphere(r.origin, v, point, rad * rad, dist)) {
		Hitpoint hitpoint;
		hitpoint.hit = true;
		hitpoint.distance = dist;
		hitpoint.name_obj = Shape::get_name();
		hitpoint.color_obj = Shape::get_color();
		float a = (r.direction.x) * (r.direction.x) +
			(r.direction.y) * (r.direction.y) + (r.direction.z) * (r.direction.z);
		float b = 2 * ((r.origin.x - point.x) * r.direction.x +
			+ (r.origin.y - point.y) * r.direction.y + (r.origin.z - point.z) * r.direction.z);
		float c = ((r.origin.x - point.x) * (r.origin.x - point.x) +
			(r.origin.y - point.y) * (r.origin.y - point.y) +
			(r.origin.z - point.z) * (r.origin.z - point.z)) - (rad * rad);
		std::cout << "hier " << a << " " << b << " " << c << std::endl;
		if ((b * b - 4 * a * c) == 0) {
			float t = (-b) / (2 * a);
			glm::vec3 treffer = { r.origin.x + (t * r.direction.x), r.origin.y + (t * r.direction.y),
			r.origin.z + (t * r.direction.z) };
			hitpoint.hit_p = treffer;
		}
		else {
			float t1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
			float t2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
			glm::vec3 treffer = { r.origin.x + (t1 * r.direction.x), r.origin.y + (t1 * r.direction.y),
			r.origin.z + (t1 * r.direction.z) }; 
			hitpoint.hit_p = treffer;
			

		}
		hitpoint.ray_dir = r.direction;
		return hitpoint;
	}
	else {
		Hitpoint hitpoint;
		hitpoint.hit = false;
		return hitpoint;
	}
	
}