#ifndef CANVASDRAWTEXTEVENT_H
#define CANVASDRAWTEXTEVENT_H

#include "../canvas/basecanvas.h"
#include "../canvas/fonts/font.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawTextEvent : public Event
	{
		public:
			CanvasDrawTextEvent(unsigned long time, BaseCanvas* canvas, unsigned short origin_x, unsigned short origin_y, Font* font, char* text);
			void run();

		private:
			BaseCanvas* canvas_;
			unsigned short origin_x_, origin_y_;
			Font* font_;
			char* text_;
	};
}

#endif // CANVASDRAWTEXTEVENT_H
