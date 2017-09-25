#include "../utility.h"
#include "lightninganimation.h"

namespace PixelMaestro {
	LightningAnimation::LightningAnimation(Colors::RGB* colors, unsigned char num_colors, unsigned short speed, unsigned short pause, unsigned char num_bolts, unsigned char down_threshold, unsigned char up_threshold,  unsigned char fork_chance) : Animation(colors, num_colors, speed, pause) {
		this->num_bolts_ = num_bolts;
		this->down_threshold_ = down_threshold;
		this->up_threshold_ = up_threshold;
		this->fork_chance_ = fork_chance;
	}

	void LightningAnimation::update(Section *section) {
		// Clear the grid
		section->set_all(&Colors::BLACK);

		// Assume horizontal movement. Choose a random point on the y-axis starting at 0, then move from left to right.
		Point start = {0, 0};
		if (orientation_ == Orientation::Vertical) {
			start.set((unsigned short)Utility::rand(section->get_dimensions()->x), 0);
		}
		else {
			start.set(0, (unsigned short)Utility::rand(section->get_dimensions()->y));
		}

		for (unsigned char bolt = 0; bolt < num_bolts_; bolt++) {
			if (orientation_ == Orientation::Vertical) {
				draw_bolt_vertical(bolt, section, &start, down_threshold_, up_threshold_, fork_chance_);
			}
			else {
				draw_bolt_horizontal(bolt, section, &start, down_threshold_, up_threshold_, fork_chance_);
			}
		}

		update_cycle(0, num_colors_);
	}

	void LightningAnimation::draw_bolt_horizontal(unsigned char bolt_num, Section* section, Point* start, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance) {
		unsigned char direction_roll;
		Point cursor = {start->x, start->y};

		/*
		 * Calculate the maximum length of the bolt.
		 * For the main bolt, we set the length equal to the length of the grid.
		 * For off-shoots, we cap the distance at 25% of the grid length.
		 */
		unsigned short length;
		if (cursor.x == 0) {
			length = section->get_dimensions()->x;
		}
		else {
			if ((cursor.x + (section->get_dimensions()->x * 0.25)) > section->get_dimensions()->x) {
				length = section->get_dimensions()->x - cursor.x;
			}
			else {
				length = cursor.x + (section->get_dimensions()->x * 0.25);
			}
		}

		/*
		 * For each step along the grid, roll the dice and compare it to the down/up thresholds.
		 */
		for (unsigned short x = cursor.x; x < length; x++) {
			direction_roll = Utility::rand(255);
			if (direction_roll > up_threshold) {
				if (cursor.y + 1 < section->get_dimensions()->y) {
					cursor.y += 1;
				}
			}
			else if (direction_roll < down_threshold) {
				if (cursor.y - 1 >= 0) {
					cursor.y -= 1;
				}
			}
			cursor.x++;

			section->set_one(x, cursor.y, get_color_at_index(cycle_index_ + bolt_num));


			// Check to see if we should fork the bolt
			if (x < (unsigned short)section->get_dimensions()->x) {
				unsigned char chance_roll = Utility::rand(255);
				if (chance_roll < fork_chance) {
					/*
					 * If we fork, reduce the fork chance by 50%.
					 * We also want to adjust the direction params based on the previous bolt's direction, e.g. if the parent bolt was going up, we want to primarily go down.
					 */
					if (direction_roll > up_threshold) {
						// Default thresholds are 80% and 60%
						draw_bolt_horizontal(bolt_num, section, &cursor, 204, 153, fork_chance / 2);
					}
					else if (direction_roll < down_threshold) {
						draw_bolt_horizontal(bolt_num, section, &cursor, 102, 51, fork_chance / 2);
					}
					else {
						draw_bolt_horizontal(bolt_num, section, &cursor, up_threshold, down_threshold, fork_chance / 2);
					}
				}
			}
		}
	}

