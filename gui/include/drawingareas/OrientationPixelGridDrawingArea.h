/*
    OrientationPixelGridDrawingArea.h - Test animation orientation.
*/

#include "Colors.h"
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include "Pixel.h"
#include "PixelGridDrawingArea.h"
#include <vector>

#ifndef ORIENTATIONPIXELGRIDDRAWINGAREA_H
#define ORIENTATIONPIXELGRIDDRAWINGAREA_H

using namespace PixelMaestro;
using namespace std;

class OrientationPixelGridDrawingArea : public PixelGridDrawingArea {
    public:
        OrientationPixelGridDrawingArea(Gtk::Window* parentWindow);

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    private:
        // Window/drawing area variables
        Gtk::Box box_;
        static const unsigned short RADIUS_ = 5;
        static const unsigned short PAD_ = RADIUS_ * 3;
        static const unsigned short OFFSET_ = RADIUS_ * 2;

        // Maestro variables
        /// The number of rows in the drawing area.
        const unsigned short NUM_ROWS_ = 15;
        /// The number of columns in the drawing area.
        const unsigned short NUM_COLUMNS_ = 50;
        /// The number of Sections in the drawing area.
        const unsigned short NUM_SECTIONS_ = 1;
        /// The number of Pixels in the drawing area (equivalent to NUM_ROWS_ * NUM_COLUMNS_).
        const unsigned int NUM_PIXELS_ = NUM_ROWS_ * NUM_COLUMNS_;

        // Collections
        vector<Colors::RGB> colors_;
        vector<Pixel> pixels_;
        vector<Section> sections_;
};

#endif // ORIENTATIONPIXELGRIDDRAWINGAREA_H
