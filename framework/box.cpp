#include "box.hpp"
#include "cmath"

Box::Box():
	Shape::Shape{"Quader"},
	min_{ 0.0f, 0.0f , 0.0f },
	max_{ 100.0f, 100.0f, 100.0f }
{}

Box::Box(glm::vec3 min, glm::vec3 max) :
	Shape::Shape{"Quader"},
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

Hitpoint Box::intersect(Ray const& ray)
{
	Hitpoint schnitt = {};
	float y;
	float z;
	float x;
	float t = 0;
	if (ray.direction.x != 0) {
		t = (min_.x - ray.origin.x) / ray.direction.x;
		y = ray.origin.y + t * ray.direction.y;
		z = ray.origin.z + t * ray.direction.z;
		if (min_.y <= y <= max_.y and min_.z <= z <= max_.z) {
			schnitt.hit = true;
			schnitt.distance = t;
			schnitt.color_obj = get_color();
			schnitt.name_obj = get_name();
			schnitt.hit_p = { min_.x, y, z };
			schnitt.ray_dir = ray.direction;
	}
	}
	else if (ray.direction.x == 0 and ray.direction.y != 0) {
		t = (min_.y - ray.origin.y) / ray.direction.y;
		x = ray.origin.x + t * ray.direction.x;
		z = ray.origin.z + t * ray.direction.z;
		if (min_.x <= x <= max_.x and min_.z <= z <= max_.z) {
			schnitt.hit = true;
			schnitt.distance = t;
			schnitt.color_obj = get_color();
			schnitt.name_obj = get_name();
			schnitt.hit_p = { x, min_.y, z };
			schnitt.ray_dir = ray.direction;
		}
	}
	else {
		t = (min_.z - ray.origin.z) / ray.direction.z;
		x = ray.origin.x + t * ray.direction.x;
		y = ray.origin.y + t * ray.direction.y;
		if (min_.x <= x <= max_.x and min_.y <= y <= max_.y) {
			schnitt.hit = true;
			schnitt.distance = t;
			schnitt.color_obj = get_color();
			schnitt.name_obj = get_name();
			schnitt.hit_p = { x, y, min_.z };
			schnitt.ray_dir = ray.direction;
		}
	}
	
	return schnitt;
}
