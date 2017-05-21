/*
    Orientation.h - Tests animation orientations.
*/

#include <gtkmm/window.h>
#include "SimplePixelGridDrawingArea.h"

#ifndef ORIENTATION_H
#define ORIENTATION_H

class Orientation : public SimplePixelGridDrawingArea {
    public:
        Orientation(Gtk::Window* parentWindow);
};

#endif // ORIENTATION_H
