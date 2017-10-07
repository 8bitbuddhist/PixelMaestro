#include "controller/maestrocontroller.h"
#include "window/settingsdialog.h"
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

	/*
	 * Render each Pixel in the Maestro by mapping its location in the grid to a location on the DrawingArea.
	 * Note: This assumes we only have one section in the Maestro.
	 * If there's more than one, the last Section will overwrite the first.
	 * For more complex layouts, create a custom MaestroDrawingArea or add multiple SimpleDrawingAreas to the window.
	 */
	uint16_t section = 0;
	if (last_pixel_count_ != maestro_controller_->get_section_controller(section)->get_section()->get_dimensions()->size()) {
		resizeEvent(nullptr);
		last_pixel_count_ = maestro_controller_->get_section_controller(section)->get_section()->get_dimensions()->size();
	}

	for (uint16_t row = 0; row < maestro_controller_->get_section_controller(section)->get_section()->get_dimensions()->y; row++) {
		for (uint16_t pixel = 0; pixel < maestro_controller_->get_section_controller(section)->get_section()->get_dimensions()->x; pixel++) {			
			tmp_rgb_ = maestro_controller_->get_maestro()->get_pixel_color(section, maestro_controller_->get_section_controller(section)->get_section()->get_pixel_index(pixel, row));
			tmp_color_.setRgb(tmp_rgb_.r, tmp_rgb_.g, tmp_rgb_.b);
			tmp_brush_.setColor(tmp_color_);
			tmp_brush_.setStyle(Qt::BrushStyle::SolidPattern);

			/*
			 * Draw the Pixel.
			 * First, calculate the bounds of the Pixel.
			 * Then, set the color of the pen to the color of the Pixel.
			 * Finally, draw the Pixel to the screen.
			 */
			tmp_rect_.setRect(pixel * pad_, row * pad_, radius_, radius_);
			painter.setBrush(tmp_brush_);
			painter.setPen(Qt::PenStyle::NoPen);

			// Determine which shape to draw
			switch (settings_.value(SettingsDialog::pixel_shape).toInt()) {
				case 0:	// Circle
					painter.drawEllipse(tmp_rect_);
					break;
				case 1:	// Rect
					painter.drawRect(tmp_rect_);
					break;
			}
		}
	}
}

/**
 * Resize the grid based on the number of rows and columns.
 */
void SimpleDrawingArea::resizeEvent(QResizeEvent *event) {
	QSize widget_size = this->size();

	// Find the optimal radius of each Pixel
	uint8_t max_width = widget_size.width() / maestro_controller_->get_section_controller(0)->get_section()->get_dimensions()->x;
	uint8_t max_height = widget_size.height() / maestro_controller_->get_section_controller(0)->get_section()->get_dimensions()->y;

	// Find the smaller dimension
	if (max_width < max_height) {
		radius_ = max_width;
	}
	else {
		radius_ = max_height;
	}

	pad_ = radius_;

	// Calculate radius
	switch (settings_.value(SettingsDialog::pixel_padding).toInt()) {
		case 1:	// Small
			radius_ *= 0.8;
			break;
		case 2:	// Medium
			radius_ *= 0.6;
			break;
		case 3:	// Large
			radius_ *= 0.4;
			break;
	}
}
