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
			painter.drawEllipse(tmp_rect_);
		}
	}
}

/**
 * Resize the grid based on the number of rows and columns.
 */
void SimpleDrawingArea::resizeEvent(QResizeEvent *event) {
	/*
	 * Check to see if either axis is out of bounds.
	 * If so, resize the grid.
	 */
	QSize widget_size = this->size();

	// Find the optimal radius
	int optimal_width = ((widget_size.width() - pad_) / maestro_controller_->get_section_controller(0)->get_section()->get_dimensions()->x) / 2;
	int optimal_height = ((widget_size.height() - pad_) / maestro_controller_->get_section_controller(0)->get_section()->get_dimensions()->y) / 2;

	// Apply the smallest optimal radius, then recalculate the pad and offset.
	if (optimal_width < optimal_height) {
		radius_ = optimal_width;
	}
	else {
		radius_ = optimal_height;
	}

	switch (settings_.value(SettingsDialog::interface_padding).toInt()) {
		case 0:	// None
			pad_ = radius_;
			break;
		case 1:	// Small
			pad_ = radius_ + (radius_ / 2);
			break;
		case 2:	// Medium
			pad_ = radius_ * 2;
			break;
		case 3:	// Large
			pad_ = radius_ * 3;
			break;
	}
}
