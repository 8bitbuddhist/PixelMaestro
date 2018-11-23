#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section* section) : MappedAnimation(section) {
		type_ = AnimationType::Wave;
		map();
	}

	bool WaveAnimation::get_mirror() const {
		return mirror_;
	}

	int8_t WaveAnimation::get_skew() const {
		return skew_;
	}

	void WaveAnimation::set_mirror(bool mirror) {
		this->mirror_ = mirror;
		map();
	}

	void WaveAnimation::set_skew(int8_t skew) {
		this->skew_ = skew;
		map();
	}

	void WaveAnimation::map() {
		if (mirror_) {
			Point center = get_center();
			if (orientation_ == Orientation::Vertical) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					uint16_t count = 0;

					// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
					for (int32_t y = center.y; y >= 0; y--) {
						map_[y][x] = count + (x * skew_);
						count++;
					}

					/*
						Check for an odd number of Pixels.
						If so, set the center one to index 0.
					*/
					uint8_t offset = 0;
					if (section_->get_dimensions()->size() % 2 != 0) {
						offset += 1;
						map_[center.y + offset][x] = (x * skew_);
					}

					offset += 1;

					// Go from the center to the last
					count = 0;
					for (uint16_t y = center.y + offset; y < section_->get_dimensions()->y; y++) {
						map_[y][x] = count + (x * skew_);
						count++;
					}
				}
			}
			else {	// Horizontal
				for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
					uint16_t count = 0;

					// Note: ROW MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
					for (int32_t x = center.x; x >= 0; x--) {
						map_[y][x] = count + (y * skew_);
						count++;
					}

					/*
						Check for an odd number of Pixels.
						If so, set the center one to index 0.
					*/
					uint8_t offset = 0;
					if (section_->get_dimensions()->size() % 2 != 0) {
						offset += 1;
						map_[y][center.x + offset] = y * skew_;
					}

					offset += 1;

					// Go from the center to the last
					count = 0;
					for (uint16_t x = center.x + offset; x < section_->get_dimensions()->x; x++) {
						map_[y][x] = count + (y * skew_);
						count++;
					}
				}
			}
		}
		else {
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					if (orientation_ == Orientation::Vertical) {
						map_[y][x] = y + (x * skew_);
					}
					else {	// Horizontal
						map_[y][x] = x + (y * skew_);
					}
				}
			}
		}
	}

	void WaveAnimation::update() {
		MappedAnimation::update();

		// Rebuild map if the orientation changes.
		if (orientation_ != last_orientation_) {
			map();
			last_orientation_ = orientation_;
		}

		for (uint8_t x = 0; x < dimensions_.x; x++) {
			for (uint8_t y = 0; y < dimensions_.y; y++) {
				section_->set_one(x, y, palette_->get_color_at_index(map_[y][x] + cycle_index_));
			}
		}

		update_cycle(0, palette_->get_num_colors());
	}
}
