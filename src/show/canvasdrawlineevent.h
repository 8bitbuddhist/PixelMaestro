#ifndef CANVASDRAWLINEEVENT_H
#define CANVASDRAWLINEEVENT_H


#include "../canvas/canvas.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawLineEvent : public Event {
		public:
			CanvasDrawLineEvent(unsigned long time, Canvas* canvas, unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y);
			void run();

		private:
			Canvas* canvas_;
			unsigned short origin_x_, origin_y_;
			unsigned short target_x_, target_y_;
	};
}

#endif // CANVASDRAWLINEEVENT_H
