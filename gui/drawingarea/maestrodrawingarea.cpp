#include "core/maestro.h"
#include "maestrodrawingarea.h"
#include "window/settingsdialog.h"
#include <QElapsedTimer>
#include <QSettings>
#include <QTimer>

using namespace PixelMaestro;

/**
 * Constructor.
 * @param parent The parent QWidget.
 * @param maestro_controller The MaestroController rendered by this DrawingArea.
 */
MaestroDrawingArea::MaestroDrawingArea(QWidget* parent, MaestroController* maestro_controller) : QWidget(parent), timer_(this) {
	this->maestro_controller_ = maestro_controller;

	// Initialize timers
	timer_.setTimerType(Qt::PreciseTimer);
	connect(&timer_, SIGNAL(timeout()), this, SLOT(refresh_maestro()));

	// Initialize runtime timer
	elapsed_timer_.start();

	/*
	 * Set timer's refresh rate to the Maestro's refresh rate.
	 * If we can't load the configured refresh rate, default to 40 (25fps)
	 */
	QSettings settings;
	int refresh = settings.value(SettingsDialog::refresh_rate, QVariant(40)).toInt();
	maestro_controller_->get_maestro()->set_refresh_interval(refresh);
	timer_.start(refresh);

}

MaestroController* MaestroDrawingArea::get_maestro_controller() {
	return maestro_controller_;
}

void MaestroDrawingArea::refresh_maestro() {
	maestro_controller_->get_maestro()->update(elapsed_timer_.elapsed(), true);
	update();
}
