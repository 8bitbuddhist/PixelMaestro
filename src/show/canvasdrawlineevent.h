#ifndef CANVASDRAWLINEEVENT_H
#define CANVASDRAWLINEEVENT_H


#include "../canvas.h"
#include "event.h"
#include "../point.h"

namespace PixelMaestro {
	class CanvasDrawLineEvent : public Event {
		public:
			CanvasDrawLineEvent(unsigned long time, Canvas *canvas, Point *origin, Point *target);
			void run();

		private:
			Canvas *canvas_;
			Point *origin_;
			Point *target_;
	};
}

#endif // CANVASDRAWLINEEVENT_H
