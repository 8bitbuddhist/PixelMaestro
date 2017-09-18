#include "../core/section.h"
#include "sectionsetcycleintervalevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Changes a Section's cycle interval.
	 * @param time Time until the Event runs.
	 * @param section Section to update.
	 * @param interval New interval to set.
	 * @param pause Pause interval.
	 */
	SectionSetCycleIntervalEvent::SectionSetCycleIntervalEvent(unsigned long time, Section* section, unsigned short interval, unsigned short pause) : Event(time) {
		this->section_ = section;
		this->interval_ = interval;
		this->pause_ = pause;
	}

	void SectionSetCycleIntervalEvent::run() {
		section_->set_cycle_interval(interval_, pause_);
	}
}
