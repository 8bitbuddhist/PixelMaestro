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

ShowDemo::ShowDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(new Point(10, 10));

	SectionController *section_controller = maestro_controller_->get_section_controller(0);

	animations_.push_back(new SolidAnimation(section_controller->get_section().get()));
	animations_.push_back(new BlinkAnimation(section_controller->get_section().get()));
	animations_.push_back(new CycleAnimation(section_controller->get_section().get()));
	animations_.push_back(new WaveAnimation(section_controller->get_section().get()));
	animations_.push_back(new PongAnimation(section_controller->get_section().get()));
	animations_.push_back(new MergeAnimation(section_controller->get_section().get()));
	animations_.push_back(new RandomAnimation(section_controller->get_section().get()));
	animations_.push_back(new SparkleAnimation(section_controller->get_section().get()));

	for (unsigned int index = 0; index < animations_.size(); index++) {
		animations_[index]->set_colors(Colors::COLORWHEEL, 12);
	}

	//section_controller->get_section()->set_cycle_interval(300);

	/*
	 * Initialize Event.
	 * This show has just one Event, which simply changes to the next animation every 5 seconds.
	 */
	events_.push_back(new SectionSetAnimationEvent(5000, section_controller->get_section().get(), &animations_[0], animations_.size()));

	maestro_controller_->add_show(&events_[0], events_.size(), Show::TimingModes::RELATIVE, true);
}
