#ifndef CANVASDRAWCIRCLEEVENT_H
#define CANVASDRAWCIRCLEEVENT_H

#include "../canvas/canvas.h"
#include "../canvas/colorcanvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawCircleEvent : public Event {
		public:
			CanvasDrawCircleEvent(unsigned long time, Canvas* canvas, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			CanvasDrawCircleEvent(unsigned long time, ColorCanvas* canvas, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			void run();

		private:
			Canvas* canvas_;
			Colors::RGB color_;
			bool is_color_canvas_ = false;
			bool fill_;
			unsigned short origin_x_, origin_y_;
			unsigned short radius_;
	};
}

#endif // CANVASDRAWCIRCLEEVENT_H
