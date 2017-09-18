#ifndef CANVASDRAWPOINTEVENT_H
#define CANVASDRAWPOINTEVENT_H

#include "../canvas/canvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawPointEvent : Event {
		public:
			CanvasDrawPointEvent(unsigned long time, Canvas *canvas, unsigned short cursor_x, unsigned short cursor_y);
			void run();

		private:
			Canvas* canvas_;
			unsigned short cursor_x_, cursor_y_;
	};
}

#endif // CANVASDRAWPOINTEVENT_H
