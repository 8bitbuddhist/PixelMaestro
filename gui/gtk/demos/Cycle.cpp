#include "../include/Colors.h"
#include "../demos/Cycle.h"
#include <gtkmm/window.h>
#include "../include/Maestro.h"

using namespace PixelMaestro;
using namespace std;

Cycle::Cycle(Gtk::Window* parentWindow) : SimplePixelGridDrawingArea(parentWindow, num_rows_, 10) {
	colors_.resize(num_columns_);
	pixels_.resize(num_pixels_);
	sections_.resize(num_sections_);

	/*
        Initialize Section.
        This example renders colors from the center of the grid to the top and bottom.
    */
	sections_[0].setColors(Colors::COLORWHEEL, 12);
	sections_[0].setPixels(&pixels_[0], num_rows_, 10);
	sections_[0].setColorAnimation(Section::ColorAnimations::WAVE, true, Section::AnimationOrientations::HORIZONTAL);
	sections_[0].setCycleInterval(100);

	// Initialize maestro
	maestro_.setSections(&sections_[0], num_sections_);
}
