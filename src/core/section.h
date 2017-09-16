/*
	Section.cpp - Class for controlling multiple Pixels.
*/

#ifndef SECTION_H
#define SECTION_H

#include "../animation/animation.h"
#include "../canvas/canvas.h"
#include "colors.h"
#include "point.h"
#include "pixel.h"

namespace PixelMaestro {
	class Canvas;

	class Animation;

	class Section {

		public:
			/**
				Overlays a second Section on top of the current one.
				When getting color output, use get_pixel_color(). This returns RGB values after blending the two Sections together.
			*/
			struct Overlay {
				/**
				 * The Section to use as the overlay.
				 * This is different from the Section containing the Overlay object.
				 */
				Section* section = nullptr;

				/// Method of blending the output from the Overlay with the base Section.
				Colors::MixMode mix_mode = Colors::MixMode::NONE;

				/// Transparency level of the overlaid Section (if applicable).
				unsigned char alpha;

				/**
				 * Constructor.
				 * @param section Section to use as the Overlay.
				 * @param mix_mode Color mixing method to use.
				 * @param alpha For The amount of transparency that the Overlay will have (0 - 255).
				 */
				Overlay(Point* dimensions, Colors::MixMode mix_mode, unsigned char alpha) {
					this->section = new Section(dimensions);
					this->mix_mode = mix_mode;
					this->alpha = alpha;
				}

				~Overlay() {
					delete this->section;
				}
			};

			Section(Point* dimensions);
			~Section();
			Canvas* add_canvas();
			Section::Overlay* add_overlay(Colors::MixMode mix_mode = Colors::MixMode::NORMAL, unsigned char alpha = 128);
			Animation* get_animation();
			Canvas* get_canvas();
			unsigned short get_cycle_interval();
			Point* get_dimensions();
			Section::Overlay* get_overlay();
			Pixel* get_pixel(unsigned int pixel);
			Colors::RGB get_pixel_color(unsigned int pixel);
			unsigned int get_pixel_index(Point* coordinates);
			unsigned int get_pixel_index(unsigned short x, unsigned short y);
			unsigned short get_refresh_interval();
			void remove_canvas();
			void remove_overlay();
			void set_all(Colors::RGB* color);
			void set_animation(Animation* animation, bool preserve_cycle_index = false);
			void set_cycle_interval(unsigned short interval, unsigned short pause = 0);
			void set_one(unsigned int pixel, Colors::RGB* color);
			void set_one(unsigned short x, unsigned short y, Colors::RGB* color);
			void set_pixels(Point* layout);
			void set_refresh_interval(unsigned short* interval);
			void update(const unsigned long& current_time);

		private:
			/// The animation displayed in this Section.
			Animation* animation_ = nullptr;

			/// The Canvas to display (if applicable).
			Canvas* canvas_ = nullptr;

			/// The time between animation cycles in milliseconds. Defaults to 250.
			unsigned short cycle_interval_ = 250;

			/// The logical layout of the Pixels.
			Point* dimensions_ = nullptr;

			/// The time since the last animation cycle change in milliseconds. Defaults to 0.
			unsigned long last_cycle_ = 0;

			/// The Section overlaying the current section (if applicable).
			Overlay* overlay_ = nullptr;

			/// The amount of time the Section waits in milliseconds before starting the next animation cycle, by finishing the current cycle early. Defaults to 0.
			unsigned short pause_ = 0;

			/// The array of Pixels managed by the Section.
			Pixel* pixels_ = nullptr;

			/// The time between Pixel redraws in milliseconds. Controlled by the Maestro.
			unsigned short* refresh_interval_ = nullptr;
	};
}

#endif
