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
			/**
				Overlays a second Section on top of the current one.
				When getting color output, use get_pixel_color(). This returns RGB values after blending the two Sections together.
			*/
			struct Overlay {
				/**
				 * The Section to use as the overlay.
				 * This is different from the Section containing the Overlay object.
				 */
				Section* section = nullptr;

				/// Method of blending the output from the Overlay with the base Section.
				Colors::MixMode mix_mode = Colors::MixMode::None;

				/// Transparency level of the overlaid Section.
				uint8_t alpha;

				/**
				 * Constructor.
				 * @param section Section to use as the Overlay.
				 * @param mix_mode Color mixing method to use.
				 * @param alpha For The amount of transparency that the Overlay will have (0 - 255).
				 */
				Overlay(Section* parent, Colors::MixMode mix_mode, uint8_t alpha = 0) {
					this->section = new Section(*parent->get_dimensions(), parent);
					this->mix_mode = mix_mode;
					this->alpha = alpha;
				}

				~Overlay() {
					delete this->section;
				}
			};

			Section();
			Section(Point dimensions, Section* parent = nullptr);
			Section(uint16_t x, uint16_t y, Section* parent = nullptr);
			~Section();
			Animation* get_animation();
			Canvas* get_canvas();
			Point* get_dimensions();
			Maestro* get_maestro();
			Section::Overlay* get_overlay();
			uint8_t get_num_overlays();
			Section* get_parent_section();
			Pixel* get_pixel(uint16_t x, uint16_t y);
			Colors::RGB get_pixel_color(uint16_t x, uint16_t y);
			void remove_animation();
			void remove_canvas();
			void remove_overlay();
			Animation* set_animation(AnimationType::Type type, Colors::RGB* colors, uint8_t num_colors, bool preserve_cycle_index = true);
			Canvas* set_canvas(CanvasType::Type type = CanvasType::Type::AnimationCanvas, uint16_t num_frames = 1);
			void set_dimensions(uint16_t x, uint16_t y);
			void set_maestro(Maestro* maestro);
			void set_one(uint32_t pixel, Colors::RGB* color);
			void set_one(uint16_t x, uint16_t y, Colors::RGB* color);
			Section::Overlay* set_overlay(Colors::MixMode mix_mode = Colors::MixMode::Alpha, uint8_t alpha = 128);
			void update(const uint32_t& current_time);

		private:
			/// The animation displayed in this Section.
			Animation* animation_ = nullptr;

			/// The Canvas to display (if applicable).
			Canvas* canvas_ = nullptr;

			/// The logical layout of the Pixels.
			Point dimensions_;

			/// The Section's parent Maestro.
			Maestro* maestro_ = nullptr;

			/// The Section overlaying the current section (if applicable).
			Overlay* overlay_ = nullptr;

			/// The Section's parent (if this is an Overlay).
			Section* parent_section_ = nullptr;

			/// The array of Pixels managed by the Section.
			Pixel* pixels_ = nullptr;
	};
}

#endif
