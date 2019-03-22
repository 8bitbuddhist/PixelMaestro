#include "../utility.h"
#include "lightninganimation.h"

namespace PixelMaestro {
	LightningAnimation::LightningAnimation(Section* section) : Animation(section) {
		type_ = AnimationType::Lightning;
	}

	void LightningAnimation::update() {
		// Clear the grid
		for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				section_->set_one(x, y, &black_, timer_->get_step_count());
			}
		}

		/*
		 * Assume horizontal movement. Choose a random point on the y-axis starting at 0, then move from left to right.
		 * "102" is the maximum length of the grid that a single fork can cover (102 equates to 40%).
		 */
		Point start = {0, 0};
		for (uint8_t bolt = 0; bolt < num_bolts_; bolt++) {
			if (orientation_ == Orientation::Vertical) {
				start.set((uint16_t)Utility::rand(section_->get_dimensions()->x), 0);
				draw_bolt_vertical(bolt, &start, drift_, fork_chance_, 102);
			}
			else {
				start.set(0, (uint16_t)Utility::rand(section_->get_dimensions()->y));
				draw_bolt_horizontal(bolt, &start, drift_, fork_chance_, 102);
			}
		}

		update_cycle(0, palette_->get_num_colors());
	}

	/**
	 * Draw a horizontal bolt.
	 * @param bolt_num The bolt's number in the drawing order.
	 * @param start The bolt's starting location.
	 * @param drift The chance/direction that the bolt will drift in.
	 * @param fork_chance The chance that the bolt will fork.
	 * @param max_fork_length The max length of the bolt's fork, if it does fork.
	 */
	void LightningAnimation::draw_bolt_horizontal(uint8_t bolt_num, Point* start, int8_t drift, uint8_t fork_chance, uint8_t max_fork_length) {
		Point cursor = {start->x, start->y};

		/*
		 * Calculate the maximum length of the bolt.
		 * For the main bolt, we set the length equal to the length of the grid.
		 * For forks, we cap the distance at a percentage of the grid length (calculated using max_fork_length).
		 */
		uint16_t length;
		if (cursor.x == 0) {
			length = section_->get_dimensions()->x;
		}
		else {
			if ((cursor.x + (section_->get_dimensions()->x * (max_fork_length / (float)100))) > section_->get_dimensions()->x) {
				length = section_->get_dimensions()->x - cursor.x;
			}
			else {
				length = cursor.x + (section_->get_dimensions()->x * (max_fork_length / (float)100));
			}
		}

		/*
		 * For each step along the grid, generate a random number and compare it to the drift threshold.
		 * This determines the direction that the bolt moves in.
		 */
		for (uint16_t x = cursor.x; x < length; x++) {
			int8_t drift_roll = Utility::rand(UINT8_MAX) - INT8_MAX;
			if (drift_roll > drift) {
				if (cursor.y + 1 < section_->get_dimensions()->y) {
					cursor.y += 1;
				}
			}
			else {
				if (cursor.y - 1 >= 0) {
					cursor.y -= 1;
				}
			}
			cursor.x++;

			section_->set_one(x, cursor.y, palette_->get_color_at_index(cycle_index_ + bolt_num), timer_->get_step_count());

			// Check to see if we should fork the bolt.
			if (x < (uint16_t)section_->get_dimensions()->x) {
				uint8_t fork_roll = Utility::rand(UINT8_MAX);
				if (fork_roll < fork_chance) {

					/*
					 * If we forked...
					 *	1) Change the drift so that it sends the bolt away from the parent. We do this by increasing the drift threshold to 85% in the opposite direciton, making it extremely likely that the bolt will move that way.
					 *	2) Reduce the chance of another fork by 50%.
					 *	3) Reduce the length of the next fork by a random amount. We don't want forks longer than their parents.
					 */
					if (drift_roll < drift) {
						draw_bolt_horizontal(bolt_num, &cursor, 90, fork_chance / 2, Utility::rand(max_fork_length));
					}
					else {
						// Invert threshold
						draw_bolt_horizontal(bolt_num, &cursor, -90, fork_chance / 2, Utility::rand(max_fork_length));
					}
				}
			}
		}
	}

	/**
	 * Draws a vertical bolt. See draw_horizontal_fork() for comments.
	 * @param bolt_num The bolt's number in the drawing order.
	 * @param start The bolt's starting location.
	 * @param drift The chance/direction that the bolt will drift in.
	 * @param fork_chance The chance that the bolt will fork.
	 * @param max_fork_length The max length of the bolt's fork, if it does fork.
	 */
	void LightningAnimation::draw_bolt_vertical(uint8_t bolt_num, Point* start, int8_t drift, uint8_t fork_chance, uint8_t max_fork_length) {
		Point cursor = {start->x, start->y};

		uint32_t length;
		if (cursor.y == 0) {
			length = section_->get_dimensions()->y;
		}
		else {
			if (cursor.y + ((section_->get_dimensions()->y * (max_fork_length / (float)100))) > section_->get_dimensions()->y) {
				length = section_->get_dimensions()->y - cursor.y;
			}
			else {
				length = cursor.y + (section_->get_dimensions()->y * (max_fork_length / (float)100));
			}
		}

		for (uint16_t y = cursor.y; y < length; y++) {
			int8_t drift_roll = Utility::rand(UINT8_MAX) - INT8_MAX;
			if (drift_roll < drift) {	// Intentionally inverted from draw_bolt_horizontal.
				if (cursor.x + 1 < section_->get_dimensions()->x) {
					cursor.x += 1;
				}
			}
			else {
				if (cursor.x - 1 >= 0) {
					cursor.x -= 1;
				}
			}
			cursor.y++;

			section_->set_one(cursor.x, y, palette_->get_color_at_index(cycle_index_ + bolt_num), timer_->get_step_count());

			if (y < (uint16_t)section_->get_dimensions()->y) {
				uint8_t fork_roll = Utility::rand(UINT8_MAX);
				if (fork_roll < fork_chance) {
					if (drift_roll > drift) {
						draw_bolt_vertical(bolt_num, &cursor, 90, fork_chance / 2, Utility::rand(max_fork_length));
					}
					else {
						draw_bolt_vertical(bolt_num, &cursor, -90, fork_chance / 2, Utility::rand(max_fork_length));
					}
				}
			}
		}
	}

	/**
	 * Returns the number of bolts.
	 * @return Bolt count.
	 */
	uint8_t LightningAnimation::get_bolt_count() const {
		return num_bolts_;
	}

	/**
	 * Returns the fork chance.
	 * @return Fork chance.
	 */
	uint8_t LightningAnimation::get_fork_chance() const {
		return fork_chance_;
	}

	/**
	 * Returns the amount of drift.
	 * @return Drift amount.
	 */
	int8_t LightningAnimation::get_drift() const {
		return drift_;
	}

	/**
	 * Sets the number of bolts generated in each strike.
	 * @param bolt_count Number of bolts (0 - 255).
	 */
	void LightningAnimation::set_bolt_count(uint8_t bolt_count) {
		this->num_bolts_ = bolt_count;
	}

	/**
	 * Sets the chances of a bolt forking.
	 * @param fork_chance Chance of a bolt forking (0 - 255).
	 */
	void LightningAnimation::set_fork_chance(uint8_t fork_chance) {
		this->fork_chance_ = fork_chance;
	}

	/**
	 * Sets the amount of drift.
	 * Negative values increase the amount of negative drift (left or down).
	 * Positive values increase the amount of positive drift (right or up).
	 * @param drift Drift amount.
	 */
	void LightningAnimation::set_drift(int8_t drift) {
		this->drift_ = drift;
	}
}
