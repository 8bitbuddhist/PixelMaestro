#include "overlaysetoptionsevent.h"

namespace PixelMaestro {
	/**
	 * Constructor. Modifies an Overlay.
	 * @param time Time until the Event runs.
	 * @param overlay Overlay to modify.
	 * @param mix_mode The Overlay's mixing mode.
	 * @param alpha The Overlay's transparency.
	 */
	OverlaySetOptionsEvent::OverlaySetOptionsEvent(unsigned long time, Section::Overlay* overlay, Colors::MixMode mix_mode, unsigned char alpha) : Event(time) {
		this->overlay_ = overlay;
		this->mix_mode_ = mix_mode;
		this->alpha_ = alpha;
	}

	void OverlaySetOptionsEvent::run() {
		overlay_->mix_mode = mix_mode_;
		overlay_->alpha = alpha_;
	}
}
