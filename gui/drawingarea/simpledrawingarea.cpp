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

void SimpleDrawingArea::draw_section(QPainter* painter, uint8_t section_index, QRect start) {
	Section* section = maestro_controller_->get_maestro()->get_section(section_index);

	if (last_pixel_count_[section_index] != section->get_dimensions()->size()) {
		resizeEvent(nullptr);
		last_pixel_count_[section_index] = section->get_dimensions()->size();
	}

	for (uint16_t row = 0; row < section->get_dimensions()->y; row++) {
		for (uint16_t column = 0; column < section->get_dimensions()->x; column++) {
			tmp_rgb_ = section->get_pixel_color(column, row);
			tmp_color_.setRgb(tmp_rgb_.r, tmp_rgb_.g, tmp_rgb_.b);
			tmp_brush_.setColor(tmp_color_);
			tmp_brush_.setStyle(Qt::BrushStyle::SolidPattern);

			/*
			 * Draw the Pixel.
			 * First, calculate the bounds of the Pixel.
			 * Then, set the color of the pen to the color of the Pixel.
			 * Finally, draw the Pixel to the screen.
			 */
			tmp_rect_.setRect((start.x() + column) * pad_, row * pad_, radius_, radius_);
			painter->setBrush(tmp_brush_);
			painter->setPen(Qt::PenStyle::NoPen);

			// Determine which shape to draw
			switch (settings_.value(SettingsDialog::pixel_shape).toInt()) {
				case 0:	// Circle
					painter->drawEllipse(tmp_rect_);
					break;
				case 1:	// Rect
					painter->drawRect(tmp_rect_);
					break;
			}
		}
	}
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
	if (last_pixel_count_.size() != maestro_controller_->get_maestro()->get_num_sections()) {
		last_pixel_count_.resize(maestro_controller_->get_maestro()->get_num_sections());
	}

	QRect cursor;
	for (uint8_t i = 0; i < maestro_controller_->get_maestro()->get_num_sections(); i++) {
		Section* section = maestro_controller_->get_maestro()->get_section(i);

		// Check to see if the Section size has changed
		if (last_pixel_count_[i] != section->get_dimensions()->size()) {
			resizeEvent(nullptr);
			last_pixel_count_[i] = section->get_dimensions()->size();
		}

		draw_section(&painter, i, cursor);

		cursor.setX(cursor.x() + section->get_dimensions()->x);
	}

}

/**
 * Resize the grid based on the number of rows and columns.
 */
void SimpleDrawingArea::resizeEvent(QResizeEvent *event) {
	QSize widget_size = this->size();

	/*
	 * Find the optimal radius of each Pixel.
	 * First, get the total width and height of the Maestro by summing each Section.
	 */
	uint32_t total_width = 0;
	uint32_t height = 0;
	for (uint8_t section = 0; section < maestro_controller_->get_maestro()->get_num_sections(); section++) {
		total_width += maestro_controller_->get_maestro()->get_section(section)->get_dimensions()->x;

		if (maestro_controller_->get_maestro()->get_section(section)->get_dimensions()->y > height) {
			height = maestro_controller_->get_maestro()->get_section(section)->get_dimensions()->y;
		}
	}

	// Next, get the max size of each Pixel via the window size.
	uint16_t max_width = widget_size.width() / total_width;
	uint16_t max_height = widget_size.height() / height;

	// Find the smaller dimension
	if (max_width < max_height) {
		radius_ = max_width;
	}
	else {
		radius_ = max_height;
	}

	pad_ = radius_;

	// Finally, calculate the radius using the Settings dialog
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
