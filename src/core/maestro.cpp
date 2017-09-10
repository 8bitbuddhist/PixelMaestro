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
		Returns the refresh interval.

		@return Amount of time between refreshes (in ms).
	*/
	unsigned short Maestro::get_refresh_interval() {
		return refresh_interval_;
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
		Sets whether the Maestro is running.

		@param running Whether or not the Maestro is running.
	*/
	void Maestro::set_running(bool running) {
		running_ = running;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Maestro::update(const unsigned long& current_time) {
		// If running, call each Section's update method.
		if (running_) {
			for (unsigned short section = 0; section < num_sections_; section++) {
				sections_[section].update(current_time);
			}
		}
	}
}
