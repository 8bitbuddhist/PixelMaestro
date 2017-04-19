#include <cairomm/context.h>
#include <chrono>
#include <cmath>
#include "Colors.h"
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include "Maestro.h"
#include "../include/PixelGridDrawingArea.h"
#include <vector>

using namespace PixelMaestro;
using namespace std;
using namespace std::chrono;

PixelGridDrawingArea::PixelGridDrawingArea(Gtk::Window* parentWindow) {
    // Initialize timer
	start_time_ = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);

	// Initialize collections
	colors_.resize(NUM_COLUMNS_);
	pixels_.resize(NUM_PIXELS_ * 2);
	sections_.resize(NUM_SECTIONS_);

	// Initialize Section
	sections_[0].setColors(Colors::COLORWHEEL, 12);
	sections_[0].setPixels(&pixels_[0], NUM_ROWS_, NUM_COLUMNS_);
	sections_[0].setColorAnimation(Section::ColorAnimations::WAVE, true);
	sections_[0].setCycleSpeed(500);

	// Initialize maestro
	maestro_ = new Maestro(&sections_[0], NUM_SECTIONS_);

    // Adjust window to fit all Pixels according to the size of the drawing area.
	// There has to be a better way to do this.
	parentWindow->set_default_size((NUM_COLUMNS_ * PAD_) + RADIUS_,(NUM_ROWS_ * PAD_) + RADIUS_);
	parentWindow->set_resizable(false);

	// Add the grid to the Window
	box_ = Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 5);
	box_.pack_start(*this, true, true, 0);
	box_.show_all();
	parentWindow->add(box_);
}

Maestro* PixelGridDrawingArea::getMaestro() {
    return maestro_;
}

bool PixelGridDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // Draw a black rectangle behind the grid
    cr->rectangle(0, 0, 1000, 1000);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->fill();
    // Iterate through the Maestro and draw each Pixel
    for (unsigned short section = 0; section < maestro_->getNumSections(); section++) {
        for (unsigned short row = 0; row < maestro_->getSection(section)->getLayout()->rows; row++) {
            for (unsigned short pixel = 0; pixel < maestro_->getSection(section)->getLayout()->columns; pixel++) {
                pixel_rgb_ = maestro_->getSection(section)->getPixelColor(maestro_->getSection(section)->getPixelIndex(row, pixel));
                float_rgb_ = RGBtoFloatRGB(pixel_rgb_);
                //if (pixel_rgb_ != Colors::BLACK) {
                    cr->arc((double)(pixel * PAD_) + OFFSET_, (double)(row * PAD_) + OFFSET_, (double)RADIUS_, 0.0, (double)(2 * M_PI));
                    cr->set_source_rgb(float_rgb_.r, float_rgb_.g, float_rgb_.b);
                    cr->fill();
                //}
            }
        }
	}

    return true;
}

PixelGridDrawingArea::FloatRGB PixelGridDrawingArea::RGBtoFloatRGB(Colors::RGB rgb) {
    return FloatRGB {
        (double)rgb.r / 255,
        (double)rgb.g / 255,
        (double)rgb.b / 255
    };
}

bool PixelGridDrawingArea::update() {
	runtime_ = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch() - start_time_
	);

	// Update maestro
	maestro_->update(runtime_.count());

	this->queue_draw();

	return true;
}
