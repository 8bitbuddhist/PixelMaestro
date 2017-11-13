#include <QLabel>
#include <QSettings>
#include "virtualserialdevicedialog.h"
#include "window/settingsdialog.h"
#include "ui_virtualserialdevicedialog.h"
#include "colorpresets.h"

using namespace PixelMaestro;

VirtualSerialDeviceDialog::VirtualSerialDeviceDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::VirtualSerialDeviceDialog) {
	ui->setupUi(this);

	// Enable and configure Maestro
	maestro_controller_ = std::unique_ptr<MaestroController>(new MaestroController());
	Maestro* maestro = maestro_controller_->get_maestro();

	QSettings settings;
	Point size(settings.value(SettingsDialog::virtual_device_width).toUInt(), settings.value(SettingsDialog::virtual_device_height).toUInt());
	maestro_controller_->set_sections(1, size);
	CueController* controller = maestro->set_cue_controller();
	controller->enable_handler(CueController::Handler::AnimationHandler);
	controller->enable_handler(CueController::Handler::CanvasHandler);
	controller->enable_handler(CueController::Handler::MaestroHandler);
	controller->enable_handler(CueController::Handler::SectionHandler);

	// Add Maestro to window
	QLayout* layout = this->findChild<QLayout*>("maestroLayout");
	drawing_area_ = std::unique_ptr<SimpleDrawingArea>(new SimpleDrawingArea(layout->widget(), maestro_controller_.get()));
	layout->addWidget(drawing_area_.get());

	// For debugging only
	/*
	interpreted = new QLabel(this);
	interpreted->setAlignment(Qt::AlignLeft);
	layout->addWidget(interpreted);
	*/
}

void VirtualSerialDeviceDialog::display_cue(uint8_t* cue) {
	std::string interpreted_cue = cue_interpreter_->interpret_cue(cue);
	interpreted->setText(QString("Last action: ") + QString::fromStdString(interpreted_cue));
}

Maestro* VirtualSerialDeviceDialog::get_maestro() {
	return maestro_controller_->get_maestro();
}

VirtualSerialDeviceDialog::~VirtualSerialDeviceDialog() {
	delete ui;
}
