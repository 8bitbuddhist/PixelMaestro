/*
	Section.cpp - Class for controlling multiple Pixels.
*/

#ifndef SECTION_H
#define SECTION_H

#include "coloranimation.h"
#include "colors.h"
#include "canvas.h"
#include "point.h"
#include "pixel.h"

namespace PixelMaestro {
	class Canvas;

	class ColorAnimation;

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
				float alpha;

				/**
				 * Constructor.
				 * @param section Section to use as the Overlay.
				 * @param mix_mode Color mixing method to use.
				 * @param alpha For MixMode::ALPHA, the amount of transparency that the Overlay will have.
				 */
				Overlay(Section* section, Colors::MixMode mix_mode, float alpha) {
					this->section = section;
					this->mix_mode = mix_mode;
					this->alpha = alpha;
				}
			};

			Section(Pixel* pixels, Point* layout);
			Canvas* get_canvas();
			ColorAnimation* get_color_animation();
			unsigned short get_cycle_interval();
			Point* get_dimensions();
			Section::Overlay* get_overlay();
			unsigned int get_num_pixels();
			Pixel* get_pixel(unsigned int pixel);
			Colors::RGB get_pixel_color(unsigned int pixel);
			unsigned int get_pixel_index(Point* coordinates);
			unsigned int get_pixel_index(unsigned short x, unsigned short y);
			unsigned short get_refresh_interval();
			void set_all(Colors::RGB* color);
			void set_canvas(Canvas* canvas);
			void set_new_color_animation(ColorAnimation* animation);
			void set_cycle_interval(unsigned short interval, unsigned short pause = 0);
			void set_one(unsigned int pixel, Colors::RGB* color);
			void set_one(unsigned short row, unsigned short column, Colors::RGB* color);
			void set_overlay(Overlay* overlay);
			void set_pixels(Pixel* pixels, Point* layout);
			void set_refresh_interval(unsigned short interval);
			void update(const unsigned long& current_time);
			void unset_overlay();

		private:
			/// The animation displayed in this Section.
			ColorAnimation* color_animation_ = nullptr;

			/// The Canvas to display (if applicable).
			Canvas* canvas_ = nullptr;

			/// Array of colors used in animations..
			Colors::RGB* colors_ = nullptr;

			///	The current stage of the animation cycle. Defaults to 0.
			unsigned short cycle_index_ = 0;

			/// The time between animation cycles in milliseconds. Defaults to 100.
			unsigned short cycle_interval_ = 100;

			/// The logical layout of the Pixels.
			Point* dimensions_ = nullptr;

			/// The time since the last animation cycle change in milliseconds. Defaults to 0.
			unsigned long last_cycle_ = 0;

			/// The time since the Pixels were last refreshed in milliseconds. Defaults to 0.
			unsigned long last_refresh_ = 0;

			/// The Section overlaying the current section (if applicable).
			Overlay* overlay_ = nullptr;

			/// The amount of time the Section waits in milliseconds before starting the next animation cycle, by finishing the current cycle early. Defaults to 0.
			unsigned short pause_ = 0;

			/// The array of Pixels managed by the Section.
			Pixel* pixels_ = nullptr;

			/// The time between Pixel redraws in milliseconds. Only relevant when fading is enabled. Defaults to 20.
			unsigned short refresh_interval_ = 20;
	};
}

#endif
