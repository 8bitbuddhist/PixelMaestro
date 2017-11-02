#include <QSerialPortInfo>
#include <QSettings>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

// Initialize strings
QString SettingsDialog::pixel_padding = QStringLiteral("interface/padding");
QString SettingsDialog::pixel_shape = QStringLiteral("interface/shape");
QString SettingsDialog::refresh_rate = QStringLiteral("maestro/refresh");
QString SettingsDialog::serial_enabled = QStringLiteral("serial/enabled");
QString SettingsDialog::serial_port = QStringLiteral("serial/port");

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
	ui->setupUi(this);

	// Interface settings
	ui->paddingComboBox->setCurrentIndex(settings_.value(pixel_padding).toInt());
	ui->pixelShapeComboBox->setCurrentIndex(settings_.value(pixel_shape).toInt());
	if (settings_.value(refresh_rate).toInt()) {
		ui->refreshSpinBox->setValue(settings_.value(refresh_rate).toInt());
	}
	else {
		ui->refreshSpinBox->setValue(50);
	}

	// Serial settings
	ui->serialCheckBox->setChecked(settings_.value(serial_enabled).toBool());
	on_serialCheckBox_toggled(ui->serialCheckBox->isChecked());

	// Populate port settings
	ui->serialCheckBox->setEnabled(true);
	ui->serialPortComboBox->setCurrentText(settings_.value(serial_port).toString());
}

void SettingsDialog::check_port_combobox() {
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	for (QSerialPortInfo port : ports) {
		ui->serialPortComboBox->addItem(port.systemLocation());
	}

	// Only enable port dropdown if there are available devices
	ui->serialPortComboBox->setEnabled(ui->serialCheckBox->isChecked() && ports.size() > 0);
}

void SettingsDialog::on_buttonBox_accepted() {
	// Save serial options
	settings_.setValue(serial_enabled, ui->serialCheckBox->isChecked());
	settings_.setValue(serial_port, ui->serialPortComboBox->currentText());
	settings_.setValue(refresh_rate, ui->refreshSpinBox->value());

	// Save pixel padding
	settings_.setValue(pixel_padding, ui->paddingComboBox->currentIndex());

	// Save pixel shape
	settings_.setValue(pixel_shape, ui->pixelShapeComboBox->currentIndex());
}

void SettingsDialog::on_serialCheckBox_toggled(bool checked) {
	check_port_combobox();
}

SettingsDialog::~SettingsDialog() {
	delete ui;
}
