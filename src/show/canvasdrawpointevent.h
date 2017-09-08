#ifndef CANVASDRAWPOINTEVENT_H
#define CANVASDRAWPOINTEVENT_H

#include "../canvas/canvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawPointEvent : Event {
		public:
			CanvasDrawPointEvent(unsigned long time, Canvas *canvas, Point* cursor);
			void run();

		private:
			Canvas* canvas_;
			Point* cursor_;
	};
}

#endif // CANVASDRAWPOINTEVENT_H
