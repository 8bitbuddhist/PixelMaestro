#include "controller/maestrocontroller.h"
#include "maestrodrawingarea.h"
#include "simpledrawingarea.h"
#include <QPainter>
#include <vector>

/**
 * Constructor.
 * @param parent The parent QWidget.
 * @param maestro_controller The MaestroController rendered by this DrawingArea.
 */
SimpleDrawingArea::SimpleDrawingArea(QWidget* parent, MaestroController* maestro_controller) : MaestroDrawingArea(parent, maestro_controller) {
	this->maestro_controller_ = maestro_controller;
}

/**
 * Renders the Maestro using a simple, regular 2D grid.
 * @param event
 */
void SimpleDrawingArea::paintEvent(QPaintEvent *event) {
	// Paint Pixels (see http://doc.qt.io/qt-5/qtwidgets-widgets-analogclock-example.html)
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	Colors::RGB tmp_rgb;	// RGB output from each Pixel
	QColor tmp_color;		// tmpRGB converted to QColor
	QBrush tmp_brush;		// Brush used to paint tmpColor
	QRect tmp_rect;			// Size and location of the Pixel to draw using tmpBrush

	/*
	 * Note: This assumes we only have one section in the Maestro.
	 * If there's more than one, the last Section will overwrite the first.
	 * For more complex layouts, create a custom MaestroDrawingArea or add multiple SimpleDrawingAreas to the window.
	 */

	/*
	 * Render each Pixel in the Maestro by mapping its location in the grid to a location on the DrawingArea.
	 */
	this->resize_pixels();
	for (unsigned short section = 0; section < this->maestro_controller_->get_num_section_controllers(); section++) {
		for (unsigned short row = 0; row < this->maestro_controller_->get_section_controller(section)->get_section()->get_dimensions()->y; row++) {
			for (unsigned short pixel = 0; pixel < this->maestro_controller_->get_section_controller(section)->get_section()->get_dimensions()->x; pixel++) {
				tmp_rgb = this->maestro_controller_->get_section_controller(section)->get_section()->get_pixel_color(this->maestro_controller_->get_section_controller(section)->get_section()->get_pixel_index(pixel, row));
				tmp_color.setRgb(tmp_rgb.r, tmp_rgb.g, tmp_rgb.b);
				tmp_brush.setColor(tmp_color);
				tmp_brush.setStyle(Qt::BrushStyle::SolidPattern);

				/*
				 * Draw the Pixel.
				 * First, calculate the bounds of the Pixel.
				 * Then, set the color of the pen to the color of the Pixel.
				 * Finally, draw the Pixel to the screen.
				 */
				tmp_rect.setRect(pixel * pad_, row * pad_, radius_, radius_);
				painter.setBrush(tmp_brush);
				painter.setPen(Qt::PenStyle::NoPen);
				painter.drawEllipse(tmp_rect);
			}
		}
	}
}

/**
 * Resize the grid based on the number of rows and columns.
 * TODO: Improve dynamic scaling.
 */
void SimpleDrawingArea::resize_pixels() {
	int min_dimension, min_point;
	// Find the smallest dimension. We'll use this to determine whether (and in which direction) to reduce the size of the grid.
	if (this->width() < this->height()) {
		min_dimension = this->width();
	}
	else {
		min_dimension = this->height();
	}

	Point* dimensions = this->maestro_controller_->get_section_controller(0)->get_section()->get_dimensions();
	if (dimensions->y > dimensions->x) {
		min_point = dimensions->y;
	}
	else {
		min_point = dimensions->x;
	}

	radius_ = (min_dimension / min_point) / 2;
	pad_ = radius_ * 2;
	offset_ = pad_;
}
