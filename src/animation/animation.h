/*
 * Animation - Base class for rendering Animations on a Section.
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdint.h>
#include "animationtype.h"
#include "../core/colors.h"
#include "../core/section.h"

namespace PixelMaestro {
	class Section;

	class Animation {
		public:

			/// The orientation of the animation. Does not affect animations that don't have a specific direction (e.g. CycleAnimation).
			enum Orientation : uint8_t {
				Horizontal,
				Vertical
			};

			Animation(Colors::RGB* colors, uint8_t num_colors);
			virtual ~Animation();
			Colors::RGB* get_color_at_index(uint8_t index);
			Colors::RGB* get_colors();
			uint8_t get_cycle_index();
			bool get_fade();
			uint8_t get_num_colors();
			uint32_t get_num_pixels();
			Orientation get_orientation();
			bool get_reverse();
			uint16_t get_pause();
			uint16_t get_speed();
			AnimationType::Type get_type();
			void set_colors(Colors::RGB* colors, uint8_t num_colors);
			void set_cycle_index(uint8_t index);
			void set_fade(bool fade);
			void set_orientation(Orientation orientation);
			void set_speed(uint16_t speed, uint16_t pause = 0);
			void set_reverse(bool reverse);
			bool update(const uint32_t& current_time, Section *section);
			virtual void update(Section* section) = 0;

		protected:			
			/// Array of colors used in the animation.
			Colors::RGB* colors_ = nullptr;

			///	The current stage in the animation cycle. Defaults to 0.
			uint8_t cycle_index_ = 0;

			/// Whether to fade between cycles. Defaults to true.
			bool fade_ = true;

			/// The amount of time (in milliseconds) since the last animation cycle change.
			uint32_t last_cycle_ = 0;

			/// The number of colors in colors_.
			uint8_t num_colors_ = 0;

			/// The orientation of the animation. Defaults to HORIZONTAL.
			Orientation orientation_ = Orientation::Horizontal;

			/// The amount of time (in milliseconds) to wait before starting an animation cycle. Defaults to 0.
			uint16_t pause_ = 0;

			/// Whether to animate the current animation in reverse. Defaults to false.
			bool reverse_ = false;

			/// The amount of time (in milliseconds) between animation updates. Defaults to 100.
			uint16_t speed_ = 100;

			/// The type of Animation. Gets set in the derived class' constructor.
			AnimationType::Type type_;

			void update_cycle(uint8_t min, uint8_t max);
	};
}

#endif // ANIMATION_H
