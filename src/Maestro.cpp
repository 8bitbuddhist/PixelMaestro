/*
	Maestro.cpp - Library for controlling a collection of Pixels and Sections.
*/

#include "../include/Maestro.h"
#include "../include/Section.h"

namespace PixelMaestro {
	/**
		Returns the number of Sections.

		@return Number of Sections.
	*/
	unsigned short Maestro::getNumSections() {
		return num_sections_;
	}

	/**
		Returns the refresh rate based on the fastest running Section.

		@return Refresh rate of the fastest Section.
	*/
	unsigned short Maestro::getRefreshRate() {
		// Start off at the slowest possible speed
		unsigned short minRefreshRate = 65535;

		// The Maestro must be at least as fast as the fastest animation.
		for (unsigned short section = 0; section < num_sections_; section++) {
			if (sections_[section].getRefreshRate() < minRefreshRate) {
				minRefreshRate = sections_[section].getRefreshRate();
			}
		}

		return minRefreshRate;
	}

	/**
		Returns whether the Maestro is running.

		@return Whether the Maestro is running.
	*/
	bool Maestro::getRunning() {
		return running_;
	}

	/**
		Returns the Section at the specified index.

		@param section Index of the Section to return.
		@return Section at the specified index.
	*/
	Section *Maestro::getSection(unsigned short section) {
		return &sections_[section];
	}

	/**
		Sets the Sections used in the Maestro.

		@param sections Array of Sections.
		@param numSections Number of Sections in the array.
	*/
	void Maestro::setSections(Section *sections, unsigned short numSections) {
		sections_ = sections;
		num_sections_ = numSections;
	}

	/**
		Toggles whether the Maestro is conducting (running).
	*/
	void Maestro::toggleRunning() {
		running_ = !running_;
	}

	/**
		Main update routine.

		@param currentTime Program runtime.
	*/
	void Maestro::update(unsigned long currentTime) {
		// Call each Section's update method.
		if (running_) {
			for (unsigned short section = 0; section < num_sections_; section++) {
				sections_[section].update(currentTime);
			}
		}
	}
}
