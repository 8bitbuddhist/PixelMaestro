#ifndef MAESTRODRAWINGAREA_H
#define MAESTRODRAWINGAREA_H

#include "Colors.h"
#include "Maestro.h"
#include "controller/maestrocontroller.h"
#include "maestrodrawingarea.h"
#include "Pixel.h"
#include <QElapsedTimer>
#include <QTimer>
#include <QWidget>
#include "Section.h"
#include "controller/sectioncontroller.h"
#include <vector>

using namespace PixelMaestro;

class MaestroDrawingArea : public QWidget {
	Q_OBJECT

	public:
		MaestroDrawingArea(QWidget *parent, MaestroController *maestroController);
		//MaestroDrawingArea(QWidget *parent, Maestro *maestro, unsigned short rows, unsigned short columns);
		Maestro *getMaestro();
		MaestroController *getMaestroController();

	protected:
		QElapsedTimer elapsedTimer;
		QTimer *timer;

		// Maestro/grid variables
		Maestro *maestro_;
		MaestroController *maestro_controller_;
		unsigned short num_rows_ = 10;
		unsigned short num_columns_ = 10;
		unsigned short num_sections_ = 1;
		unsigned int num_pixels_ = num_rows_ * num_columns_;

	private slots:
		void refreshMaestro();
};

#endif // MAESTRODRAWINGAREA_H
