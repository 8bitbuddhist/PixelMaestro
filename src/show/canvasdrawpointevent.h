#ifndef CANVASDRAWPOINTEVENT_H
#define CANVASDRAWPOINTEVENT_H

#include "../canvas/basecanvas.h"
#include "../canvas/colorcanvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawPointEvent : Event {
		public:
			CanvasDrawPointEvent(unsigned long time, BaseCanvas *canvas, unsigned short cursor_x, unsigned short cursor_y);
			CanvasDrawPointEvent(unsigned long time, ColorCanvas *canvas, Colors::RGB color, unsigned short cursor_x, unsigned short cursor_y);
			void run();

		private:
			BaseCanvas* canvas_;
			Colors::RGB color_;
			bool is_color_canvas_ = false;
			unsigned short cursor_x_, cursor_y_;
	};
}

#endif // CANVASDRAWPOINTEVENT_H
