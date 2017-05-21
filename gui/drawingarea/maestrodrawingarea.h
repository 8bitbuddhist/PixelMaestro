#ifndef MAESTRODRAWINGAREA_H
#define MAESTRODRAWINGAREA_H

#include "Maestro.h"
#include <QElapsedTimer>
#include <QTimer>
#include <QWidget>

using namespace PixelMaestro;

class MaestroDrawingArea : public QWidget {
	Q_OBJECT

	public:
		MaestroDrawingArea(QWidget *parent, Maestro *maestro);
		Maestro *getMaestro();

	protected:
		QElapsedTimer elapsedTimer;
		Maestro *maestro_;
		QTimer *timer;

	private slots:
		void refreshMaestro();
};

#endif // MAESTRODRAWINGAREA_H
