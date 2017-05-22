#include "maestrodrawingarea.h"
#include "simpledrawingarea.h"
#include <QPainter>
#include <vector>

SimpleDrawingArea::SimpleDrawingArea(QWidget *parent, Maestro *maestro, unsigned short rows, unsigned short columns) : SimpleDrawingArea(parent, maestro) {
	this->num_rows_ = rows;
	this->num_columns_ = columns;
}

SimpleDrawingArea::SimpleDrawingArea(QWidget *parent, Maestro *maestro) : MaestroDrawingArea(parent, maestro) {
	this->maestro_ = maestro;
}

void SimpleDrawingArea::paintEvent(QPaintEvent *event) {
	// Paint Pixels (see http://doc.qt.io/qt-5/qtwidgets-widgets-analogclock-example.html)
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	Colors::RGB tmpRGB;
	QColor tmpColor;
	QBrush tmpBrush;
	QRect tmpRect;
	for (unsigned short section = 0; section < maestro_->getNumSections(); section++) {
		for (unsigned short row = 0; row < maestro_->getSection(section)->getLayout()->rows; row++) {
			for (unsigned short pixel = 0; pixel < maestro_->getSection(section)->getLayout()->columns; pixel++) {
				tmpRGB = maestro_->getSection(section)->getPixelColor(maestro_->getSection(section)->getPixelIndex(row, pixel));
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