	void LightningAnimation::draw_bolt_vertical(unsigned char bolt_num, Section* section, Point* start, unsigned char left_threshold, unsigned char right_threshold, unsigned char fork_chance) {
		unsigned char direction_roll;
		Point cursor = {start->x, start->y};

		/*
		 * Calculate the maximum length of the bolt.
		 * For the main bolt, we set the length equal to the length of the grid.
		 * For off-shoots, we cap the distance at 25% of the grid length.
		 */
		unsigned int length;
		if (cursor.y == 0) {
			length = section->get_dimensions()->y;
		}
		else {
			if (cursor.y + ((section->get_dimensions()->y * 0.25)) > section->get_dimensions()->y) {
				length = section->get_dimensions()->y - cursor.y;
			}
			else {
				length = cursor.y + (section->get_dimensions()->y * 0.25);
			}
		}

		/*
		 * For each step along the grid, roll the dice and compare it to the down/up thresholds.
		 */
		for (unsigned short y = cursor.y; y < length; y++) {
			direction_roll = Utility::rand(255);
			if (direction_roll > right_threshold) {
				if (cursor.x + 1 < section->get_dimensions()->x) {
					cursor.x += 1;
				}
			}
			else if (direction_roll < left_threshold) {
				if (cursor.x - 1 >= 0) {
					cursor.x -= 1;
				}
			}
			cursor.y++;

			section->set_one(cursor.x, y, get_color_at_index(cycle_index_ + bolt_num));

			// Check to see if we should fork the bolt
			if (y < (unsigned short)section->get_dimensions()->y) {
				unsigned char chance_roll = Utility::rand(255);
				if (chance_roll < fork_chance) {
					/*
					 * If we fork, reduce the fork chance by 50%.
					 * We also want to adjust the direction params based on the previous bolt's direction, e.g. if the parent bolt was going up, we want to primarily go down.
					 */
					if (direction_roll > right_threshold) {
						draw_bolt_vertical(bolt_num, section, &cursor, 204, 153, fork_chance / 2);
					}
					else if (direction_roll < left_threshold) {
						draw_bolt_vertical(bolt_num, section, &cursor, 102, 51, fork_chance / 2);
					}
					else {
						draw_bolt_vertical(bolt_num, section, &cursor, right_threshold, left_threshold, fork_chance / 2);
					}
				}
			}
		}
	}

	/**
	 * Returns the number of bolts.
	 * @return Bolt count.
	 */
	unsigned char LightningAnimation::get_bolt_count() {
		return num_bolts_;
	}

	/**
	 * Returns the fork chance.
	 * @return Fork chance.
	 */
	unsigned char LightningAnimation::get_fork_chance() {
		return fork_chance_;
	}

	/**
	 * Returns the down threshold.
	 * @return Down threshold.
	 */
	unsigned char LightningAnimation::get_down_threshold() {
		return down_threshold_;
	}

	/**
	 * Returns the up threshold.
	 * @return Up threshold.
	 */
	unsigned char LightningAnimation::get_up_threshold() {
		return up_threshold_;
	}

	/**
	 * Sets the number of bolts generated in each strike.
	 * @param bolt_count Number of bolts (0 - 255).
	 */
	void LightningAnimation::set_bolt_count(unsigned char bolt_count) {
		this->num_bolts_ = bolt_count;
	}

	/**
	 * Sets the chances of a bolt forking.
	 * @param fork_chance Chance of a bolt forking (0 - 255).
	 */
	void LightningAnimation::set_fork_chance(unsigned char fork_chance) {
		this->fork_chance_ = fork_chance;
	}

	/**
	 * Sets the chances of a bolt drifting in a certain direction.
	 * @param down_threshold Chances of a bolt drifting downwards (left in vertical orientation).
	 * @param up_threshold Chances of a bolt drifting upwards (right in vertical orientation).
	 */
	void LightningAnimation::set_thresholds(unsigned char down_threshold, unsigned char up_threshold) {
		this->down_threshold_ = down_threshold;
		this->up_threshold_ = up_threshold;
	}

	LightningAnimation::~LightningAnimation() {}
}
