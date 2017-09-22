#include "canvasclearevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. This Event clears a Canvas.
	 * @param time Time until the Event runs.
	 * @param canvas Canvas to clear.
	 */
	CanvasClearEvent::CanvasClearEvent(unsigned long time, BaseCanvas *canvas) : Event(time) {
		this->canvas_ = canvas;
	}

	void CanvasClearEvent::run() {
		canvas_->clear();
	}

}
