#ifndef CANVASCLEAREVENT_H
#define CANVASCLEAREVENT_H

#include "../canvas/canvas.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasClearEvent : Event {
		public:
			CanvasClearEvent(unsigned long time, Canvas *canvas);
			void run();

		private:
			Canvas *canvas_;
	};
}

#endif // CANVASCLEAREVENT_H
