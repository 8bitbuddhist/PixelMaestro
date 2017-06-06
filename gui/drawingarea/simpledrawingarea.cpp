#include "controller/maestrocontroller.h"
#include "maestrodrawingarea.h"
#include "simpledrawingarea.h"
#include <QPainter>
#include <vector>

SimpleDrawingArea::SimpleDrawingArea(QWidget *parent, MaestroController *maestroController) : MaestroDrawingArea(parent, maestroController) {
	this->maestro_controller_ = maestroController;
}

void SimpleDrawingArea::paintEvent(QPaintEvent *event) {
	// Paint Pixels (see http://doc.qt.io/qt-5/qtwidgets-widgets-analogclock-example.html)
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	Colors::RGB tmpRGB;
	QColor tmpColor;
	QBrush tmpBrush;
	QRect tmpRect;
	for (unsigned short section = 0; section < this->maestro_controller_->getNumSectionControllers(); section++) {
		for (unsigned short row = 0; row < this->maestro_controller_->getSectionController(section)->getSection()->getLayout()->rows; row++) {
			for (unsigned short pixel = 0; pixel < this->maestro_controller_->getSectionController(section)->getSection()->getLayout()->columns; pixel++) {
				tmpRGB = this->maestro_controller_->getSectionController(section)->getSection()->getPixelColor(this->maestro_controller_->getSectionController(section)->getSection()->getPixelIndex(row, pixel));
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

void SimpleDrawingArea::resizePixels() {
	int minDimension, minLayout;
	if (this->width() < this->height()) {
		minDimension = this->width();
	}
	else {
		minDimension = this->height();
	}

	Section::Layout *layout = this->maestro_controller_->getSectionController(0)->getSection()->getLayout();
	if (layout->rows > layout->columns) {
		minLayout = layout->rows;
	}
	else {
		minLayout = layout->columns;
	}

	RADIUS_ = (minDimension / minLayout) / 2;
	PAD_ = RADIUS_ * 2;
	OFFSET_ = PAD_;
}
