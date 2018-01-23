/*
	Section.cpp - Class for controlling multiple Pixels.
*/

#ifndef SECTION_H
#define SECTION_H

#include <stdint.h>
#include "../animation/animation.h"
#include "../animation/animationtype.h"
#include "../canvas/canvas.h"
#include "../canvas/canvastype.h"
#include "colors.h"
#include "maestro.h"
#include "point.h"
#include "pixel.h"
#include "../utility.h"

namespace PixelMaestro {
	class Canvas;

	class Animation;

	class Maestro;

	class Section {

		public:
			/// Sets the Section's scrolling behavior.
			struct Scroll {
				/// If true, reverses the scrolling direction along the x axis.
				bool reverse_x = false;
				/// If true, reverses the scrolling direction along the y axis.
				bool reverse_y = false;

				/**
				 * Sets the amount of time between a single x-axis step.
				 * Overrides step_x when step_x is less than 1.
				 */
				Timing* timing_x = nullptr;
				/**
				 * Sets the amount of time between a single y-axis step.
				 * Overrides step_y when step_y is less than 1.
				 */
				Timing* timing_y = nullptr;

				/**
				 * Sets the number of y-axis steps to take with each update.
				 * Overridden by timing_x when this is calculated to be less than 1.
				 */
				uint16_t step_x = 0;
				/**
				 * Sets the number of y-axis steps to take with each update.
				 * Overridden by timing_y when this is calculated to be less than 1.
				 */
				uint16_t step_y = 0;

				/// Removes the timing interval along the x axis.
				void remove_timing_x() {
					delete timing_x;
					timing_x = nullptr;
				}

				/// Removes the timing interval along the y axis.
				void remove_timing_y() {
					delete timing_y;
					timing_y = nullptr;
				}

				/**
				 * Sets the scrolling behavior.
				 * The step count is calculated by factoring in the Pixel grid size and Maestro refresh rate.
				 * @param refresh_interval Amount of time between Maestro refreshes.
				 * @param dimensions The dimensions of the parent Section.
				 * @param interval_x The amount of time to complete a scroll along the x axis.
				 * @param interval_y The amount of time to complete a scroll along the y axis.
				 * @param reverse_x If true, reverses the scrolling direction along the x axis.
				 * @param reverse_y If true, reverses the scrolling direction along the y axis.
				 */
				void set(uint16_t refresh_interval, Point* dimensions, uint16_t interval_x, uint16_t interval_y, bool reverse_x = false, bool reverse_y = false) {
					this->reverse_x = reverse_x;
					this->reverse_y = reverse_y;
					/*
					 * Calculate step counts.
					 * Using the scroll interval, we need to determine how to change the offset values on each refresh.
					 *
					 * If the interval is low (Section scrolls quickly), each update moves the image > 1 pixel.
					 * In this case, we simply adjust the offset by the number of pixels it needs to move per refresh.
					 *
					 * If the interval is high (Section scrolls slowly), each update moves the image < 1 pixel.
					 * In this case, we calculate the amount of time until the offset moves 1 pixel.
					 * If this time is larger than the Maestro's refresh interval, scrolling won't occur until at least the next refresh.
					 */

					/*
					 * Calculate the x-axis step count.
					 *
					 * Divide the x interval by the Maestro's refresh rate, then divide the Section's x-axis size by the result.
					 * This gives you the number of pixels to move over per refresh.
					 */
					float x = dimensions->x / (float)(interval_x / (float)refresh_interval);
					// If x is less than 1 pixel, calculate the amount of time until the Section scrolls by 1 pixel.
					if (x > 0 && x < 1) {
						uint16_t interval = (1 / x) * refresh_interval;
						if (timing_x) {
							timing_x->set_interval(interval);
						}
						else {
							timing_x = new Timing(interval);
						}
					}
					// x is greater than 1 pixel, so use x as our step amount.
					else {
						remove_timing_x();
						step_x = x;
					}

					float y = dimensions->y / (float)(interval_y / (float)refresh_interval);
					if (y > 0 && y < 1) {
						uint16_t interval = (1 / x) * refresh_interval;
						if (timing_y) {
							timing_y->set_interval(interval);
						}
						else {
							timing_y = new Timing(interval);
						}
					}
					else {
						remove_timing_y();
						step_y = y;
					}
				}

