#include "../include/Colors.h"
#include <gtkmm/window.h>
#include "../include/Maestro.h"
#include "../demos/Orientation.h"

using namespace PixelMaestro;
using namespace std;
using namespace std::chrono;

// Resize the array so that it's 10x40
Orientation::Orientation(Gtk::Window* parentWindow) : SimplePixelGridDrawingArea(parentWindow, 40, 10) {
	colors_.resize(num_columns_);
	pixels_.resize(num_pixels_);
	sections_.resize(num_sections_);

	/*
        Initialize Section.
        This example renders colors from the center of the grid to the top and bottom.
    */
	sections_[0].setColors(Colors::COLORWHEEL, 12);
	sections_[0].setPixels(&pixels_[0], num_rows_, num_columns_);
	sections_[0].setColorAnimation(Section::ColorAnimations::MERGE, true, Section::AnimationOrientations::VERTICAL);
	sections_[0].setCycleSpeed(100);

	// Initialize maestro
	maestro_.setSections(&sections_[0], num_sections_);
}
