/*
	PixelGridDrawingArea.h - Abstract class for rendering Pixels to a screen.
*/

#include <chrono>
#include "Colors.h"
#include <gtkmm/drawingarea.h>
#include "Maestro.h"

#ifndef PIXELGRIDDRAWINGAREA_H
#define PIXELGRIDDRAWINGAREA_H

using namespace PixelMaestro;
using namespace std;

class PixelGridDrawingArea : public Gtk::DrawingArea
{
    public:
        PixelGridDrawingArea();
        Maestro* getMaestro();
        bool update();

    protected:
        /// Stores a color as a Cairo-friendly float value.
        struct FloatRGB
        {
            double r;
            double g;
            double b;
        };

        /// Temporarily stores a Pixel's Colors::RGB value.
        Colors::RGB pixel_rgb_;
        /// Temporarily stores a Pixel's FloatRGB value.
        FloatRGB float_rgb_;
        /// Maestro controlling this grid.
        Maestro maestro_;
        /// The drawing area's current runtime.
        chrono::milliseconds runtime_;
        /// The drawing area's start time.
        chrono::milliseconds start_time_;

        /**
            Re-draws the drawing area. This method must be overriden by the inheriting class.

            @param cr Pointer to the Cairo context.
        */
        virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override = 0;
        FloatRGB RGBtoFloatRGB(Colors::RGB rgb);
};

#endif // PIXELGRIDDRAWINGAREA_H
