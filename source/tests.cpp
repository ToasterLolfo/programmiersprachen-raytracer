#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "shape.hpp"
#include "sphere.hpp"
#include "box.hpp"

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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
