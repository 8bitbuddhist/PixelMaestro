#ifndef TIMERTEST_H
#define TIMERTEST_H

class TimerTest {
	public:
		TimerTest();

	protected:

	private:
};

#endif // TIMERTEST_H

#include "../catch/single_include/catch.hpp"
#include "../../src/core/maestro.h"
#include "../../src/core/section.h"
#include "../../src/core/timer/timer.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a Timer.", "[Timer]") {
	Timer timer;
	int interval = 2000;

	SECTION("Verify the interval.") {
		timer.set_interval(interval);
		REQUIRE(timer.get_interval() == interval);
	}

	SECTION("Verify update and last time works.") {
		timer.set_interval(interval);
		REQUIRE(timer.update(interval + 1) == true);
		REQUIRE(timer.get_last_time() == (interval + 1));
	}

	SECTION("Verify start and stop work.") {
		timer.set_interval(interval);
		timer.stop();

		REQUIRE(timer.update(interval + 1) == false);

		timer.start();
		REQUIRE(timer.update(interval + 1) == true);
	}

	SECTION("Verify ups_to_millis returns accurate conversion.", "[int]") {
		REQUIRE(Timer::ups_to_millis(125) == 8);
		REQUIRE(Timer::ups_to_millis(100) == 10);
		REQUIRE(Timer::ups_to_millis(200) == 5);
		REQUIRE(Timer::ups_to_millis(1000) == 1);
		REQUIRE(Timer::ups_to_millis(0.25) == 4000);
	}
}
