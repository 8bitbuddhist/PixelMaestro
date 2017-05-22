#ifndef MAESTRODRAWINGAREA_H
#define MAESTRODRAWINGAREA_H

#include "Colors.h"
#include "Maestro.h"
#include "maestrodrawingarea.h"
#include "Pixel.h"
#include <QElapsedTimer>
#include <QTimer>
#include <QWidget>
#include "Section.h"
#include <vector>

using namespace PixelMaestro;

class MaestroDrawingArea : public QWidget {
	Q_OBJECT

	public:
		MaestroDrawingArea(QWidget *parent, Maestro *maestro);
		MaestroDrawingArea(QWidget *parent, Maestro *maestro, unsigned short rows, unsigned short columns);
		Maestro *getMaestro();

		std::vector<Colors::RGB> colors_;
		std::vector<Pixel> pixels_;
		std::vector<Section> sections_;

	protected:
		QElapsedTimer elapsedTimer;
		QTimer *timer;

		// Maestro/grid variables
		Maestro *maestro_;
		unsigned short num_rows_ = 10;
		unsigned short num_columns_ = 10;
		unsigned short num_sections_ = 1;
		unsigned int num_pixels_ = num_rows_ * num_columns_;

	private slots:
		void refreshMaestro();
};

#endif // MAESTRODRAWINGAREA_H
