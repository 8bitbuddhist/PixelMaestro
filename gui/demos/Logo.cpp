#include "../include/Colors.h"
#include <gtkmm/window.h>
#include "../demos/Logo.h"

using namespace PixelMaestro;

Logo::Logo(Gtk::Window* parentWindow) : SimplePixelGridDrawingArea(parentWindow) {
    // Initialize collections
	colors_.resize(num_columns_);
	pixels_.resize(num_pixels_ * 2);
	sections_.resize(num_sections_ * 2);

	/*
        Initialize Sections.
        Section 1 renders the colors that will display over the logo.
	*/
	sections_[0].setColors(Colors::COLORWHEEL, 12);
	sections_[0].setPixels(&pixels_[0], num_rows_, num_columns_);
	sections_[0].setColorAnimation(Section::ColorAnimations::WAVE, true);
	sections_[0].setCycleInterval(200);

	/*
        Section 2 is the overlay.
        It renders the pattern to the grid (which in this case, displays the text "PixelMaestro").
        The OVERLAY mix mode works by multiplying the color values of the base and overlaying Pixels.
        Setting the overlay to only show the color White (255, 255, 255) means the colors from Section 1 render at full brightness.
	*/
	overlay_colors_ = {Colors::WHITE};
	sections_[1].setPixels(&pixels_[num_pixels_], num_rows_, num_columns_);
	sections_[1].setColors(&overlay_colors_[0], 1);
	sections_[1].setColorAnimation(Section::ColorAnimations::PATTERN);
	sections_[1].setRefreshInterval(1000);
	sections_[1].setCycleInterval(1000);
	sections_[1].setPattern(pattern_, 14, 40, 1);

	sections_[0].setOverlay(&sections_[1], Colors::MixMode::OVERLAY, 1.0);

	// Initialize maestro
	maestro_.setSections(&sections_[0], num_sections_);
}
