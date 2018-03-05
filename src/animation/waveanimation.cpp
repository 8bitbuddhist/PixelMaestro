#include "waveanimation.h"

namespace PixelMaestro {
	WaveAnimation::WaveAnimation(Section* section) : Animation(section) {
		type_ = AnimationType::Wave;
	}

	bool WaveAnimation::get_mirror() const {
		return mirror_;
	}

	int8_t WaveAnimation::get_skew() const {
		return skew_;
	}

	void WaveAnimation::set_mirror(bool mirror) {
		this->mirror_ = mirror;
	}

	void WaveAnimation::set_skew(int8_t skew) {
		this->skew_ = skew;
	}

	void WaveAnimation::update() {
		if (mirror_) {
			Point center = get_center();
			if (orientation_ == Orientation::Vertical) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					uint16_t count = 0;

					// Note: COLUMN MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
					for (int32_t y = center.y; y >= 0; y--) {
						section_->set_one(x, y, palette_->get_color_at_index(count + cycle_index_ + (x * skew_)));
						count++;
					}

					/*
						Check for an odd number of Pixels.
						If so, set the center one to index 0.
					*/
					uint8_t offset = 0;
					if (section_->get_dimensions()->size() % 2 != 0) {
						offset += 1;
						section_->set_one(x, center.y + offset, palette_->get_color_at_index(cycle_index_ + (x * skew_)));
					}

					offset += 1;

					// Go from the center to the last
					count = 0;
					for (uint16_t y = center.y + offset; y < section_->get_dimensions()->y; y++) {
						section_->set_one(x, y, palette_->get_color_at_index(count + cycle_index_ + (x * skew_)));
						count++;
					}
				}
			}
			else {	// Horizontal
				for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
					uint16_t count = 0;

					// Note: ROW MUST BE A SIGNED INT IN ORDER TO ACCESS INDEX 0.
					for (int32_t x = center.x; x >= 0; x--) {
						section_->set_one(x, y, palette_->get_color_at_index(count + cycle_index_ + (y * skew_)));
						count++;
					}

					/*
						Check for an odd number of Pixels.
						If so, set the center one to index 0.
					*/
					uint8_t offset = 0;
					if (section_->get_dimensions()->size() % 2 != 0) {
						offset += 1;
						section_->set_one(center.x + offset, y, palette_->get_color_at_index(cycle_index_ + (y * skew_)));
					}

					offset += 1;

					// Go from the center to the last
					count = 0;
					for (uint16_t x = center.x + offset; x < section_->get_dimensions()->x; x++) {
						section_->set_one(x, y, palette_->get_color_at_index(count + cycle_index_ + (y * skew_)));
						count++;
					}
				}
			}
		}
		else {
			for (uint16_t y = 0; y < section_->get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < section_->get_dimensions()->x; x++) {
					if (orientation_ == Orientation::Vertical) {
						section_->set_one(x, y, palette_->get_color_at_index(y + cycle_index_ + (x * skew_)));
					}
					else {	// Horizontal
						section_->set_one(x, y, palette_->get_color_at_index(x + cycle_index_ + (y * skew_)));
					}
				}
			}
		}

		update_cycle(0, palette_->get_size());
	}

	WaveAnimation::~WaveAnimation() {}
}
