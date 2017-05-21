/*
    ShowDemo.h - Demonstrates controlling a Maestro using a Show.
*/

#ifndef SHOWDEMO_H
#define SHOWDEMO_H

#include <gtkmm/window.h>
#include "SimplePixelGridDrawingArea.h"
#include "Show.h"
#include <vector>

using namespace PixelMaestro;
using namespace std;

class ShowDemo : public SimplePixelGridDrawingArea {
    public:
        ShowDemo(Gtk::Window* parentWindow);

    private:
        vector<Show::Transition> transitions_;
};

#endif // SHOWDEMO_H
