/*
	Maestro.cpp - Library for controlling a collection of Pixels and Sections.
*/

#include "../utility.h"
#include "maestro.h"
#include "section.h"

namespace PixelMaestro {

	/**
	 * Constructor. Creates the Maestro with the specified Sections.
	 * @param sections Array of Sections to manage.
	 * @param num_sections Number of Sections in the array.
	 */
	Maestro::Maestro(Section* sections, unsigned char num_sections) {
		set_sections(sections, num_sections);
	}

	/**
		Returns the number of Sections.

		@return Number of Sections.
	*/
	unsigned char Maestro::get_num_sections() {
		return num_sections_;
	}

	/**
	 * Returns the color of the specified Pixel in the specified Section after applying post-processing.
	 * @param section Section to retrieve the Pixel from.
	 * @param pixel Index of the Pixel to retrieve.
	 * @return Pixel color after adjusting for Overlays and brightness.
	 */
	Colors::RGB Maestro::get_pixel_color(unsigned char section, unsigned int pixel) {
		return sections_[section].get_pixel_color(pixel) * brightness_;
	}

	/**
		Returns the Maestro's refresh interval.

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
	Section* Maestro::get_section(unsigned char section) {
		return &sections_[section];
	}

	/**
	 * Sets the Maestro's global brightness level.
	 * @param brightness Brightness level from 0.0 (completely dark) to 1.0 (completely lit).
	 */
	void Maestro::set_brightness(float brightness) {
		if (brightness < 0.0) {
			brightness_ = 0.0;
		}
		else if (brightness > 1.0) {
			brightness_ = 1.0;
		}
		else {
			brightness_ = brightness;
		}
	}

	/**
	 * Sets the Maestro's refresh interval.
	 * @param interval New refresh interval.
	 */
	void Maestro::set_refresh_interval(unsigned short interval)	{
		refresh_interval_ = interval;
	}

	/**
		Sets whether the Maestro is running.

		@param running Whether or not the Maestro is running.
	*/
	void Maestro::set_running(bool running) {
		running_ = running;
	}

	/**
		Sets the Sections used in the Maestro.

		@param sections Array of Sections.
		@param num_sections Number of Sections in the array.
	*/
	void Maestro::set_sections(Section* sections, unsigned char num_sections) {
		sections_ = sections;
		num_sections_ = num_sections;

		for (unsigned char section = 0; section < num_sections; section++) {
			sections_[section].set_refresh_interval(&refresh_interval_);
		}
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Maestro::update(const unsigned long& current_time) {
		// If running, call each Section's update method.
		if (running_) {

			/*
			 * Refresh the Pixels.
			 * refresh_interval_ tracks the amount of time between Pixel draws, and last_refresh_ tracks the time of the last refresh.
			 */
			if (current_time - last_refresh_ >= (unsigned long)refresh_interval_) {
				for (unsigned char section = 0; section < num_sections_; section++) {
					sections_[section].update(current_time);
				}

				// Update the last refresh time.
				last_refresh_ = current_time;
			}
		}
	}
}
