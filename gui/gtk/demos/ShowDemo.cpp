/*
    ShowDemo.h - Demonstrates controlling a Maestro using a Show.
*/

#include "../include/Colors.h"
#include <gtkmm/window.h>
#include "../demos/Orientation.h"
#include "../include/Show.h"
#include "ShowDemo.h"

ShowDemo::ShowDemo(Gtk::Window* parentWindow) : SimplePixelGridDrawingArea(parentWindow) {
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
	sections_[0].setCycleInterval(100);

	// Initialize maestro
	maestro_.setSections(&sections_[0], num_sections_);

	// Define Transitions
	int numTransitions = 2;
    transitions_.resize(numTransitions);
    transitions_[0].time = 1000;
    transitions_[0].action = std::bind(&Maestro::toggleRunning, this->getMaestro());

    transitions_[1].time = 1000;
    transitions_[1].action = std::bind(&Maestro::toggleRunning, this->getMaestro());

    show_.setTiming(Show::TimingModes::RELATIVE);
    show_.setTransitions(&transitions_[0], numTransitions);
    show_.toggleLooping();

	// Initialize Show
	show_.setMaestro(&maestro_);
}
