/*
	Maestro.cpp - Library for controlling a collection of Pixels and Sections.
*/

#include <stdint.h>
#include "../utility.h"
#include "maestro.h"
#include "section.h"

namespace PixelMaestro {

	/**
	 * Constructor. Creates the Maestro with the specified Sections.
	 * @param sections Array of Sections to manage.
	 * @param num_sections Number of Sections in the array.
	 */
	Maestro::Maestro(Section* sections, uint8_t num_sections) {
		set_sections(sections, num_sections);
	}

	/**
	 * Returns the active Cue controller.
	 * @return Cue controller.
	 */
	CueController* Maestro::get_cue_controller() {
		return cue_controller_;
	}

	/**
		Returns the number of Sections.

		@return Number of Sections.
	*/
	uint8_t Maestro::get_num_sections() {
		return num_sections_;
	}

	/**
	 * Returns the color of the specified Pixel in the specified Section after applying post-processing.
	 * @param section Section to retrieve the Pixel from.
	 * @param pixel Index of the Pixel to retrieve.
	 * @return Pixel color after adjusting for Overlays and brightness.
	 */
	Colors::RGB Maestro::get_pixel_color(uint8_t section, uint32_t pixel) {
		return sections_[section].get_pixel_color(pixel) * (float)(brightness_ / (float)255);
	}

	/**
		Returns the Maestro's refresh interval.

		@return Amount of time between refreshes (in ms).
	*/
	uint16_t Maestro::get_refresh_interval() {
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
	Section* Maestro::get_section(uint8_t section) {
		return &sections_[section];
	}

	/**
	 * Returns the current Show.
	 * @return Active Show.
	 */
	Show* Maestro::get_show() {
		return show_;
	}

	/**
	 * Sets the Maestro's global brightness level.
	 * @param brightness Brightness level from 0 (off) to 255 (full).
	 */
	void Maestro::set_brightness(uint8_t brightness) {
		brightness_ = brightness;
	}

	/**
	 * Sets a new Cue controller, or returns the current Controller if one is already set.
	 * @return New Cue controller.
	 */
	CueController* Maestro::set_cue_controller() {
		if (cue_controller_ == nullptr) {
			cue_controller_ = new CueController(this);
		}

		return cue_controller_;
	}

	/**
	 * Sets the Maestro's refresh interval.
	 * @param interval New refresh interval.
	 */
	void Maestro::set_refresh_interval(uint16_t interval)	{
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
	void Maestro::set_sections(Section* sections, uint8_t num_sections) {
		sections_ = sections;
		num_sections_ = num_sections;

		for (uint8_t section = 0; section < num_sections; section++) {
			sections_[section].set_refresh_interval(&refresh_interval_);
		}
	}

	/**
	 * Sets a new Show.
	 * If a Show already exists, this updates the existing Show with the new Event list.
	 * This also initializes a CueController if one does not already exist.
	 *
	 * @param events Events used in the Show.
	 * @param num_events The number of Events.
	 * @return New Show.
	 */
	Show* Maestro::set_show(Event* events, uint16_t num_events) {
		if (show_ == nullptr) {
			show_ = new Show(set_cue_controller(), events, num_events);
		}
		else {
			show_->set_events(events, num_events);
		}

		return show_;
	}

	/**
		Main update routine.

		@param current_time Program runtime.
	*/
	void Maestro::update(const uint32_t& current_time) {
		// If running, call each Section's update method.
		if (running_) {

			// Compare the refresh time to the time since the last refresh.
			if (current_time - last_refresh_ >= (uint32_t)refresh_interval_) {

				// Run the Show
				if (show_) {
					show_->update(current_time);
				}

				// Update each Section
				for (uint8_t section = 0; section < num_sections_; section++) {
					sections_[section].update(current_time);
				}

				// Update the last refresh time.
				last_refresh_ = current_time;
			}
		}
	}

	Maestro::~Maestro() {
		delete cue_controller_;
		delete show_;
	}
}
