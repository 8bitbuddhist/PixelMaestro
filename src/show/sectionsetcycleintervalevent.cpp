#include "../section.h"
#include "sectionsetcycleintervalevent.h"

using namespace PixelMaestro;

namespace PixelMaestro {
	SectionSetCycleIntervalEvent::SectionSetCycleIntervalEvent(unsigned long time, Section* section, unsigned short interval, unsigned short pause) : Event(time) {
		this->section_ = section;
		this->interval_ = interval;
		this->pause_ = pause;
	}

	void SectionSetCycleIntervalEvent::run() {
		section_->set_cycle_interval(interval_, pause_);
	}
}
