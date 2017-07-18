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
		Maestro *getMaestro();
		MaestroController *getMaestroController();

	protected:
		/// Tracks the time elapsed since the DrawingArea's initialization.
		QElapsedTimer elapsedTimer;
		/// Handles calling the DrawingArea's refreshMaestro() method every 20ms (depending on the interval).
		QTimer *timer;

		/*
		 * Maestro/grid variables.
		 * These define how the Maestro is rendered initially in the DrawingArea.
		 */
		Maestro *maestro_;
		MaestroController *maestro_controller_;
		unsigned short num_rows_ = 10;
		unsigned short num_columns_ = 10;
		unsigned short num_sections_ = 1;
		unsigned int num_pixels_ = num_rows_ * num_columns_;

	private:
		/// Maestro's refresh rate (defaults to 20ms or 50Hz).
		const unsigned char REFRESH_ = 20;

	private slots:
		void refreshMaestro();
};

#endif // MAESTRODRAWINGAREA_H
