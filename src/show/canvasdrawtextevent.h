#ifndef CANVASDRAWTEXTEVENT_H
#define CANVASDRAWTEXTEVENT_H

#include "../canvas/canvas.h"
#include "../canvas/fonts/font.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawTextEvent : public Event
	{
		public:
			CanvasDrawTextEvent(unsigned long time, Canvas* canvas, Point* origin, Font* font, char* text);
			void run();

		private:
			Canvas* canvas_;
			Point* origin_;
			Font* font_;
			char* text_;
	};
}

#endif // CANVASDRAWTEXTEVENT_H