				~Scroll() {
					delete timing_x;
					delete timing_y;
				}
			};

			/**
				Layers a second Section on top of the current one.
				When getting color output, use get_pixel_color(). This returns RGB values after blending the two Sections together.
			*/
			struct Layer {
				/**
				 * The Section to use as the layer.
				 * This is different from the Section containing the Layer object.
				 */
				Section* section = nullptr;

				/// Method of blending the output from the Layer with the base Section.
				Colors::MixMode mix_mode = Colors::MixMode::None;

				/// Transparency level of the overlaid Section.
				uint8_t alpha;

				/**
				 * Constructor.
				 * @param section Section to use as the Layer.
				 * @param mix_mode Color mixing method to use.
				 * @param alpha For The amount of transparency that the Layer will have (0 - 255).
				 */
				Layer(Section* parent, Colors::MixMode mix_mode, uint8_t alpha = 0) {
					this->section = new Section(*parent->get_dimensions(), parent);
					this->section->set_maestro(parent->get_maestro());
					this->mix_mode = mix_mode;
					this->alpha = alpha;
				}

				~Layer() {
					delete this->section;
				}
			};

			Section();
			Section(Point dimensions, Section* parent = nullptr);
			Section(uint16_t x, uint16_t y, Section* parent = nullptr);
			~Section();
			Animation* get_animation() const;
			Canvas* get_canvas() const;
			Point* get_dimensions();
			Maestro* get_maestro() const;
			Section::Layer* get_layer() const;
			Point* get_offset();
			Section* get_parent_section() const;
			Pixel* get_pixel(uint16_t x, uint16_t y) const;
			Colors::RGB get_pixel_color(uint16_t x, uint16_t y);
			Scroll* get_scroll() const;
			void remove_animation();
			void remove_canvas();
			void remove_layer();
			void remove_scroll();
			Animation* set_animation(AnimationType::Type type, Colors::RGB* colors, uint8_t num_colors, bool preserve_settings = true);
			Canvas* set_canvas(CanvasType::Type type = CanvasType::Type::AnimationCanvas, uint16_t num_frames = 1);
			void set_dimensions(uint16_t x, uint16_t y);
			Section::Layer* set_layer(Colors::MixMode mix_mode = Colors::MixMode::Alpha, uint8_t alpha = 128);
			void set_maestro(Maestro* maestro);
			Point* set_offset(uint16_t x, uint16_t y);
			void set_one(uint32_t pixel, Colors::RGB* color);
			void set_one(uint16_t x, uint16_t y, Colors::RGB* color);
			Scroll* set_scroll(uint16_t x, uint16_t y, bool reverse_x = false, bool reverse_y = false);
			void update(const uint32_t& current_time);
			void update_scroll(const uint32_t& current_time);

		private:
			/// The animation displayed in this Section.
			Animation* animation_ = nullptr;

			/// The Canvas to display (if applicable).
			Canvas* canvas_ = nullptr;

			/// The logical layout of the Pixels.
			Point dimensions_;

			/// The Section's parent Maestro.
			Maestro* maestro_ = nullptr;

			/// The Section layering the current section (if applicable).
			Layer* layer_ = nullptr;

			/// How far the Section is offset from the grid origin.
			Point offset_ = Point(0, 0);

			/// The Section's parent (if this is an Layer).
			Section* parent_section_ = nullptr;

			/// The array of Pixels managed by the Section.
			Pixel* pixels_ = nullptr;

			/// The Section's scrolling behavior.
			Scroll* scroll_ = nullptr;
	};
}

#endif
