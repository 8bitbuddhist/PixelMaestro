#ifndef CANVASDRAWTRIANGLEEVENT_H
#define CANVASDRAWTRIANGLEEVENT_H

#include "../canvas.h"
#include "../point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawTriangleEvent : Event {
		public:
			CanvasDrawTriangleEvent(unsigned long time, Canvas* canvas, Point* point_a, Point* point_b, Point* point_c, bool fill);
			void run();

		private:
			Canvas* canvas_;
			bool fill_;
			Point* point_a_;
			Point* point_b_;
			Point* point_c_;
	};
}

#endif // CANVASDRAWTRIANGLEEVENT_H
