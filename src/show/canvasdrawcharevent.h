#ifndef CANVASDRAWCHAREVENT_H
#define CANVASDRAWCHAREVENT_H

#include "../canvas/canvas.h"
#include "../canvas/fonts/font.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawCharEvent : public Event {
		public:
			CanvasDrawCharEvent(unsigned long time, Canvas* canvas, Point* origin, Font* font, char character);
			void run();

		private:
			Canvas* canvas_;
			Point* origin_;
			Font* font_;
			char character_;
	};
}

#endif // CANVASDRAWCHAREVENT_H
