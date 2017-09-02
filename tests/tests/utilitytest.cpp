#include "../catch/single_include/catch.hpp"
#include "utility.h"
#include "utilitytest.h"

using namespace PixelMaestro;

TEST_CASE("RNG returns a non-zero value.", "[int]") {
	REQUIRE(Utility::rand() != 0);
}

TEST_CASE("abs_int returns absolute value.", "[int]") {
	int neg = -15;
	REQUIRE(Utility::abs_int(neg) == (neg * -1));
}
