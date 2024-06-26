#include "box.hpp"

Box::Box():
	min_{ 0.0f, 0.0f , 0.0f },
	max_{ 100.0f, 100.0f, 100.0f }
{}

float Box::area()const {
	float a = max_.x - min_.x;
	float b = max_.y - min_.y;
	float c = max_.z - min_.z;
	return 2 * a * b + 2 * a * c + 2 * b * c;
}

float Box::volume()const {
	return (max_.x - min_.x) * (max_.y - min_.y) * (max_.z - min_.z);
}
