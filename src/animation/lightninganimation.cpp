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
		// TODO: For some reason, this only works when fading
		// Clear the grid
		section->set_all(&Colors::BLACK);

		// Assume horizontal movement. Choose a random point on the y-axis starting at 0, then move from left to right.
		Point start = {0, Utility::rand(section->get_dimensions()->y)};

		for (unsigned short bolt = 0; bolt < num_bolts_; bolt++) {
			draw_bolt(section, &start, fork_chance_);
		}

		update_cycle(0, num_colors_);
	}

	void LightningAnimation::draw_bolt(Section* section, Point* start, unsigned char fork_chance) {
		int roll;
		Point cursor = {start->x, start->y};

		/*
		 * For each increment in x-axis, roll the dice and compare it to the down/up thresholds.
		 * For off-shoots, we cap the distance at 10% of the distance of the grid.
		 */
		unsigned int max_length;
		if (cursor.x == 0) {	// If x==0, then this is the initial/main bolt.
			max_length = section->get_dimensions()->x;
		}
		else {
			max_length = section->get_dimensions()->x * 0.1;
		}
		for (unsigned int x = cursor.x; x < max_length; x++) {
			roll = Utility::rand(100);
			if (roll > up_threshold_) {
				if (cursor.y + 1 < section->get_dimensions()->y) {
					cursor.y += 1;
				}
			}
			else if (roll < down_threshold_) {
				if (cursor.y - 1 >= 0) {
					cursor.y -=1;
				}
			}
			cursor.x++;

			section->set_one(x, cursor.y, &colors_[cycle_index_]);

			// Check to see if we should fork the bolt
			if (x != max_length) {
				roll = Utility::rand(100);
				if (roll < fork_chance) {
					// TODO: Handle bolts correctly
					// If we fork, reduce the fork chance by 50%.
					draw_bolt(section, &cursor, fork_chance / 2);
				}
			}
		}
	}
}
