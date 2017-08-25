#ifndef CANVASDRAWTEXTEVENT_H
#define CANVASDRAWTEXTEVENT_H

#include "../canvas.h"
#include "event.h"
#include "../canvas/fonts/font.h"
#include "../point.h"

namespace PixelMaestro {
	class CanvasDrawTextEvent : public Event
	{
		public:
			CanvasDrawTextEvent(unsigned long time, Canvas *canvas, Point *origin, Font *font, char *text, unsigned int numChars);
			void run();

		private:
			Canvas *canvas_;
			Point *origin_;
			Font *font_;
			char *text_;
			unsigned int num_chars_;
	};
}

#endif // CANVASDRAWTEXTEVENT_H
