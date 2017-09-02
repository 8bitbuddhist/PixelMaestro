/*
 * MaestroDrawingArea - Renders output from a MaestroController to a DrawingArea. Forms the basis for other DrawingAreas.
 */

#ifndef MAESTRODRAWINGAREA_H
#define MAESTRODRAWINGAREA_H

#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "colors.h"
#include "maestro.h"
#include "maestrodrawingarea.h"
#include "pixel.h"
#include <QElapsedTimer>
#include <QTimer>
#include <QWidget>
#include "section.h"
#include <vector>

using namespace PixelMaestro;

class MaestroDrawingArea : public QWidget {
	Q_OBJECT

	public:
		MaestroDrawingArea(QWidget* parent, MaestroController* maestro_controller);
		MaestroController* get_maestro_controller();

	protected:
		/// Tracks the time elapsed since the DrawingArea's initialization.
		QElapsedTimer elapsed_timer;

		/// Handles calling the DrawingArea's refreshMaestro() method.
		QTimer *timer;

		/// The MaestroController managed by this DrawingArea.
		MaestroController* maestro_controller_;

	private:
		/// Maestro's refresh rate (defaults to 20ms or 50Hz).
		const unsigned char refresh_ = 20;

	private slots:
		void refresh_maestro();
};

#endif // MAESTRODRAWINGAREA_H
