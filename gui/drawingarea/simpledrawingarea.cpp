#include "controller/maestrocontroller.h"
#include "maestrodrawingarea.h"
#include "simpledrawingarea.h"
#include <QPainter>
#include <vector>

/**
 * Constructor.
 * @param parent The parent QWidget.
 * @param maestroController The MaestroController rendered by this DrawingArea.
 */
SimpleDrawingArea::SimpleDrawingArea(QWidget *parent, MaestroController *maestroController) : MaestroDrawingArea(parent, maestroController) {
	this->maestro_controller_ = maestroController;
}

/**
 * Renders the Maestro using a simple, regular 2D grid.
 * @param event
 */
void SimpleDrawingArea::paintEvent(QPaintEvent *event) {
	// Paint Pixels (see http://doc.qt.io/qt-5/qtwidgets-widgets-analogclock-example.html)
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	Colors::RGB tmpRGB;	// RGB output from each Pixel
	QColor tmpColor;	// tmpRGB converted to QColor
	QBrush tmpBrush;	// Brush used to paint tmpColor
	QRect tmpRect;		// Size and location of the Pixel to draw using tmpBrush

	/*
	 * Note: This assumes we only have one section in the Maestro.
	 * If there's more than one, the last Section will overwrite the first.
	 * For more complex layouts, create a custom MaestroDrawingArea or add multiple SimpleDrawingAreas to the window.
	 */

	/*
	 * Render each Pixel in the Maestro by mapping its location in the grid to a location on the DrawingArea.
	 */
	this->resizePixels();
	for (unsigned short section = 0; section < this->maestro_controller_->getNumSectionControllers(); section++) {
		for (unsigned short row = 0; row < this->maestro_controller_->getSectionController(section)->getSection()->getDimensions()->y; row++) {
			for (unsigned short pixel = 0; pixel < this->maestro_controller_->getSectionController(section)->getSection()->getDimensions()->x; pixel++) {
				tmpRGB = this->maestro_controller_->getSectionController(section)->getSection()->getPixelColor(this->maestro_controller_->getSectionController(section)->getSection()->getPixelIndex(pixel, row));
				tmpColor.setRgb(tmpRGB.r, tmpRGB.g, tmpRGB.b);
				tmpBrush.setColor(tmpColor);
				tmpBrush.setStyle(Qt::BrushStyle::SolidPattern);

				/*
				 * Draw the Pixel.
				 * First, calculate the bounds of the Pixel.
				 * Then, set the color of the pen to the color of the Pixel.
				 * Finally, draw the Pixel to the screen.
				 */
				tmpRect.setRect(pixel * PAD_, row * PAD_, RADIUS_, RADIUS_);
				painter.setBrush(tmpBrush);
				painter.setPen(Qt::PenStyle::NoPen);
				painter.drawEllipse(tmpRect);
			}
		}
	}
}

/**
 * Resize the grid based on the number of rows and columns.
 * TODO: Improve dynamic scaling.
 */
void SimpleDrawingArea::resizePixels() {
	int minDimension, minPoint;
	// Find the smallest dimension. We'll use this to determine whether (and in which direction) to reduce the size of the grid.
	if (this->width() < this->height()) {
		minDimension = this->width();
	}
	else {
		minDimension = this->height();
	}

	Point *dimensions = this->maestro_controller_->getSectionController(0)->getSection()->getDimensions();
	if (dimensions->y > dimensions->x) {
		minPoint = dimensions->y;
	}
	else {
		minPoint = dimensions->x;
	}

	RADIUS_ = (minDimension / minPoint) / 2;
	PAD_ = RADIUS_ * 2;
	OFFSET_ = PAD_;
}
