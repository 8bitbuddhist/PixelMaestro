#include "maestrodrawingarea.h"
#include "maestro.h"
#include <QElapsedTimer>
#include <QTimer>

using namespace PixelMaestro;

/**
 * Constructor.
 * @param parent The parent QWidget.
 * @param maestro_controller The MaestroController rendered by this DrawingArea.
 */
MaestroDrawingArea::MaestroDrawingArea(QWidget* parent, MaestroController* maestro_controller) : QWidget(parent) {
	this->maestro_controller_ = maestro_controller;

	// Initialize timers.
	this->timer = new QTimer(this);
	this->timer->setTimerType(Qt::PreciseTimer);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(refresh_maestro()));

	// Initialize runtime timer
	this->elapsed_timer.start();

	// Set Maestro's refresh rate
	this->timer->start(this->refresh_);
}

MaestroController* MaestroDrawingArea::get_maestro_controller() {
	return this->maestro_controller_;
}

void MaestroDrawingArea::refresh_maestro() {
	/*
	 * Check if a Show has been created.
	 * If so, run the Show. Otherwise, update the Maestro.
	 */
	if (this->maestro_controller_->get_show()) {
		this->maestro_controller_->get_show()->update(this->elapsed_timer.elapsed());
	}
	else {
		this->maestro_controller_->get_maestro()->update(this->elapsed_timer.elapsed());
	}
	this->update();
}
