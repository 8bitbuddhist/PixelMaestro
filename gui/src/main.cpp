#include <gtkmm.h>
#include "drawingareas/Orientation.h"

int main (int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv);
	Gtk::Window window;
	window.set_title("PixelMaestro");
	//window.set_default_size(200, 200);

	Orientation *pixelGridDrawingArea = new Orientation(&window);

	// Refresh at 50Hz
	Glib::signal_timeout().connect( sigc::mem_fun(pixelGridDrawingArea, &PixelGridDrawingArea::update), 20);

	return app->run(window);
}
