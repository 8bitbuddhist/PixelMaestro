#include <chrono>
#include "Colors.h"
#include <gtkmm/box.h>
#include <gtkmm/drawingarea.h>
#include <gtkmm/window.h>
#include "Maestro.h"
#include "Pixel.h"
#include <vector>

#ifndef PIXELGRIDDRAWINGAREA_H
#define PIXELGRIDDRAWINGAREA_H

using namespace PixelMaestro;
using namespace std;

class PixelGridDrawingArea : public Gtk::DrawingArea
{
    public:
        PixelGridDrawingArea(Gtk::Window* parentWindow);
        Maestro* getMaestro();
        bool update();

    protected:
        bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    private:
        struct FloatRGB {
            double r;
            double g;
            double b;
        };

        // Window/drawing area variables
        Gtk::Box box_;
        static const unsigned short RADIUS_ = 5;
        static const unsigned short PAD_ = RADIUS_ * 3;
        static const unsigned short OFFSET_ = RADIUS_ * 2;

        // Maestro variables
        Maestro* maestro_;
        const unsigned short NUM_ROWS_ = 15;
        const unsigned short NUM_COLUMNS_ = 50;
        const unsigned short NUM_SECTIONS_ = 1;
        const unsigned int NUM_PIXELS_ = NUM_ROWS_ * NUM_COLUMNS_;

        // Collections
        vector<Colors::RGB> colors_;
        vector<Pixel> pixels_;
        vector<Section> sections_;
        vector<Colors::RGB> overlay_colors_;

        // Variables for storing temporary/volatile data
        Colors::RGB pixel_rgb_;
        FloatRGB float_rgb_;
        FloatRGB RGBtoFloatRGB(Colors::RGB rgb);
        chrono::milliseconds runtime_;
        chrono::milliseconds start_time_;
        vector<unsigned long> pattern_;

        static unsigned long long binaryToInt(const char* binary, unsigned int numChars);
};

#endif // PIXELGRIDDRAWINGAREA_H
