#include <gtkmm.h>
#include "../demos/Logo.h"
#include "../demos/Orientation.h"

int main (int argc, char *argv[])
{
	auto app = Gtk::Application::create(argc, argv);
	Gtk::Window window;
	window.set_title("PixelMaestro");
	//window.set_default_size(200, 200);

	//Logo *pixelGridDrawingArea = new Logo(&window);
	Orientation *pixelGridDrawingArea = new Orientation(&window);

	// Refresh at 50Hz
	Glib::signal_timeout().connect( sigc::mem_fun(pixelGridDrawingArea, &PixelGridDrawingArea::update), 20);

	return app->run(window);
}
