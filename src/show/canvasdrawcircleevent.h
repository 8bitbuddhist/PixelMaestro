#ifndef CANVASDRAWCIRCLEEVENT_H
#define CANVASDRAWCIRCLEEVENT_H

#include "../canvas/canvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawCircleEvent : public Event {
		public:
			CanvasDrawCircleEvent(unsigned long time, Canvas* canvas, Point* origin, unsigned short radius, bool fill);
			void run();

		private:
			Canvas* canvas_;
			bool fill_;
			Point* origin_;
			unsigned short radius_;
	};
}

#endif // CANVASDRAWCIRCLEEVENT_H
