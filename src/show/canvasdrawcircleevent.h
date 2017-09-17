#ifndef CANVASDRAWCIRCLEEVENT_H
#define CANVASDRAWCIRCLEEVENT_H

#include "../canvas/canvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawCircleEvent : public Event {
		public:
			CanvasDrawCircleEvent(unsigned long time, Canvas* canvas, unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill);
			void run();

		private:
			Canvas* canvas_;
			bool fill_;
			unsigned short origin_x_, origin_y_;
			unsigned short radius_;
	};
}

#endif // CANVASDRAWCIRCLEEVENT_H
