#include "../catch/single_include/catch.hpp"
#include "../../src/utility.h"
#include "utilitytest.h"

using namespace PixelMaestro;

TEST_CASE("RNG returns a value other than its starting value.", "[int]") {
	int old_num = 10000;
	int new_num = Utility::rand(old_num);
	REQUIRE(new_num != old_num);
}

TEST_CASE("abs_int returns absolute value.", "[int]") {
	int neg = -15;
	REQUIRE(Utility::abs_int(neg) == (neg * -1));
}
