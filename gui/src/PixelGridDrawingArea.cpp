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
		binaryToInt("1111001111101000101111101000000000000000", 40),
		binaryToInt("1000100010001000101000001000000000000000", 40),
		binaryToInt("1000100010000101001000001000000000000000", 40),
		binaryToInt("1111000010000010001111101000000000000000", 40),
		binaryToInt("1000000010000101001000001000000000000000", 40),
		binaryToInt("1000000010001000101000001000000000000000", 40),
		binaryToInt("1000001111101000101111101111100000000000", 40),

		// Maestro
		binaryToInt("1000100010001111100111101111101110001110", 40),
		binaryToInt("1101100101001000001000000010001001010001", 40),
		binaryToInt("1010101000101000001000000010001001010001", 40),
		binaryToInt("1000101111101111100111000010001110010001", 40),
		binaryToInt("1000101000101000000000100010001001010001", 40),
		binaryToInt("1000101000101000000000100010001001010001s", 40),
		binaryToInt("1000101000101111101111000010001001001110", 40)

		/*binaryToInt("1110011101000001011111010000001100011000100011111001110111001110001100", 70),
		binaryToInt("1001001000100010010000010000001010101001010010000010000010001001010010", 70),
		binaryToInt("1001001000010100010000010000001001001010001010000010000010001001010010", 70),
		binaryToInt("1110001000001000011111010000001000001011111011111001100010001110010010", 70),
		binaryToInt("1000001000010100010000010000001000001010001010000000010010001001010010", 70),
		binaryToInt("1000001000100010010000010000001000001010001010000000010010001001010010", 70),
		binaryToInt("1000011101000001011111011111001000001010001011111011100010001001001100", 70)*/
	};
	sections_[1].setColors(&overlay_colors_[0], 1);
	sections_[1].setColorAnimation(Section::ColorAnimations::PATTERN);
	sections_[1].setRefreshRate(1000);
	sections_[1].setCycleSpeed(1000);
	sections_[1].setPattern(&pattern_[0], 14, 1);

	sections_[0].setOverlay(&sections_[1], Colors::MixMode::OVERLAY, 1.0);

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


unsigned long long PixelGridDrawingArea::binaryToInt(const char* binary, unsigned int numChars) {
    unsigned long long result = 0;
    for (unsigned int i = 0; i < numChars; i++) {
        if (binary[i] == '1') {
            //result += pow(2, (numChars - 1) - i);
            result += pow(2, i);
        }
    }
    return result;
}
