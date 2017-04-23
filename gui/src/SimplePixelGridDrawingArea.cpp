#include <cairomm/context.h>
#include <chrono>
#include <cmath>
#include "Colors.h"
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include "Maestro.h"
#include "../include/SimplePixelGridDrawingArea.h"
#include <vector>

using namespace PixelMaestro;
using namespace std;
using namespace std::chrono;

SimplePixelGridDrawingArea::SimplePixelGridDrawingArea(Gtk::Window* parentWindow) {
	// Initialize collections
	colors_.resize(NUM_COLUMNS_);
	//pixels_.resize(NUM_PIXELS_);
	//sections_.resize(NUM_SECTIONS_);
	pixels_.resize(NUM_PIXELS_ * 2);
	sections_.resize(NUM_SECTIONS_ * 2);

	// Initialize Section
	/*
	sections_[0].setColors(Colors::COLORWHEEL, 12);
	sections_[0].setPixels(&pixels_[0], NUM_ROWS_, NUM_COLUMNS_);
	sections_[0].setColorAnimation(Section::ColorAnimations::MERGE);
	sections_[0].setCycleSpeed(500);
	*/

    //Colors::generateScalingColorArray(&colors_[0], Colors::AZURE, Colors::RED, NUM_COLUMNS_, true);
	//sections_[0].setColors(&colors_[0], NUM_COLUMNS_);
	sections_[0].setColors(Colors::COLORWHEEL, 12);
	sections_[0].setPixels(&pixels_[0], NUM_ROWS_, NUM_COLUMNS_);
	sections_[0].setColorAnimation(Section::ColorAnimations::WAVE, true);
	sections_[0].setCycleSpeed(200);

	// Handle overlay
	overlay_colors_ = {Colors::WHITE};
	sections_[1].setPixels(&pixels_[NUM_PIXELS_], NUM_ROWS_, NUM_COLUMNS_);
	pattern_ = {

		// Pixel
		1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

		// Maestro
		1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0,
		1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0
	};
	sections_[1].setColors(&overlay_colors_[0], 1);
	sections_[1].setColorAnimation(Section::ColorAnimations::PATTERN);
	sections_[1].setRefreshRate(1000);
	sections_[1].setCycleSpeed(1000);
	sections_[1].setPattern(&pattern_[0], 14, 40, 1);

	sections_[0].setOverlay(&sections_[1], Colors::MixMode::OVERLAY, 1.0);

	// Initialize maestro
	maestro_ = new Maestro(&sections_[0], NUM_SECTIONS_);

	// Add the grid to the Window
	box_ = Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 5);
	box_.pack_start(*this, true, true, 0);
	box_.show_all();
	parentWindow->add(box_);

	// Adjust window to fit all Pixels according to the size of the drawing area.
	// There has to be a better way to do this.
	parentWindow->set_default_size((NUM_COLUMNS_ * PAD_) + RADIUS_,(NUM_ROWS_ * PAD_) + RADIUS_);
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
                    cr->arc((double)(pixel * PAD_) + OFFSET_, (double)(row * PAD_) + OFFSET_, (double)RADIUS_, 0.0, (double)(2 * M_PI));
                    cr->set_source_rgb(float_rgb_.r, float_rgb_.g, float_rgb_.b);
                    cr->fill();
                }
            }
        }
	}

    return true;
}

/**
    Converts a binary representation of a Pattern row to a value that the Pattern can actually use.

    @param binary String representation of a Pattern row as binary.
    @param numChars The number of characters in the string.
    @return The bitmasked Pattern value.
*/
unsigned long long SimplePixelGridDrawingArea::binaryToInt(const char* binary, unsigned int numChars) {
    unsigned long long result = 0;
    for (unsigned int i = 0; i < numChars; i++) {
        if (binary[i] == '1') {
            //result += pow(2, (numChars - 1) - i);
            result += pow(2, i);
        }
    }
    return result;
}

void SimplePixelGridDrawingArea::encodeFrame(bool *boolArray, unsigned char *charArray, unsigned short rows, unsigned short columns, unsigned short frames) {
    // Index of the active column. Resets to 0 when we hit 8 columns.
    unsigned short columnIndex = 0;

    // Index of the active chunk.
    unsigned short chunkIndex = 0;

    // If the number of chunks doesn't evenly match the number of columns, we need to pad out the remainder.
    unsigned short remainder = columns % 8;

    // Iterate through the array and create each chunk.
    for (unsigned short row = 0; row < rows; row++) {
        for (unsigned short column = 0; column < columns; column++) {
            // Move to the next chunk
            if (column % 8 == 0) {
                columnIndex = 0;
                chunkIndex++;
            }
        }
    }
}
