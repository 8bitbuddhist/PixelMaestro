#include "../catch/single_include/catch.hpp"
#include "Utility.h"
#include "UtilityTest.h"

using namespace PixelMaestro;

TEST_CASE("RNG returns a value.", "[int]") {
	REQUIRE(Utility::rand() > 0);
}

TEST_CASE("abs_char returns absolute value.", "[int]") {
	char neg = -15;
	REQUIRE(Utility::abs_char(neg) == (neg * -1));
}
