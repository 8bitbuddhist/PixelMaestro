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
			void activate(uint32_t pixel);
			void deactivate(uint32_t pixel);
			Colors::RGB get_pixel_color(uint32_t pixel);
			CanvasType::Type get_type();
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
