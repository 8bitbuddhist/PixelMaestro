#include <cairomm/context.h>
#include <cmath>
#include "../../include/Colors.h"
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include "../../include/Maestro.h"
#include "../../include/drawingareas/SimplePixelGridDrawingArea.h"
#include <vector>

using namespace PixelMaestro;
using namespace std;
using namespace std::chrono;

SimplePixelGridDrawingArea::SimplePixelGridDrawingArea(Gtk::Window* parentWindow) {
    this->build_grid(parentWindow);
}

SimplePixelGridDrawingArea::SimplePixelGridDrawingArea(Gtk::Window* parentWindow, unsigned short rows, unsigned short columns) {
    num_rows_ = rows;
    num_columns_ = columns;

    this->build_grid(parentWindow);
}

void SimplePixelGridDrawingArea::build_grid(Gtk::Window* parentWindow) {
    // Add the grid to the Window
	box_ = Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 5);
	box_.pack_start(*this, true, true, 0);
	box_.show_all();
	parentWindow->add(box_);

	/*
        Adjust window to fit all Pixels according to the size of the drawing area.
        There has to be a smarter way to do this.
    */
	parentWindow->set_default_size((num_columns_ * pad_) + radius_,(num_rows_ * pad_) + radius_);
	parentWindow->set_resizable(false);
}

bool SimplePixelGridDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    // Draw a black rectangle behind the grid
    cr->rectangle(0, 0, 1000, 1000);
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->fill();

    /*
        Iterate through the Maestro and draw each Pixel.
        We first draw a representation of a Pixel as a circle (or arc), then fill in the arc with the Pixel's color.
        PAD_, RADIUS_, and OFFSET_ determine the padding, size, and relative origin of each circle respectively.
    */
    for (unsigned short section = 0; section < maestro_->getNumSections(); section++) {
        for (unsigned short row = 0; row < maestro_->getSection(section)->getLayout()->rows; row++) {
            for (unsigned short pixel = 0; pixel < maestro_->getSection(section)->getLayout()->columns; pixel++) {
                pixel_rgb_ = maestro_->getSection(section)->getPixelColor(maestro_->getSection(section)->getPixelIndex(row, pixel));
                float_rgb_ = RGBtoFloatRGB(pixel_rgb_);
                if (pixel_rgb_ != Colors::BLACK) {
                    cr->arc((double)(pixel * pad_) + offset_, (double)(row * pad_) + offset_, (double)radius_, 0.0, (double)(2 * M_PI));
                    cr->set_source_rgb(float_rgb_.r, float_rgb_.g, float_rgb_.b);
                    cr->fill();
                }
            }
        }
	}

    return true;
}
