/*
	Maestro.cpp - Library for controlling a collection of Pixels and Sections.
*/

#include <stdint.h>
#include "../utility.h"
#include "maestro.h"
#include "section.h"

namespace PixelMaestro {

	/**
	 * Constructor. Creates a Maestro with the designated dimensions and Section count.
	 *
	 * @param rows Number of rows in the new Sections.
	 * @param columns Number of columns in the new Sections.
	 * @param num_sections Number of Sections to create.
	 */
	Maestro::Maestro(uint16_t rows, uint16_t columns, uint8_t num_sections) {
		Section* sections = new Section[num_sections] {
			Section(rows, columns)
		};
		set_sections(sections, num_sections);

		dynamically_allocated_sections_ = true;
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
	CueController& Maestro::get_cue_controller() const {
		return *cue_controller_;
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
		return sections_[section].get_pixel_color(x, y);
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
		else {
			return &sections_[section];
		}
	}

	/**
	 * Returns the current Show.
	 * @return Active Show.
	 */
	Show* Maestro::get_show() const {
		return show_;
	}

	/**
	 * Gets the Maestro's update timer.
	 * @return Maestro timer.
	 */
	Timer& Maestro::get_timer() const {
		return const_cast<Timer&>(timer_);
	}

	/**
	 * Deletes and dereferences the Sections array.
	 */
	void Maestro::remove_sections() {
		if (dynamically_allocated_sections_) {
			delete [] sections_;
		}
		sections_ = nullptr;
	}

	/**
	 * Deletes the active Show.
	 */
	void Maestro::remove_show() {
		delete show_;
		show_ = nullptr;
	}

	/**
	 * Sets the global brightness level for all Sections simultaneously.
	 * @param brightness Brightness level from 0 (off) to 255 (full).
	 */
	void Maestro::set_brightness(uint8_t brightness) {
		for (uint8_t section = 0; section < num_sections_; section++) {
			sections_[section].set_brightness(brightness);
		}
	}

	/**
	 * Sets a new Cue controller, or returns the current Controller if one is already set.
	 * @param buffer_size The size of the CueController buffer (defaults to 256).
	 * @return New Cue controller.
	 */
	CueController& Maestro::set_cue_controller(uint16_t buffer_size) {
		if (cue_controller_ == nullptr) {
			cue_controller_ = new CueController(*this, buffer_size);
		}

		return *cue_controller_;
	}

	/**
		Sets the Sections used in the Maestro.
		If there are dynamically allocated Sections, they will be deleted.

		@param sections Array of Sections.
		@param num_sections Number of Sections in the array.
	*/
	void Maestro::set_sections(Section* sections, uint8_t num_sections) {
		remove_sections();

		sections_ = sections;
		num_sections_ = num_sections;

		for (uint16_t section = 0; section < num_sections; section++) {
			sections_[section].set_maestro(*this);
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
	Show& Maestro::set_show(Event* events, uint16_t num_events) {
		if (show_ == nullptr) {
			show_ = new Show(set_cue_controller(), events, num_events);
		}
		else {
			show_->set_events(events, num_events);
		}

		return *show_;
	}

	/**
	 * Sets the interval between Maestro updates.
	 * @param interval Update interval.
	 * @return Maestro timer.
	 */
	Timer& Maestro::set_timer(uint16_t interval) {
		timer_.set_interval(interval);
		return timer_;
	}

	/**
	 * Sets each component's last refresh time (including the Maestro itself).
	 * @param new_time The new refresh time. Leave blank to set to 0.
	 */
	void Maestro::sync(const uint32_t& new_time) {
		this->get_timer().set_last_time(new_time);
		for (uint8_t section = 0; section < num_sections_; section++) {
			sections_[section].sync(new_time);
		}

		if (show_ != nullptr) {
			show_->sync(new_time);
		}
	}

	/**
		Main update routine.

		@param current_time Current program runtime.
		@param force If true, bypass the refresh interval check and force the Maestro to update.
		@return True if the Maestro has changed.
	*/
	bool Maestro::update(const uint32_t& current_time, bool force) {
		uint32_t last_time = timer_.get_last_time();

		// Update if the time is exceeded or if force is true
		if (timer_.update(current_time) || force) {

			/*
			 * To account for lag, check to see how many times the Maestro should be updated.
			 * First, derive the number of updates that should've run from the last time and interval.
			 * For each update, multiply the update num by the interval and add this to the last time to get what should have been the current_time for that update, then store this in new_time.
			 * Then, pass new_time to each component and continue the loop.
			 */

			uint16_t num_updates = (current_time - last_time) / timer_.get_interval();
			uint16_t i = 1;

			do {
				uint32_t new_time = timer_.get_last_time() + (timer_.get_interval() * i);

				// Run the Show
				if (show_) {
					show_->update(new_time);
				}

				// Update each Section
				for (uint8_t section = 0; section < num_sections_; section++) {
					sections_[section].update(new_time);
				}
				++i;
			}
			while (i <= num_updates);

			return true;
		}

		return false;
	}

	Maestro::~Maestro() {
		delete cue_controller_;
		remove_show();

		remove_sections();
	}
}
