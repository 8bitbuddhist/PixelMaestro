#include "core/maestro.h"
#include "maestrodrawingarea.h"
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
	this->refresh_ = maestro_controller_->get_maestro()->get_refresh_rate();

	// Initialize timers.
	timer_ = new QTimer(this);
	timer_->setTimerType(Qt::PreciseTimer);
	connect(timer_, SIGNAL(timeout()), this, SLOT(refresh_maestro()));

	// Initialize runtime timer
	elapsed_timer_.start();

	// Set Maestro's refresh rate
	timer_->start(refresh_);
}

MaestroController* MaestroDrawingArea::get_maestro_controller() {
	return maestro_controller_;
}

void MaestroDrawingArea::refresh_maestro() {
	/*
	 * Check if a Show has been created.
	 * If so, run the Show. Otherwise, update the Maestro.
	 */
	if (maestro_controller_->get_show()) {
		maestro_controller_->get_show()->update(elapsed_timer_.elapsed());
	}
	else {
		maestro_controller_->get_maestro()->update(elapsed_timer_.elapsed());
	}
	update();
}
