#include "maestrodrawingarea.h"
#include "Maestro.h"
#include <QElapsedTimer>
#include <QTimer>

using namespace PixelMaestro;

MaestroDrawingArea::MaestroDrawingArea(QWidget *parent, Maestro *maestro) : QWidget(parent) {
	// Initialize the Maestro
	this->maestro_ = maestro;

	// Initialize refresh timer
	this->timer = new QTimer(this);
	this->timer->setTimerType(Qt::PreciseTimer);
	connect(this->timer, SIGNAL(timeout()), this, SLOT(refreshMaestro()));

	// Initialize runtime timer
	this->elapsedTimer.start();

	// Manually set refresh rate to 20ms, or 50Hz
	this->timer->start(20);
}

Maestro *MaestroDrawingArea::getMaestro() {
	return this->maestro_;
}

void MaestroDrawingArea::refreshMaestro() {
	this->maestro_->update(this->elapsedTimer.elapsed());
	this->update();
}
