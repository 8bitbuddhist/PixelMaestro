#ifndef ANIMATIONTIMERTEST_H
#define ANIMATIONTIMERTEST_H

class AnimationTimerTest {
	public:
		AnimationTimerTest();

	protected:

	private:
};

#endif // ANIMATIONTIMERTEST_H

#include "../catch/single_include/catch.hpp"
#include "../../src/animation/blinkanimation.h"
#include "../../src/core/maestro.h"
#include "../../src/core/section.h"
#include "../../src/core/timer/animationtimer.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate an Animation Timer.", "[Animation Timer]") {
	Section sections[] {
		Section(10, 10)
	};

	Maestro maestro = Maestro(sections, 1);
	Section* section = maestro.get_section(0);
	BlinkAnimation* animation = dynamic_cast<BlinkAnimation*>(section->set_animation(AnimationType::Blink));

	AnimationTimer timer = AnimationTimer(*animation);
	int interval = 4000;
	int delay = 1000;

	timer.set_interval(interval);

	SECTION("Verify interval works.") {
		REQUIRE(timer.update(interval + 1) == true);
		REQUIRE(timer.get_last_time() == (interval + 1));
	}

	SECTION("Verify delay works.") {
		timer.set_interval(interval, delay);
		REQUIRE(timer.update(interval + 1) == false);
		REQUIRE(timer.update(interval + delay + 1) == true);
	}

	SECTION("Verify step count recalculation.") {
		animation->set_fade(true);

		timer.recalculate_step_count();
		REQUIRE(timer.get_step_count() == interval / (float)maestro.get_timer()->get_interval());
	}
}
