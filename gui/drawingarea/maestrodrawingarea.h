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
		QElapsedTimer elapsed_timer_;

		/// Handles calling the DrawingArea's refreshMaestro() method.
		QTimer *timer_;

		/// The MaestroController managed by this DrawingArea.
		MaestroController* maestro_controller_;

		/// tmp_rgb_ converted to QColor
		QColor tmp_color_;

		/// Brush used to paint tmp_color
		QBrush tmp_brush_;

		/// Size and location of the Pixel to draw using tmp_brush
		QRect tmp_rect_;

		/// Colors::RGB output from each Pixel
		Colors::RGB tmp_rgb_;

	private:
		/// Maestro's refresh rate (defaults to 20ms or 50Hz).
		const unsigned char refresh_ = 20;

	private slots:
		void refresh_maestro();
};

#endif // MAESTRODRAWINGAREA_H
