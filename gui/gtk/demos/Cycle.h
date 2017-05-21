/*
    Cycle.h - Displays a simple Cycle animation.
*/

#include "Colors.h"
#include <gtkmm/window.h>
#include "SimplePixelGridDrawingArea.h"

#ifndef CYCLE_H
#define CYCLE_H

class Cycle : public SimplePixelGridDrawingArea {
    public:
        Cycle(Gtk::Window* parentWindow);
};

#endif // CYCLE_H
