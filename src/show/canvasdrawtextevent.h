#ifndef CANVASDRAWTEXTEVENT_H
#define CANVASDRAWTEXTEVENT_H

#include "../canvas/colorcanvas.h"
#include "../canvas/fonts/font.h"
#include "../core/point.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasDrawTextEvent : public Event
	{
		public:
			CanvasDrawTextEvent(unsigned long time, BaseCanvas* canvas, unsigned short origin_x, unsigned short origin_y, Font* font, char* text);
			CanvasDrawTextEvent(unsigned long time, ColorCanvas* canvas, Colors::RGB color, unsigned short origin_x, unsigned short origin_y, Font* font, char* text);
			void run();

		private:
			BaseCanvas* canvas_;
			Colors::RGB color_;
			bool is_color_canvas_ = false;
			unsigned short origin_x_, origin_y_;
			Font* font_;
			char* text_;
	};
}

#endif // CANVASDRAWTEXTEVENT_H
