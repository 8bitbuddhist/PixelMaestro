#ifndef COLORANIMATION_H
#define COLORANIMATION_H

#include "colors.h"
#include "section.h"

namespace PixelMaestro {
	class Section;

	class ColorAnimation {
		public:
			/// Set of animations usable by the Section.
			enum Animations {
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

			/// The orientation of the current animation. Does not affect animations that don't have a specific direction (e.g. BLINK).
			enum Orientations {
				HORIZONTAL,
				VERTICAL
			};

			/// Array of colors used in the animation.
			Colors::RGB* colors_ = nullptr;

			ColorAnimation(Section *section, bool reverse = false, Orientations orientation = Orientations::HORIZONTAL);
			unsigned short get_num_colors();
			unsigned int get_num_pixels();
			unsigned int get_pixel_index(unsigned short x, unsigned short y);
			void set_colors(Colors::RGB* colors, unsigned short num_colors);
			virtual void update() = 0;

		protected:
			///	The current stage of the animation cycle. Defaults to 0.
			unsigned short cycle_index_ = 0;

			/// The time between animation cycles in milliseconds. Defaults to 100.
			unsigned short cycle_interval_ = 100;

			/// Whether to fade between cycles. Defaults to true.
			bool fade_ = true;

			/// The time since the last animation cycle change in milliseconds. Defaults to 0.
			unsigned long last_cycle_ = 0;

			/// The time since the Pixels were last refreshed in milliseconds. Defaults to 0.
			unsigned long last_refresh_ = 0;

			/// The number of colors in colors_.
			unsigned short num_colors_ = 0;

			/// The orientation of the animation. Defaults to HORIZONTAL.
			Orientations orientation_ = Orientations::HORIZONTAL;

			/// The amount of time to wait in milliseconds before starting the next animation cycle by finishing the current cycle early. Defaults to 0.
			unsigned short pause_ = 0;

			/// The time between Pixel redraws in milliseconds. Only relevant when fading is enabled. Defaults to 20.
			unsigned short refresh_interval_ = 20;

			/// Whether to animate the current animation in reverse. Defaults to false.
			bool reverse_ = false;

			Section* section_ = nullptr;

			unsigned short get_color_index(unsigned short count);
			void update_cycle(unsigned short min, unsigned short max);
	};
}

#endif // COLORANIMATION_H
