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
			/// Set of animations usable by the Section.
			enum ColorAnimations {
				SOLID,			/// Activates each Pixel.
				BLINK,			/// Alternates Pixels between their default color and black (off).
				WAVE,			/// Scrolls the color array across the Section.
				PONG,			/// Scrolls the color array back and forth in a ping-pong animation.
				MERGE,			/// Converges the color array into the center of the Section.
				RANDOMINDEX,	/// Sets each Pixel to a random color stored in colors_.
				SPARKLE,		/// Creates a shimmering effect by turning on random pixels.
				PATTERN,		/// Scrolls through a pattern defined in pattern_.
				CYCLE,			/// Cycles all pixels through all stored colors.
				STATIC,			/// Creates a static effect by blending each pixel between varying levels of gray.
				NONE			/// Turns off all Pixels in the Section. This should always be the last animation in the list.
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
					Stored as an array of unsigned ints where each element corresponds to a row.
				*/
				unsigned int *pattern;
				/// The number of rows in a single frame.
				unsigned short height;
				/// The number of frames in the Pattern.
				unsigned short frames;
			};

			Section();
			Section(Pixel *pixels, unsigned short rows, unsigned short columns);

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
			void setColorAnimation(Section::ColorAnimations animation = ColorAnimations(NONE), bool reverseAnimation = false);
			void setColors(Colors::RGB *colors, unsigned int numColors);
			void setCycleIndex(unsigned int index);
			void setCycleSpeed(unsigned short speed);
			void setOverlay(Overlay overlay);
			void setOne(unsigned int pixel, Colors::RGB *color);
			void setOne(unsigned short row, unsigned short column, Colors::RGB *color);
			void setPattern(unsigned int *pattern, unsigned short patternRows, unsigned short numFrames);
			void setPixels(Pixel *pixels, unsigned short rows, unsigned short columns);
			void setRefreshRate(unsigned short refreshRate);
			void toggleFade();
			void update(unsigned long currentTime);
			void unsetOverlay();

		private:
			Section::ColorAnimations color_animation_ = ColorAnimations(SOLID);	/// The active Section animation. Defaults to SOLID.
			Colors::RGB *colors_;				/// Array of colors used in animations.
			unsigned int cycle_index_ = 0;		///	The current cycle index.
			unsigned short cycle_speed_ = 100;	/// The time between animation cycles in milliseconds.
			bool fade_ = true;					/// Whether to fade between cycles.
			unsigned long last_cycle_ = 0;		/// The time since the last animation cycle change.
			unsigned long last_refresh_ = 0;	/// The time since the Pixels were last refreshed.
			Layout layout_;						/// The Pixel layout of the array.
			Overlay overlay_;					/// Section overlaying the current section (if applicable);
			Pattern pattern_;					/// The layout of the pattern used in the PATTERN animation (if applicable).
			Pixel *pixels_;						/// Array of Pixels stored in the Section.
			unsigned int num_colors_;			/// The number of colors in colors_.
			unsigned short refresh_rate_ = 20;	/// The time between Pixel updates in milliseconds.
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
