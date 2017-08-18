/*
 * MaestroDrawingArea - Renders output from a MaestroController to a DrawingArea. Forms the basis for other DrawingAreas.
 */

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
		MaestroController *getMaestroController();

	protected:
		/// Tracks the time elapsed since the DrawingArea's initialization.
		QElapsedTimer elapsedTimer;
		/// Handles calling the DrawingArea's refreshMaestro() method.
		QTimer *timer;

		/// The MaestroController managed by this DrawingArea.
		MaestroController *maestro_controller_;

	private:
		/// Maestro's refresh rate (defaults to 20ms or 50Hz).
		const unsigned char REFRESH_ = 20;

	private slots:
		void refreshMaestro();
};

#endif // MAESTRODRAWINGAREA_H
