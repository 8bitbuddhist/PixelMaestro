#include "maestrodrawingarea.h"
#include "Maestro.h"
#include <QElapsedTimer>
#include <QTimer>

using namespace PixelMaestro;

/**
 * Constructor.
 * @param parent The parent QWidget.
 * @param maestroController The MaestroController rendered by this DrawingArea.
 */
MaestroDrawingArea::MaestroDrawingArea(QWidget *parent, MaestroController *maestroController) : QWidget(parent) {
	this->maestro_controller_ = maestroController;

	// Initialize timers.
	this->timer = new QTimer(this);
	this->timer->setTimerType(Qt::PreciseTimer);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(refreshMaestro()));

	// Initialize runtime timer
	this->elapsedTimer.start();

	// Set Maestro's refresh rate
	this->timer->start(this->REFRESH_);
}

MaestroController *MaestroDrawingArea::getMaestroController() {
	return this->maestro_controller_;
}

void MaestroDrawingArea::refreshMaestro() {
	/*
	 * Check if a Show has been created.
	 * If so, run the Show. Otherwise, update the Maestro.
	 */
	if (this->maestro_controller_->getShow()) {
		this->maestro_controller_->getShow()->update(this->elapsedTimer.elapsed());
	}
	else {
		this->maestro_controller_->getMaestro()->update(this->elapsedTimer.elapsed());
	}
	this->update();
}
