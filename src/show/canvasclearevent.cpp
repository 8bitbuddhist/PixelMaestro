#include "canvasclearevent.h"

namespace PixelMaestro {
	CanvasClearEvent::CanvasClearEvent(unsigned long time, Canvas *canvas) : Event(time) {
		this->canvas_ = canvas;
	}

	void CanvasClearEvent::run() {
		canvas_->clear();
	}

}
