/*
    Orientation.h - Tests animation orientations.
*/

#include "Colors.h"
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include "Pixel.h"
#include "SimplePixelGridDrawingArea.h"
#include <vector>

#ifndef ORIENTATION_H
#define ORIENTATION_H

using namespace PixelMaestro;
using namespace std;

class Orientation : public SimplePixelGridDrawingArea {
    public:
        Orientation(Gtk::Window* parentWindow);
};

#endif // ORIENTATION_H
