/*
    SimplePixelGridDrawingArea.h - Renders the Maestro to a plain 2D Pixel grid.
*/

#include "Colors.h"
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include "Pixel.h"
#include "PixelGridDrawingArea.h"
#include <vector>

#ifndef SIMPLEPIXELGRIDDRAWINGAREA_H
#define SIMPLEPIXELGRIDDRAWINGAREA_H

using namespace PixelMaestro;
using namespace std;

class SimplePixelGridDrawingArea : public PixelGridDrawingArea {
    public:
        SimplePixelGridDrawingArea(Gtk::Window* parentWindow);
        SimplePixelGridDrawingArea(Gtk::Window* parentWindow, unsigned short rows, unsigned short columns);

    protected:
        // Window/drawing area variables
        Gtk::Box box_;
        static const unsigned short radius_ = 5;
        static const unsigned short pad_ = radius_ * 3;
        static const unsigned short offset_ = radius_ * 2;

        // Maestro/grid variables
        unsigned short num_rows_ = 15;
        unsigned short num_columns_ = 50;
        unsigned short num_sections_ = 1;
        unsigned int num_pixels_ = num_rows_ * num_columns_;

        vector<Colors::RGB> colors_;
        vector<Pixel> pixels_;
        vector<Section> sections_;

        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    private:
        void build_grid(Gtk::Window* parentWindow);
};

#endif // SIMPLEPIXELGRIDDRAWINGAREA_H
