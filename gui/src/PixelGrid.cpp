#include <cairomm/context.h>
#include <cmath>
#include <Colors.h>
#include <gtkmm/box.h>
#include <gtkmm/container.h>
#include <gtkmm/window.h>
#include <Maestro.h>
#include <PixelGrid.h>
#include <PixelGridDrawingArea.h>
#include <Show.h>
#include <vector>
#include <Utility.h>

using namespace PixelMaestro;
using namespace std;
using namespace std::chrono;

PixelGrid::PixelGrid(Gtk::Window* parentWindow) {
	// Adjust window to fit all Pixels according to the size of the drawing area.
	// There has to be a better way to do this.
	parentWindow->set_default_size(
		(NUM_COLUMNS * PixelGridDrawingArea::PAD) + PixelGridDrawingArea::RADIUS,
		(NUM_ROWS * PixelGridDrawingArea::PAD) + PixelGridDrawingArea::RADIUS
	);
	parentWindow->set_resizable(false);

	// Initialize timer
	start_time_ = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch()
	);

	// Initialize Maestro components.
	colors_.resize(NUM_COLUMNS);
	pixels_.resize(NUM_PIXELS * 2);
	sections_.resize(NUM_SECTIONS);

	//Colors::generateScalingColorArray(&colors_[0], Colors::COLORWHEEL[rand() % 12], NUM_COLUMNS, 50, true);
	Colors::generateScalingColorArray(&colors_[0], Colors::AZURE, Colors::RED, NUM_COLUMNS, true);
	sections_[0].setColors(&colors_[0], NUM_COLUMNS);
	//sections_[0].setColors(Colors::COLORWHEEL, 12);
	sections_[0].setPixels(&pixels_[0], NUM_ROWS, NUM_COLUMNS);
	sections_[0].setColorAnimation(Section::ColorAnimations::WAVE, true);
	sections_[0].setCycleSpeed(500);

	// Handle overlay
	Colors::RGB overlayColors[] = {Colors::WHITE};
	Section * overlay = new Section(&pixels_[NUM_PIXELS], NUM_ROWS, NUM_COLUMNS);
	pattern_ = {

		// Pixel
		Utility::binaryToInt("1111001111101000101111101000000000000000", 40),
		Utility::binaryToInt("1000100010001000101000001000000000000000", 40),
		Utility::binaryToInt("1000100010000101001000001000000000000000", 40),
		Utility::binaryToInt("1111000010000010001111101000000000000000", 40),
		Utility::binaryToInt("1000000010000101001000001000000000000000", 40),
		Utility::binaryToInt("1000000010001000101000001000000000000000", 40),
		Utility::binaryToInt("1000001111101000101111101111100000000000", 40),

		// Maestro
		Utility::binaryToInt("1000100010001111100111101111101110001110", 40),
		Utility::binaryToInt("1101100101001000001000000010001001010001", 40),
		Utility::binaryToInt("1010101000101000001000000010001001010001", 40),
		Utility::binaryToInt("1000101111101111100111000010001110010001", 40),
		Utility::binaryToInt("1000101000101000000000100010001001010001", 40),
		Utility::binaryToInt("1000101000101000000000100010001001010001s", 40),
		Utility::binaryToInt("1000101000101111101111000010001001001110", 40)

		/*Utility::binaryToInt("1110011101000001011111010000001100011000100011111001110111001110001100", 70),
		Utility::binaryToInt("1001001000100010010000010000001010101001010010000010000010001001010010", 70),
		Utility::binaryToInt("1001001000010100010000010000001001001010001010000010000010001001010010", 70),
		Utility::binaryToInt("1110001000001000011111010000001000001011111011111001100010001110010010", 70),
		Utility::binaryToInt("1000001000010100010000010000001000001010001010000000010010001001010010", 70),
		Utility::binaryToInt("1000001000100010010000010000001000001010001010000000010010001001010010", 70),
		Utility::binaryToInt("1000011101000001011111011111001000001010001011111011100010001001001100", 70)*/
	};
	overlay->setColors(&overlayColors[0], 1);
	overlay->setColorAnimation(Section::ColorAnimations::PATTERN);
	overlay->setRefreshRate(1000);
	overlay->setCycleSpeed(1000);
	overlay->setPattern(&pattern_[0], 14, 1);

	sections_[0].setOverlay(overlay, Colors::MixMode::OVERLAY);

	// Initialize maestro
	maestro_ = new Maestro(&sections_[0], NUM_SECTIONS);

	mainBox_ = Gtk::Box(Gtk::Orientation::ORIENTATION_VERTICAL, 5);
	parentWindow->add(mainBox_);
	drawingArea_ = new PixelGridDrawingArea(maestro_);
	mainBox_.pack_start(*drawingArea_, true, true, 0);
	mainBox_.show_all();

	/*
	// TESTING: Create and run a show
	struct Show::Transition tr_change_speed = {
		.time = 3000,
		.action = Show::Actions::SET_UPDATE_SPEED,
		.opts = [](){ Show::Opts o{};
			o.grid = true,
			o.gridNum = 0,
			o.val1 = 20;
		return o; }()
	};

	struct Show::Transition tr_change_animation = {
		.time = 9000,
		.action = Show::Actions::SET_COLOR_ANIMATION,
		.opts = [](){ Show::Opts o{};
			o.grid = true,
			o.gridNum = 0,
			o.gridAnimation = Grid::ColorAnimations::BLINK;
		return o; }()
	};

	struct Show::Transition tr_toggle_fade = {
		.time = 6000,
		.action = Show::Actions::TOGGLE_FADE,
		.opts = [](){ Show::Opts o{};
			o.grid = true,
			o.gridNum = 0;
		return o; }()
	};

	transitions_.push_back(tr_change_speed);
	transitions_.push_back(tr_toggle_fade);
	transitions_.push_back(tr_change_animation);
	show_ = new Show(maestro_, &transitions_[0], 3);*/
}

Maestro* PixelGrid::getMaestro() {
	return maestro_;
}

bool PixelGrid::update() {
	runtime_ = duration_cast<milliseconds>(
		system_clock::now().time_since_epoch() - start_time_
	);

	// Update maestro
	maestro_->update(runtime_.count());
	//show_->update(runtime_.count());

	drawingArea_->queue_draw();

	return true;
}
