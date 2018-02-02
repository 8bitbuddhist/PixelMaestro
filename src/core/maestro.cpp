/*
	Maestro.cpp - Library for controlling a collection of Pixels and Sections.
*/

#include <stdint.h>
#include "../utility.h"
#include "maestro.h"
#include "section.h"

namespace PixelMaestro {

	/**
	 * Constructor. Fast-tracks creating a Maestro with a single Section.
	 * Note: The new Section is dynamically allocated. You will need to manually call delete once you're done using it.
	 * @param rows Number of rows in the new Section.
	 * @param columns Number of columns in the new Section.
	 */
	Maestro::Maestro(uint16_t rows, uint16_t columns) {
		Section* sections = new Section[1] {
			Section(rows, columns)
		};
		set_sections(sections, 1);
	}

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
	CueController* Maestro::get_cue_controller() const {
		return cue_controller_;
	}

	/**
		Returns the number of Sections.

		@return Number of Sections.
	*/
	uint8_t Maestro::get_num_sections() const {
		return num_sections_;
	}

	/**
	 * Returns the color of the specified Pixel in the specified Section after applying post-processing.
	 * @param section Section to retrieve the Pixel from.
	 * @param x Pixel's x-coordinate.
	 * @param y Pixel's y-coordinate.
	 * @return Pixel color after adjusting for Layers and brightness.
	 */
	Colors::RGB Maestro::get_pixel_color(uint8_t section, uint16_t x, uint16_t y) const {
		return sections_[section].get_pixel_color(x, y) * (float)(brightness_ / (float)255);
	}

	/**
		Returns the Section at the specified index.

		@param section Index of the Section to return.
		@return Section at the specified index.
	*/
	Section* Maestro::get_section(uint8_t section) const {
		if (section >= num_sections_) {
			return nullptr;
		}

		return &sections_[section];
	}

	/**
	 * Returns the current Show.
	 * @return Active Show.
	 */
	Show* Maestro::get_show() const {
		return show_;
	}

	/**
	 * Gets the Maestro's update timing.
	 * @return Maestro timing.
	 */
	Timing* Maestro::get_timing() const {
		return const_cast<Timing*>(&timing_);
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
	 * @param buffer_size The size of the CueController buffer (defaults to 256).
	 * @return New Cue controller.
	 */
	CueController* Maestro::set_cue_controller(uint16_t buffer_size) {
		if (cue_controller_ == nullptr) {
			cue_controller_ = new CueController(this, buffer_size);
		}

		return cue_controller_;
	}

	/**
		Sets the Sections used in the Maestro.

		@param sections Array of Sections.
		@param num_sections Number of Sections in the array.
	*/
	void Maestro::set_sections(Section* sections, uint8_t num_sections) {
		sections_ = sections;
		num_sections_ = num_sections;

		for (uint16_t section = 0; section < num_sections; section++) {
			sections_[section].set_maestro(this);
		}
	}

	/**
	 * Creates a new Show with the specified Event list.
	 * If a Show already exists, this updates the existing Show with the new Event list.
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
	 * Sets the interval between Maestro updates.
	 * @param interval Update interval.
	 * @return New Maestro timing.
	 */
	Timing* Maestro::set_timing(uint16_t interval) {
		timing_.set_interval(interval);
		return &timing_;
	}

	/**
	 * Sets each component's last refresh time (including the Maestro itself).
	 * @param new_time The new refresh time. Leave blank to set to 0.
	 */
	void Maestro::sync(const uint32_t& new_time) {
		this->get_timing()->set_last_time(new_time);
		for (uint8_t section = 0; section < num_sections_; section++) {
			sections_[section].sync(new_time);
		}
	}

	/**
		Main update routine.

		@param current_time Current program runtime.
		@param force If true, bypass the refresh interval check and force the Maestro to update.
		@return True if the Maestro has changed.
	*/
	bool Maestro::update(const uint32_t& current_time, bool force) {
		// Update if the time is exceeded or if force is true
		if (timing_.update(current_time) || force) {
			// Run the Show
			if (show_) {
				show_->update(current_time);
			}

			// Update each Section
			for (uint8_t section = 0; section < num_sections_; section++) {
				sections_[section].update(current_time);
			}

			return true;
		}

		return false;
	}

	Maestro::~Maestro() {
		delete cue_controller_;
		delete show_;
	}
}
