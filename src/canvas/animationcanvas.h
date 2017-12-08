/*
 * AnimationCanvas - Draws a pattern using the Section's underlying Animation.
 */

#ifndef ANIMATIONCANVAS_H
#define ANIMATIONCANVAS_H

#include "canvas.h"

namespace PixelMaestro {
	class AnimationCanvas : public Canvas {
		public:
			AnimationCanvas(Section* section);
			AnimationCanvas(Section* section, uint16_t num_frames);
			~AnimationCanvas();
			void activate(uint16_t x, uint16_t y);
			void deactivate(uint16_t x, uint16_t y);
			void draw_frame(bool* frame, uint16_t size_x, uint16_t size_y);
			bool* get_frame(uint16_t frame) const;
			Colors::RGB get_pixel_color(uint16_t x, uint16_t y);
			CanvasType::Type get_type() const;
			void initialize();

		protected:
			void delete_frames();

		private:
			/**
			 * The frames in the Canvas.
			 * Each frame consists of a boolean array where each value corresponds to a Pixel.
			 * If true, the Pixel is active/lit.
			 */
			bool** frames_ = nullptr;
	};
}

#endif // ANIMATIONCANVAS_H
