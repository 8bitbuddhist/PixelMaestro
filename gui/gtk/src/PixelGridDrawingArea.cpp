#include <chrono>
#include "PixelGridDrawingArea.h"
#include "Maestro.h"

using namespace PixelMaestro;
using namespace std::chrono;

PixelGridDrawingArea::PixelGridDrawingArea() {
    // Initialize timer
	start_time_ = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);
}

/**
    Returns the Maestro controlling this area.

    @return Controlling Maestro.
*/
Maestro* PixelGridDrawingArea::getMaestro() {
    return &maestro_;
}


/**
    Converts a Colors::RGB value to a FloatRGB value, which Cairo can use to draw to the screen.

    @param rgb The Colors::RGB value to convert.
    @return The equivalent FloatRGB value.
*/
PixelGridDrawingArea::FloatRGB PixelGridDrawingArea::RGBtoFloatRGB(Colors::RGB rgb) {
    return FloatRGB {
        (double)rgb.r / 255,
        (double)rgb.g / 255,
        (double)rgb.b / 255
    };
}

/**
    Refreshes the PixelGrid (and the Maestro).
*/
bool PixelGridDrawingArea::update() {
	runtime_ = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch() - start_time_
	);

	// Update Maestro or Show
	if (show_.getMaestro() == &maestro_) {
        show_.update(runtime_.count());
	}
	else {
        maestro_.update(runtime_.count());
    }

	this->queue_draw();

	return true;
}
