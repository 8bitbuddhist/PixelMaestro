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

namespace PixelMaestro {
	class Canvas;

	class Animation;

	class Maestro;

	class Section {

		public:
			/// Sets the Section's scrolling behavior.
			struct Scroll {
				/// The direction and rate that the Section will scroll along the x-axis.
				int16_t interval_x = 0;
				/// The direction and rate that the Section will scroll along the y-axis.
				int16_t interval_y = 0;

				/// The last time the Section scrolled along the x-axis.
				uint32_t last_scroll_x = 0;
				/// The last time the Section scrolled along the y-axis.
				uint32_t last_scroll_y = 0;

				/// How far the Section is offset from the origin on the x-axis.
				int16_t offset_x_ = 0;
				/// How far the Section is offset from the origin on the y-axis.
				int16_t offset_y_ = 0;

				/**
				 * Constructor. Sets the scroll rate and direction.
				 * @param x Scrolling along the x-axis.
				 * @param y Scrolling along the y-axis.
				 */
				Scroll(int16_t x, int16_t y) {
					this->interval_x = x;
					this->interval_y = y;
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
			Animation* set_animation(AnimationType::Type type, Colors::RGB* colors, uint8_t num_colors, bool preserve_cycle_index = true);
			Canvas* set_canvas(CanvasType::Type type = CanvasType::Type::AnimationCanvas, uint16_t num_frames = 1);
			void set_dimensions(uint16_t x, uint16_t y);
			Section::Layer* set_layer(Colors::MixMode mix_mode = Colors::MixMode::Alpha, uint8_t alpha = 128);
			void set_maestro(Maestro* maestro);
			Point* set_offset(uint16_t x, uint16_t y);
			void set_one(uint32_t pixel, Colors::RGB* color);
			void set_one(uint16_t x, uint16_t y, Colors::RGB* color);
			Scroll* set_scroll(int16_t x, int16_t y);
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
