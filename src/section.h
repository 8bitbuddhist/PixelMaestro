/*
	Section.cpp - Class for controlling multiple Pixels.
*/

#ifndef SECTION_H
#define SECTION_H

#include "colors.h"
#include "canvas.h"
#include "point.h"
#include "pixel.h"

namespace PixelMaestro {
	class Canvas;

	class Section {

		public:
			/// The orientation of the current animation. Does not affect animations that don't have a specific direction (e.g. BLINK).
			enum AnimationOrientations {
				HORIZONTAL,
				VERTICAL
			};

			/// Extra parameters for the current animation. If you do not specify them, they will be set implicitly in Section::setColorAnimation().
			union AnimationOpts {
				/// Threshold for activating a Pixel using the SPARKLE animation. The higher the threshold, the fewer the number of lit Pixels (0 - 100).
				unsigned char sparkle_threshold;
			};

			/// Set of animations usable by the Section.
			enum ColorAnimations {
				/// Placeholder used to skip to the next animation. This should always be the first animation in the list.
				NEXT,

				/// Sets each Pixel to its corresponding color.
				SOLID,

				/// Alternates Pixels between their default color and black (off).
				BLINK,

				/// Cycles Pixels through all stored colors.
				CYCLE,

				/// Scrolls the color array across the Section.
				WAVE,

				/// Scrolls the color array back and forth ping-pong style.
				PONG,

				/// Converges the color array into the center of the Section.
				MERGE,

				/// Sets each Pixel to a random color.
				RANDOM,

				/// Creates a shimmering effect by turning on random pixels.
				SPARKLE,

				/// Turns off the Section. This should always be the last animation in the list.
				NONE
			};

			/**
				Overlays a second Section on top of the current one.
				When getting color output, use getPixelColor(). This returns RGB values after blending the two Sections together.
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
			AnimationOpts *get_animation_opts();
			Canvas* get_canvas();
			Section::ColorAnimations get_color_animation();
			unsigned short get_cycle_interval();
			Point* get_dimensions();
			bool get_fade();
			Section::Overlay* get_overlay();
			unsigned int get_num_pixels();
			Pixel* get_pixel(unsigned int pixel);
			Colors::RGB get_pixel_color(unsigned int pixel);
			unsigned int get_pixel_index(Point* coordinates);
			unsigned int get_pixel_index(unsigned short x, unsigned short y);
			unsigned short get_refresh_interval();
			void set_all(Colors::RGB* color);
			void set_canvas(Canvas* canvas);
			void set_color_animation(Section::ColorAnimations animation = ColorAnimations(NONE), bool reverse_animation = false, AnimationOrientations = AnimationOrientations(HORIZONTAL));
			void set_colors(Colors::RGB* colors, unsigned short num_colors);
			void set_cycle_index(unsigned short index);
			void set_cycle_interval(unsigned short interval, unsigned short pause = 0);
			void set_one(unsigned int pixel, Colors::RGB* color);
			void set_one(unsigned short row, unsigned short column, Colors::RGB* color);
			void set_overlay(Overlay* overlay);
			void set_pixels(Pixel* pixels, Point* layout);
			void set_refresh_interval(unsigned short interval);
			void toggle_fade();
			void update(const unsigned long& current_time);
			void unset_overlay();

		private:
			/// The orientation of the animation. Defaults to HORIZONTAL.
			AnimationOrientations animation_orientation_ = AnimationOrientations(HORIZONTAL);

			/// Extra parameters for running animations.
			AnimationOpts animation_opts_;

			/// The Canvas to display (if applicable).
			Canvas* canvas_ = nullptr;

			/// The active Section animation. Defaults to SOLID.
			Section::ColorAnimations color_animation_ = ColorAnimations(SOLID);

			/// Array of colors used in animations..
			Colors::RGB* colors_ = nullptr;

			///	The current stage of the animation cycle. Defaults to 0.
			unsigned short cycle_index_ = 0;

			/// The time between animation cycles in milliseconds. Defaults to 100.
			unsigned short cycle_interval_ = 100;

			/// The logical layout of the Pixels.
			Point* dimensions_ = nullptr;

			/// Whether to fade between cycles. Defaults to true.
			bool fade_ = true;

			/// The time since the last animation cycle change in milliseconds. Defaults to 0.
			unsigned long last_cycle_ = 0;

			/// The time since the Pixels were last refreshed in milliseconds. Defaults to 0.
			unsigned long last_refresh_ = 0;

			/// The number of colors in colors_.
			unsigned short num_colors_ = 0;

			/// The Section overlaying the current section (if applicable).
			Overlay* overlay_ = nullptr;

			/// The amount of time the Section waits in milliseconds before starting the next animation cycle, by finishing the current cycle early. Defaults to 0.
			unsigned short pause_ = 0;

			/// The array of Pixels managed by the Section.
			Pixel* pixels_ = nullptr;

			/// The time between Pixel redraws in milliseconds. Only relevant when fading is enabled. Defaults to 20.
			unsigned short refresh_interval_ = 20;

			/// Whether to animate the current animation in reverse. Defaults to false.
			bool reverse_animation_ = false;

			// Color animation functions
			void animation_blink();
			void animation_cycle();
			unsigned short animation_get_color_index(unsigned short count);
			void animation_merge();
			void animation_pong();
			void animation_random();
			void animation_solid();
			void animation_sparkle();
			void animation_update_cycle(unsigned short min, unsigned short max);
			void animation_wave();
	};
}

#endif
