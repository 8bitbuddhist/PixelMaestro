/*
	Section.cpp - Class for controlling multiple Pixels.
*/

#ifndef SECTION_H
#define SECTION_H

#include <stdint.h>
#include "../animation/animation.h"
#include "../animation/animationtype.h"
#include "../canvas/canvas.h"
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
				/// The original x interval. This is really just storage for use in Cues.
				uint16_t interval_x = 0;
				/// The original y interval.
				uint16_t interval_y = 0;

				/// If true, reverses the scrolling direction along the x axis.
				bool reverse_x = false;
				/// If true, reverses the scrolling direction along the y axis.
				bool reverse_y = false;

				/**
				 * Sets the amount of time between a single x-axis step.
				 * Overrides step_x when step_x is less than 1.
				 */
				Timer* timer_x = nullptr;
				/**
				 * Sets the amount of time between a single y-axis step.
				 * Overrides step_y when step_y is less than 1.
				 */
				Timer* timer_y = nullptr;

				/**
				 * Sets the number of y-axis steps to take with each update.
				 * Overridden by timer_x when this is calculated to be less than 1.
				 */
				uint16_t step_x = 0;
				/**
				 * Sets the number of y-axis steps to take with each update.
				 * Overridden by timer_y when this is calculated to be less than 1.
				 */
				uint16_t step_y = 0;

				/// Removes the x axis timer.
				void remove_timer_x() {
					delete timer_x;
					timer_x = nullptr;
				}

				/// Removes the y axis timer.
				void remove_timer_y() {
					delete timer_y;
					timer_y = nullptr;
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
					this->interval_x = interval_x;
					this->interval_y = interval_y;
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
						if (timer_x) {
							timer_x->set_interval(interval);
						}
						else {
							timer_x = new Timer(interval);
						}
					}
					// x is greater than 1 pixel, so use x as our step amount.
					else {
						remove_timer_x();
						step_x = x;
					}

					float y = dimensions->y / (float)(interval_y / (float)refresh_interval);
					if (y > 0 && y < 1) {
						uint16_t interval = (1 / y) * refresh_interval;
						if (timer_y) {
							timer_y->set_interval(interval);
						}
						else {
							timer_y = new Timer(interval);
						}
					}
					else {
						remove_timer_y();
						step_y = y;
					}
				}

				~Scroll() {
					remove_timer_x();
					remove_timer_y();
				}
			};

			/**
				Layers a second Section on top of the current one.
				When getting color output, use get_pixel_color(). This returns RGB values after blending the two Sections together.
			*/
			struct Layer {
				/// The Section to use as the layer.
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
				Layer(Section& parent, Colors::MixMode mix_mode, uint8_t alpha = 0) {
					this->section = new Section(parent.get_dimensions().x, parent.get_dimensions().y, &parent);
					this->section->set_maestro(parent.get_maestro());
					this->mix_mode = mix_mode;
					this->alpha = alpha;
				}

				~Layer() {
					delete this->section;
				}
			};

			/**
			 * Controls mirroring across the x and y axes.
			 */
			struct Mirror {
				bool x = false;
				bool y = false;

				uint16_t mid_x = 0;
				uint16_t mid_y = 0;

				void set(bool x, bool y, const Point& dimensions) {
					this->x = x;
					this->y = y;

					this->mid_x = dimensions.x / static_cast<float>(2);
					this->mid_y = dimensions.y / static_cast<float>(2);
				}
			};

			Section();
			Section(uint16_t x, uint16_t y, Section* parent = nullptr);
			~Section();
			Animation* get_animation() const;
			uint8_t get_brightness() const;
			Canvas* get_canvas() const;
			Point& get_dimensions() const;
			Section::Layer* get_layer() const;
			Maestro& get_maestro() const;
			Mirror* get_mirror() const;
			Point& get_offset();
			Section* get_parent_section() const;
			Pixel& get_pixel(uint16_t x, uint16_t y) const;
			Colors::RGB get_pixel_color(uint16_t x, uint16_t y, Colors::RGB* base_color = nullptr);
			Scroll* get_scroll() const;
			void remove_animation(bool clear_pixels);
			void remove_canvas();
			void remove_layer();
			void remove_scroll();
			Animation& set_animation(AnimationType animation_type, bool preserve_settings = true);
			void set_brightness(uint8_t brightness);
			Canvas& set_canvas(uint16_t num_frames = 1);
			void set_dimensions(uint16_t x, uint16_t y);
			Layer& set_layer(Colors::MixMode mix_mode = Colors::MixMode::Alpha, uint8_t alpha = 128);
			void set_maestro(Maestro& maestro);
			Mirror* set_mirror(bool x, bool y);
			Point& set_offset(uint16_t x, uint16_t y);
			void set_pixel_color(uint16_t x, uint16_t y, const Colors::RGB& color);
			Scroll& set_scroll(uint16_t x, uint16_t y, bool reverse_x = false, bool reverse_y = false);
			void set_step_count(uint8_t step_count);
			void sync(const uint32_t& new_time);
			void update(const uint32_t& current_time);
			void update_scroll(const uint32_t& current_time);

		private:
			/// The animation displayed in this Section.
			Animation* animation_ = nullptr;

			/// The total brightness of the Section. Defaults to full brightness.
			float brightness_ = 1.0;

			/// The Canvas to display (if applicable).
			Canvas* canvas_ = nullptr;

			/// The logical layout of the Pixels.
			Point dimensions_;

			/// The Section layering the current section (if applicable).
			Layer* layer_ = nullptr;

			/// The Section's parent Maestro.
			Maestro* maestro_ = nullptr;

			/// Mirrors the Section across the x and y axes.
			Mirror* mirror_ = nullptr;

			/// How far the Section is offset from the grid origin.
			Point offset_ = Point(0, 0);

			/// The Section's parent (if this is an Layer).
			Section* parent_section_ = nullptr;

			/// The array of Pixels managed by the Section.
			Pixel* pixels_ = nullptr;

			/// The Section's scrolling behavior.
			Scroll* scroll_ = nullptr;

			/// The number of steps for fading Pixels. Set by Animations. Defaults to 1.
			uint8_t step_count_ = 1;
	};
}

#endif
