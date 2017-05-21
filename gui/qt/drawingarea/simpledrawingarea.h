#ifndef SIMPLEDRAWINGAREA_H
#define SIMPLEDRAWINGAREA_H

#include "Colors.h"
#include "Pixel.h"
#include "maestrodrawingarea.h"
#include "Section.h"
#include <vector>

class SimpleDrawingArea : public MaestroDrawingArea {
	public:
		SimpleDrawingArea(QWidget *parent, Maestro *maestro);
		SimpleDrawingArea(QWidget *parent, Maestro *maestro, unsigned short rows, unsigned short columns);

	protected:
		void paintEvent(QPaintEvent *event) override;

		// Window/drawing area variables
		static const unsigned short RADIUS_ = 20;
		static const unsigned short PAD_ = RADIUS_ * 2;
		static const unsigned short OFFSET_ = RADIUS_ * 2;

		// Maestro/grid variables
		const unsigned short num_rows_ = 10;
		const unsigned short num_columns_ = 10;
		const unsigned short num_sections_ = 1;
		const unsigned int num_pixels_ = num_rows_ * num_columns_;

		std::vector<Colors::RGB> colors_;
		std::vector<Pixel> pixels_;
		std::vector<Section> sections_;
};

#endif // SIMPLEDRAWINGAREA_H
