/*
 * ShowDemo - Demonstrates a Maestro using a Show.
 */

#include "animation/blinkanimation.h"
#include "animation/cycleanimation.h"
#include "animation/mergeanimation.h"
#include "animation/ponganimation.h"
#include "animation/randomanimation.h"
#include "animation/solidanimation.h"
#include "animation/sparkleanimation.h"
#include "animation/waveanimation.h"
#include "showdemo.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "../drawingarea/simpledrawingarea.h"
#include <memory>
#include "../src/show/sectionsetanimationevent.h"

ShowDemo::ShowDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller_) {
	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(new Point(10, 10));

	SectionController *section_controller = maestro_controller_->get_section_controller(0);

	int num_animations = 8;
	Animation* animations[8] = {
		new SolidAnimation(section_controller->get_section().get()),
		new BlinkAnimation(section_controller->get_section().get()),
		new CycleAnimation(section_controller->get_section().get()),
		new WaveAnimation(section_controller->get_section().get()),
		new PongAnimation(section_controller->get_section().get()),
		new MergeAnimation(section_controller->get_section().get()),
		new RandomAnimation(section_controller->get_section().get()),
		new SparkleAnimation(section_controller->get_section().get())
	};

	for (unsigned int index = 0; index < num_animations; index++) {
		animations[index]->set_colors(Colors::COLORWHEEL, 12);
	}

	//section_controller->get_section()->set_cycle_interval(300);

	/*
	 * Initialize Event.
	 * This show has just one Event, which simply changes to the next animation every 5 seconds.
	 */
	events_.push_back(new SectionSetAnimationEvent(5000, section_controller->get_section().get(), animations[0], num_animations));

	maestro_controller_->add_show(&events_[0], events_.size(), Show::TimingModes::RELATIVE, true);
}
