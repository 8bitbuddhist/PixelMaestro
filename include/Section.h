/*
	Section.cpp - Class for controlling multiple Pixels.
*/

#ifndef SECTION_H
#define SECTION_H

#include "Colors.h"
#include "Pixel.h"

namespace PixelMaestro {
	class Section {

		public:
			/// The orientation of the current animation. Does not affect animations that don't have a specific direction (e.g. BLINK).
			enum AnimationOrientations {
				HORIZONTAL,
				VERTICAL
			};

			/// Set of animations usable by the Section.
			enum ColorAnimations {
				/// Activates each Pixel.
				SOLID,
				/// Alternates Pixels between their default color and black (off).
				BLINK,
				/// Scrolls the color array across the Section.
				WAVE,
				/// Scrolls the color array back and forth ping-pong style.
				PONG,
				/// Converges the color array into the center of the Section.
				MERGE,
				/// Sets each Pixel to a random color stored in colors_.
				RANDOMINDEX,
				/// Creates a shimmering effect by turning on random pixels.
				SPARKLE,
				/// Scrolls through a pattern defined in pattern_.
				PATTERN,
				/// Cycles all pixels through all stored colors.
				CYCLE,
				/// Blends each pixel between varying levels of gray. THIS MODIFIES THE COLOR ARRAY.
				STATIC,
				/// Turns off all Pixels. This should always be the last animation in the list.
				NONE
			};

			/**
				Overlays a second Section on top of the current one.
				NOTE: When getting color output, use getPixelColor(). This returns RGB values after blending the two Sections together.
			*/
			struct Overlay {
				/// The Section to overlay.
				Section *section = nullptr;
				/// Method of blending the output from the Overlay with the base Section.
				Colors::MixMode mixMode;
				/// Transparency level of the overlaid Section (if applicable).
				float alpha;

				void operator=(Overlay newLayer) {
					section = newLayer.section;
					mixMode = newLayer.mixMode;
					alpha = newLayer.alpha;
				}
			};

			/**
				Defines the Pixel layout of the Section.
				The number of Pixels in this Section is determined by rows * columns.
			*/
			struct Layout {
				/// The number of rows in the Section.
				unsigned short rows;
				/// The number of columns in the Section.
				unsigned short columns;
			};

			/**
				Defines a pattern displayed in the Section.
				Patterns are encoded in an unsigned int corresponding to a single row of Pixels.
			*/
			struct Pattern {
				/**
					The pattern to display when the PATTERN animation is active.
					Stored as an array of bools where each bool corresponds to a Pixel.
				*/
				bool *pattern;
				/// The number of rows in a single frame.
				unsigned short rows;
				/// The number of columns in a single frame.
				unsigned short columns;
				/// The number of frames in the Pattern.
				unsigned short frames;
			};

			Section::ColorAnimations getColorAnimation();
			unsigned short getCycleSpeed();
			bool getFade();
			Layout *getLayout();
			unsigned int getNumPixels();
			Pixel *getPixel(unsigned int pixel);
			Colors::RGB getPixelColor(unsigned int pixel);
			unsigned int getPixelIndex(unsigned short row, unsigned short column);
			unsigned short getRefreshRate();
			void setAll(Colors::RGB *color);
			void setColorAnimation(Section::ColorAnimations animation = ColorAnimations(NONE), bool reverseAnimation = false, AnimationOrientations = AnimationOrientations(HORIZONTAL));
			void setColors(Colors::RGB *colors, unsigned int numColors);
			void setCycleIndex(unsigned int index);
			void setCycleInterval(unsigned short rate, unsigned short pause = 0);
			void setOne(unsigned int pixel, Colors::RGB *color);
			void setOne(unsigned short row, unsigned short column, Colors::RGB *color);
			void setOverlay(Section *section, Colors::MixMode mixMode, float alpha = 0.0);
			void setPattern(bool *pattern, unsigned short rows, unsigned short columns, unsigned short frames);
			void setPattern(Pattern pattern);
			void setPixels(Pixel *pixels, unsigned short rows, unsigned short columns);
			void setRefreshInterval(unsigned short rate);
			void toggleFade();
			void update(unsigned long currentTime);
			void unsetOverlay();

		private:
			AnimationOrientations animation_orientation_ = AnimationOrientations(HORIZONTAL);
			Section::ColorAnimations color_animation_ = ColorAnimations(SOLID);	/// The active Section animation. Defaults to SOLID.
			Colors::RGB *colors_;				/// Array of colors used in animations.
			unsigned int cycle_index_ = 0;		///	The current cycle index.
			unsigned short cycle_interval_ = 100;	/// The time between animation cycles in milliseconds.
			unsigned short pause_ = 0;			/// The amount of time the Section will wait in milliseconds before starting an animation cycle.
			bool fade_ = true;					/// Whether to fade between cycles.
			unsigned long last_cycle_ = 0;		/// The time since the last animation cycle change.
			unsigned long last_refresh_ = 0;	/// The time since the Pixels were last refreshed.
			Layout layout_;						/// The Pixel layout of the array.
			Overlay overlay_;					/// Section overlaying the current section (if applicable);
			Pattern pattern_;					/// The layout of the pattern used in the PATTERN animation (if applicable).
			Pixel *pixels_;						/// Array of Pixels stored in the Section.
			unsigned int num_colors_;			/// The number of colors in colors_.
			unsigned short refresh_interval_ = 20;	/// The time between Pixel updates in milliseconds.
			bool reverse_animation_ = false;	/// Whether to reverse the current  animation.

			// Color animation functions
			void animation_blink();
			void animation_cycle();
			unsigned int animation_getColorIndex(unsigned int count);
			void animation_merge();
			void animation_pattern();
			void animation_pong();
			void animation_randomIndex();
			void animation_solid();
			void animation_sparkle();
			void animation_static();
			void animation_updateCycle(unsigned int min, unsigned int max);
			void animation_wave();
	};
}

#endif
