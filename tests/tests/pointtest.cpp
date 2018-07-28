#include "../catch/single_include/catch.hpp"
#include "../../src/core/point.h"
#include "pointtest.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Point.", "[Point]") {
	int x = 40;
	int y = 60;
	Point point(x, y);

	SECTION("Verify coordinates are stored correctly.") {
		REQUIRE(point.x == x);
		REQUIRE(point.y == y);
	}

	SECTION("Verify coordinates can be resized.") {
		int new_x = 90;
		int new_y = 180;

		point.set(new_x, new_y);

		REQUIRE(point.x == new_x);
		REQUIRE(point.y == new_y);
	}

	SECTION("Verify inline index calculates correctly.") {
		int target_x = 15;
		int target_y = 30;

		int inline_index = (target_y * point.x) + target_x;

		REQUIRE(point.get_inline_index(target_x, target_y) == inline_index);
	}

	SECTION("Verify size.") {
		REQUIRE(point.size() == x * y);
	}
}
