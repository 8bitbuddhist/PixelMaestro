/*
 * Animation - Base class for rendering Animations on a Section.
 */

#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdint.h>
#include "animationtype.h"
#include "../core/colors.h"
#include "../core/palette.h"
#include "../core/point.h"
#include "../core/section.h"
#include "../core/timer/animationtimer.h"

/*
 * FIXME: Ideas for using Animations to control Pixel next color and fade:
 *	Goal: Remove all color changing logic from Pixels without affecting functionality.
 *	Problem: Fading complicates matters, requiring Pixels to store:
 *		- The amount of steps from current color to next color
 *		- Progress until next color
 *		We can reduce mem usage by forcing Pixels to stick to the Palette, but we need to generate this info per-Palette.
 *	Actions:
 *	1) Convert all Animations into MappedAnimations so we can assign a Palette index to each Pixel
 *	2) When recalculating the map (and fade is enabled), calculate the steps from current color to next color and store in new array. We only need to do this once per color
 *		- How to track which colors have been calculated?
 *	3) When fading, apply the step_ to each color on each update. Apply the next_color_ when timer expires regardless of fade.
 */
namespace PixelMaestro {
	class AnimationTimer;
	class Section;
	class Animation {
		public:

			/// The orientation of the animation. Does not affect animations that don't have a specific direction (e.g. CycleAnimation).
			enum class Orientation : uint8_t {
				Horizontal,
				Vertical
			};

			explicit Animation(Section& section);
			virtual ~Animation();
			Point get_center() const;
			uint8_t get_cycle_index() const;
			bool get_fade() const;
			Orientation get_orientation() const;
			Palette* get_palette() const;
			bool get_reverse() const;
			Section& get_section() const;
			AnimationTimer* get_timer() const;
			AnimationType get_type() const;
			void set_cycle_index(uint8_t index);
			void set_fade(bool fade);
			void set_orientation(Orientation orientation);
			void set_palette(Palette* palette);
			void set_reverse(bool reverse);
			AnimationTimer& set_timer(uint16_t speed, uint16_t delay = 0);
			bool update(const uint32_t& current_time);
			virtual void update() = 0;

		protected:
			/// The center of the animation.
			Point center_ = {0, 0};

			///	The current stage in the animation cycle. Defaults to 0.
			uint8_t cycle_index_ = 0;

			/// Whether to fade between cycles. Defaults to true.
			bool fade_ = true;

			/// The orientation of the animation. Defaults to HORIZONTAL.
			Orientation orientation_ = Orientation::Horizontal;

			/// Color palette used in the animation.
			Palette* palette_ = nullptr;

			/// Whether to animate in reverse. Defaults to false.
			bool reverse_ = false;

			/// The Animation's parent Section.
			Section& section_;

			/// The Animation's timer. This is a pointer instead of a local object because we must initialize it after the Animation.
			AnimationTimer* timer_ = nullptr;

			/// The type of Animation. Gets set in the derived class' constructor.
			AnimationType type_ = AnimationType::Solid;

			void update_cycle(uint8_t min, uint8_t max);
	};
}

#endif // ANIMATION_H
