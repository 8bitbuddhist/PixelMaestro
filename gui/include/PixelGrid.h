#include <chrono>
#include <Colors.h>
#include <gtkmm.h>
#include <Maestro.h>
#include <Pixel.h>
#include <PixelGridDrawingArea.h>
#include <Show.h>
#include <vector>

#ifndef PIXELGRID_H
#define PIXELGRID_H

using namespace PixelMaestro;
using namespace std;

class PixelGrid
{
	public:
		/** Default constructor */
		PixelGrid(Gtk::Window* parentWindow);

		Maestro* getMaestro();
		bool update();

	protected:

	private:
		// Maestro variables
		const unsigned short NUM_ROWS = 15;
		const unsigned short NUM_COLUMNS = 40;
		const unsigned int NUM_PIXELS = NUM_ROWS * NUM_COLUMNS;
		const unsigned short NUM_SECTIONS = 1;

		vector<Colors::RGB> colors_;
		vector<Pixel> pixels_;
		vector<Section> sections_;

		Maestro *maestro_;

		chrono::milliseconds runtime_;
		chrono::milliseconds start_time_;

		Gtk::Box mainBox_;
		PixelGridDrawingArea *drawingArea_;

		// TESTING
		vector<unsigned long> pattern_;
		vector<Show::Transition> transitions_;
		Show *show_;
};

#endif // PIXELGRID_H
