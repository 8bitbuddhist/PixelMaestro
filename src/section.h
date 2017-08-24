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
				/// Placeholder used to skip to the next animation.
				NEXT,

				/// Sets each Pixel to its corresponding color.
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

				/// Cycles all pixels through all stored colors.
				CYCLE,

				/// Turns off the Section. This should always be the last animation in the list.
				NONE
			};

			/**
				Overlays a second Section on top of the current one.
				When getting color output, use getPixelColor(). This returns RGB values after blending the two Sections together.
			*/
			struct Overlay {
				/// The Section to overlay.
				Section *section = nullptr;

				/// Method of blending the output from the Overlay with the base Section.
				Colors::MixMode mixMode = Colors::MixMode::NONE;

				/// Transparency level of the overlaid Section (if applicable).
				float alpha;

				/**
				 * Constructor. The Section will automatically be deleted when the Overlay is deleted.
				 * @param section New Section to use.
				 * @param mixMode Color mixing method to use.
				 * @param alpha For MixMode::ALPHA, the amount of transparency that the Overlay will have.
				 */
				Overlay(Section *section, Colors::MixMode mixMode, float alpha) {
					this->section = section;
					this->mixMode = mixMode;
					this->alpha = alpha;
				}
			};

			Section(Pixel *pixels, Point *layout);
			AnimationOpts *getAnimationOpts();
			Canvas *getCanvas();
			Section::ColorAnimations getColorAnimation();
			unsigned short getCycleSpeed();
			Point *getDimensions();
			bool getFade();
			Section::Overlay *getOverlay();
			unsigned int getNumPixels();
			Pixel *getPixel(unsigned int pixel);
			Colors::RGB getPixelColor(unsigned int pixel);
			unsigned int getPixelIndex(unsigned short row, unsigned short column);
			unsigned short getRefreshRate();
			void setAll(Colors::RGB *color);
			void setCanvas(Canvas *canvas);
			void setColorAnimation(Section::ColorAnimations animation = ColorAnimations(NONE), bool reverseAnimation = false, AnimationOrientations = AnimationOrientations(HORIZONTAL));
			void setColors(Colors::RGB *colors, unsigned int numColors);
			void setCycleIndex(unsigned int index);
			void setCycleInterval(unsigned short interval, unsigned short pause = 0);
			void setOne(unsigned int pixel, Colors::RGB *color);
			void setOne(unsigned short row, unsigned short column, Colors::RGB *color);
			void setOverlay(Overlay *overlay);
			void setPixels(Pixel* pixels, Point *layout);
			void setRefreshInterval(unsigned short interval);
			void toggleFade();
			void update(const unsigned long &currentTime);
			void unsetOverlay();

		private:
			/// The orientation of the animation. Defaults to HORIZONTAL.
			AnimationOrientations animation_orientation_ = AnimationOrientations(HORIZONTAL);

			/// Extra parameters for running animations.
			AnimationOpts animation_opts_;

			/// The Canvas to display (if applicable).
			Canvas *canvas_ = nullptr;

			/// The active Section animation. Defaults to SOLID.
			Section::ColorAnimations color_animation_ = ColorAnimations(SOLID);

			/// Array of colors used in animations..
			Colors::RGB *colors_ = nullptr;

			///	The current stage of the animation cycle. Defaults to 0.
			unsigned int cycle_index_ = 0;

			/// The time between animation cycles in milliseconds. Defaults to 100.
			unsigned short cycle_interval_ = 100;

			/// The amount of time the Section waits in milliseconds before starting the next animation cycle, by finishing the current cycle early. Defaults to 0.
			unsigned short pause_ = 0;

			/// Whether to fade between cycles. Defaults to true.
			bool fade_ = true;

			/// The time since the last animation cycle change in milliseconds. Defaults to 0.
			unsigned long last_cycle_ = 0;

			/// The time since the Pixels were last refreshed in milliseconds. Defaults to 0.
			unsigned long last_refresh_ = 0;

			/// The logical layout of the Pixels.
			Point *dimensions_ = nullptr;

			/// The Section overlaying the current section (if applicable).
			Overlay *overlay_ = nullptr;

			/// The array of Pixels managed by the Section.
			Pixel *pixels_ = nullptr;

			/// The number of colors in colors_.
			unsigned int num_colors_;

			/// The time between Pixel redraws in milliseconds. Only relevant when fading is enabled. Defaults to 20.
			unsigned short refresh_interval_ = 20;

			/// Whether to animate the current animation in reverse. Defaults to false.
			bool reverse_animation_ = false;

			// Color animation functions
			void animation_blink();
			void animation_cycle();
			unsigned int animation_getColorIndex(unsigned int count);
			void animation_merge();
			void animation_pong();
			void animation_randomIndex();
			void animation_solid();
			void animation_sparkle();
			void animation_updateCycle(unsigned int min, unsigned int max);
			void animation_wave();
	};
}

#endif
