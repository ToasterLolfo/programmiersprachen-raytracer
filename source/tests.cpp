#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"
#include <ostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE(" box-test ", "[box-test]")
{
	Box b1 = {};
	glm::vec3 min = { 0.0f, 0.0f, 1.0f };
	glm::vec3 max = { -10.0f, 100.0f, 100.0f };
	Box b2 = { min, max };
	REQUIRE(Approx(b2.volume()) == 99000.0f);
	REQUIRE(Approx(b1.volume()) == 1000000.0f);

	REQUIRE(Approx(b2.area()) == (2000.0f + 1980.0f + 2.0f * 9900.0f));
	REQUIRE(Approx(b1.area()) == 60000.0f);
}

TEST_CASE(" sphere-test ", "[sp-test]") {
	Sphere s1 = {};
	float r = -10.0f;
	glm::vec3 p = { -10.0f, 100.0f, 100.0f };
	Sphere s2 = { r, p };
	Sphere s3 = { 0.0f, p };

	REQUIRE(Approx(s2.volume()).margin(10e-5) == 4188.7902f);
	REQUIRE(Approx(s1.volume()).margin(10e-5) == 4188.7902f);
	REQUIRE(Approx(s3.volume()).margin(10e-5) == 0.0f);

	REQUIRE(Approx(s2.area()).margin(10e-5) == 1256.637f);
	REQUIRE(Approx(s1.area()).margin(10e-5) == 1256.637f);
	REQUIRE(Approx(s3.area()).margin(10e-5) == 0.0f);
}


TEST_CASE("Outstream-test", "[os-test]") {
	Sphere s = {};
	Box b = {};
	std::cout << b << " " << s << std::endl;
}

TEST_CASE("intersect_ray_sphere", "[intersect]")
{
	glm::vec3 ray_origin{ 0.0f, 0.0f, 0.0f };

	glm::vec3 ray_direction{ 0.0f, 0.0f, 1.0f };

	glm::vec3 sphere_center{ 0.0f, 0.0f, 5.0f };
	float sphere_radius{ 1.0f };

	float distance = 0.0f;
	auto result = glm::intersectRaySphere(
		ray_origin, ray_direction, sphere_center, sphere_radius * sphere_radius, distance);
	REQUIRE(distance == Approx(4.0f));

	Sphere s1{ sphere_radius, sphere_center };
	Ray r1{ ray_origin, ray_direction };
	Hitpoint h1 = s1.intersect(r1);
	REQUIRE(h1.distance == distance);
	REQUIRE(h1.hit == result);


	glm::vec3 ray_origin1{ 0.0f, 0.0f, 0.0f };

	glm::vec3 ray_direction1{ 0.0f, 1.0f, 0.0f };

	glm::vec3 sphere_center1{ 0.0f, 0.0f, 5.0f };
	float sphere_radius1{ 1.0f };

	float distance1 = 0.0f;
	Sphere s2{ sphere_radius1, sphere_center1 };
	Ray r2{ ray_origin1, ray_direction1 };
	Hitpoint h2 = s2.intersect(r2);

	REQUIRE(h2.hit == false);

	glm::vec3 ray_origin2{ 0.0f, 1.0f, 0.0f };

	glm::vec3 ray_direction2{ 0.0f, 0.0f, 1.0f };

	glm::vec3 sphere_center2{ 0.0f, 0.0f, 5.0f };
	float sphere_radius2{ 1.0f };

	float distance2 = 0.0f;
	Sphere s3{ sphere_radius2, sphere_center2 };
	Ray r3{ ray_origin2, ray_direction2 };
	Hitpoint h3 = s3.intersect(r3);

	float dist = 0.0f;
	auto v = glm::normalize(r3.direction);
	glm::intersectRaySphere(ray_origin2, v, sphere_center2, sphere_radius2 * sphere_radius2, dist);
	glm::vec3 ergeb = { 0, 1, 5 };

	REQUIRE(h3.hit == true);
	REQUIRE(h3.color_obj == s3.get_color());
	REQUIRE(h3.name_obj == s3.get_name());
	std::cout << h3.hit_p.x << h3.hit_p.y << h3.hit_p.z << std::endl;
	REQUIRE(h3.hit_p == ergeb);
	REQUIRE(h3.distance == dist);
	REQUIRE(h3.ray_dir == ray_direction2);

}

TEST_CASE("destruktor-test", "[dtor-test]")
{
	std::cout << " Beginn " << std::endl;
	glm::vec3 red = { 1.0f, 0.0f, 0.0f };
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	std::string name1 = "sphere0";
	std::string name2 = "sphere1";
	Sphere* s1 = new Sphere{ 1.2f, position,  name1, red };
	Shape* s2 = new Sphere{ 1.2f, position,  name2, red };

	s1->print(std::cout);
	s2->print(std::cout);

	delete s1;
	delete s2;
}


int main(int argc, char *argv[])
{ 
  return Catch::Session().run(argc, argv);
}
