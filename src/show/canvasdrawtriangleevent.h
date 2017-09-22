#ifndef CANVASDRAWTRIANGLEEVENT_H
#define CANVASDRAWTRIANGLEEVENT_H

#include "../canvas/basecanvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawTriangleEvent : Event {
		public:
			CanvasDrawTriangleEvent(unsigned long time, BaseCanvas* canvas, unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill);
			void run();

		private:
			BaseCanvas* canvas_;
			bool fill_;
			unsigned short point_a_x_, point_a_y_;
			unsigned short point_b_x_, point_b_y_;
			unsigned short point_c_x_, point_c_y_;
	};
}

#endif // CANVASDRAWTRIANGLEEVENT_H
