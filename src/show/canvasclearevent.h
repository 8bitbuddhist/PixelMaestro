#ifndef CANVASCLEAREVENT_H
#define CANVASCLEAREVENT_H

#include "../canvas/basecanvas.h"
#include "event.h"

namespace PixelMaestro {
	class CanvasClearEvent : Event {
		public:
			CanvasClearEvent(unsigned long time, BaseCanvas *canvas);
			void run();

		private:
			BaseCanvas *canvas_;
	};
}

#endif // CANVASCLEAREVENT_H
