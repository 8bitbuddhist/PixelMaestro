/*
	Maestro.cpp - Library for controlling a collection of Pixels and Sections.
*/

#include "maestro.h"
#include "section.h"

namespace PixelMaestro {
	/**
		Returns the number of Sections.

		@return Number of Sections.
	*/
	unsigned short Maestro::get_num_sections() {
		return num_sections_;
	}

	/**
		Returns the refresh rate based on the fastest running Section.

		@return Refresh rate of the fastest Section.
	*/
	unsigned short Maestro::get_refresh_rate() {
		// Start off at the slowest possible speed
		unsigned short min_refresh_rate = 65535;

		// The Maestro must be at least as fast as the fastest animation.
		for (unsigned short section = 0; section < num_sections_; section++) {
			if (sections_[section].get_refresh_interval() < min_refresh_rate) {
				min_refresh_rate = sections_[section].get_refresh_interval();
			}
		}

		return min_refresh_rate;
	}

	/**
		Returns whether the Maestro is running.

		@return Whether the Maestro is running.
	*/
	bool Maestro::get_running() {
		return running_;
	}

	/**
		Returns the Section at the specified index.

		@param section Index of the Section to return.
		@return Section at the specified index.
	*/
	Section* Maestro::get_section(unsigned short section) {
		return &sections_[section];
	}

	/**
		Sets the Sections used in the Maestro.

		@param sections Array of Sections.
		@param num_sections Number of Sections in the array.
	*/
	void Maestro::set_sections(Section* sections, unsigned short num_sections) {
		sections_ = sections;
		num_sections_ = num_sections;
	}

	/**
		Toggles whether the Maestro is conducting (running).
	*/
	void Maestro::toggle_running() {
		running_ = !running_;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Maestro::update(const unsigned long& current_time) {
		// Call each Section's update method.
		if (running_) {
			for (unsigned short section = 0; section < num_sections_; section++) {
				sections_[section].update(current_time);
			}
		}
	}
}
