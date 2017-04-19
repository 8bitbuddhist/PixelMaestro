#include <gtkmm.h>
#include "../include/PixelGridDrawingArea.h"

int main (int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv);
	Gtk::Window window;
	window.set_title("PixelMaestro");
	//window.set_default_size(200, 200);

	PixelGridDrawingArea *pixelGridDrawingArea = new PixelGridDrawingArea(&window);
	Glib::signal_timeout().connect( sigc::mem_fun(pixelGridDrawingArea, &PixelGridDrawingArea::update), pixelGridDrawingArea->getMaestro()->getRefreshRate());

	return app->run(window);
}
