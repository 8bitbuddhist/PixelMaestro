#include "../utility.h"
#include "lightninganimation.h"

namespace PixelMaestro {
	LightningAnimation::LightningAnimation(unsigned char num_bolts, unsigned char down_threshold, unsigned char up_threshold,  unsigned char fork_chance, Colors::RGB* colors, unsigned short num_colors) {
		this->num_bolts_ = num_bolts;
		this->down_threshold_ = down_threshold;
		this->up_threshold_ = up_threshold;
		this->fork_chance_ = fork_chance;
	}

	void LightningAnimation::update(Section *section) {
		// Clear the grid
		section->set_all(&Colors::BLACK);

		// Assume horizontal movement. Choose a random point on the y-axis starting at 0, then move from left to right.
		Point start = {0, (short)Utility::rand(section->get_dimensions()->y)};

		for (unsigned short bolt = 0; bolt < num_bolts_; bolt++) {
			draw_bolt(section, &start, up_threshold_, down_threshold_, fork_chance_);
		}

		update_cycle(0, num_colors_);
	}

	void LightningAnimation::draw_bolt(Section* section, Point* start, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance) {
		int direction_roll;
		Point cursor = {start->x, start->y};

		/*
		 * For each increment in x-axis, roll the dice and compare it to the down/up thresholds.
		 * For off-shoots, we cap the distance at 25% of the grid length.
		 */
		unsigned int length;
		if (cursor.x == 0) {	// If x==0, then this is the initial/main bolt.
			length = section->get_dimensions()->x;
		}
		else {
			if (cursor.x + ((section->get_dimensions()->x * 0.25)) > section->get_dimensions()->x) {
				length = section->get_dimensions()->x - cursor.x;
			}
			else {
				length = cursor.x + (section->get_dimensions()->x * 0.25);
			}
		}
		for (unsigned int x = cursor.x; x < length; x++) {
			direction_roll = Utility::rand(100);
			if (direction_roll > up_threshold) {
				if (cursor.y + 1 < section->get_dimensions()->y) {
					cursor.y += 1;
				}
			}
			else if (direction_roll < down_threshold) {
				if (cursor.y - 1 >= 0) {
					cursor.y -=1;
				}
			}
			cursor.x++;

			section->set_one(x, cursor.y, &colors_[cycle_index_]);

			// Check to see if we should fork the bolt
			if (x < (unsigned short)section->get_dimensions()->x) {
				int chance_roll = Utility::rand(100);
				if (chance_roll < fork_chance) {
					// FIXME: Can only draw bolts in one direction
					/*
					 * If we fork, reduce the fork chance by 50%.
					 * We also want to adjust the direction params based on the previous bolt's direction, e.g. if the parent bolt was going up, we want to primarily go down.
					 */
					if (direction_roll > up_threshold) {
						draw_bolt(section, &cursor, up_threshold, down_threshold + 40, fork_chance / 2);
					}
					//else if (direction_roll < down_threshold) {
					else {
						draw_bolt(section, &cursor, up_threshold - 40, down_threshold, fork_chance / 2);
					}
					/*else {
						draw_bolt(section, &cursor, up_threshold, down_threshold, fork_chance / 2);
					}*/
				}
			}
		}
	}
}
