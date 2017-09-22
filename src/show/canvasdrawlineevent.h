#ifndef CANVASDRAWLINEEVENT_H
#define CANVASDRAWLINEEVENT_H

#include "../canvas/basecanvas.h"
#include "../canvas/colorcanvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawLineEvent : public Event {
		public:
			CanvasDrawLineEvent(unsigned long time, BaseCanvas* canvas, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			CanvasDrawLineEvent(unsigned long time, ColorCanvas* canvas, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			void run();

		private:
			BaseCanvas* canvas_;
			Colors::RGB color_;
			bool is_color_canvas_ = false;
			unsigned short origin_x_, origin_y_;
			unsigned short target_x_, target_y_;
	};
}

#endif // CANVASDRAWLINEEVENT_H
