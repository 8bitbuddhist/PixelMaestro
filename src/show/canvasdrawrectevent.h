#ifndef CANVASDRAWRECTEVENT_H
#define CANVASDRAWRECTEVENT_H

#include "../canvas.h"
#include "event.h"
#include "../point.h"

namespace PixelMaestro {
	class CanvasDrawRectEvent : public Event {
		public:
			CanvasDrawRectEvent(unsigned long time, Canvas *canvas, Point *origin, Point *size, bool fill);
			void run();

		private:
			Canvas *canvas_;
			Point *origin_;
			Point *size_;
			bool fill_;
	};
}

#endif // CANVASDRAWRECTEVENT_H
