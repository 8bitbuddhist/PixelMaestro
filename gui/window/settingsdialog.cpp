#include <QSerialPortInfo>
#include <QSettings>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

// Initialize strings
QString SettingsDialog::num_sections = QStringLiteral("maestro/num_sections");
QString SettingsDialog::pixel_padding = QStringLiteral("interface/padding");
QString SettingsDialog::pixel_shape = QStringLiteral("interface/shape");
QString SettingsDialog::refresh_rate = QStringLiteral("maestro/refresh");
QString SettingsDialog::serial_enabled = QStringLiteral("serial/enabled");
QString SettingsDialog::serial_port = QStringLiteral("serial/port");
QString SettingsDialog::virtual_device_option = QStringLiteral("Simulated Device");
QString SettingsDialog::virtual_device_width = QStringLiteral("serial/simulated_device/width");
QString SettingsDialog::virtual_device_height = QStringLiteral("serial/simulated_device/height");

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
	ui->setupUi(this);

	// Interface settings
	ui->paddingComboBox->setCurrentIndex(settings_.value(pixel_padding).toInt());
	ui->pixelShapeComboBox->setCurrentIndex(settings_.value(pixel_shape).toInt());

	// Maestro settings
	ui->numSectionsSpinBox->setValue(settings_.value(num_sections, 1).toInt());
	ui->refreshSpinBox->setValue(settings_.value(refresh_rate, 50).toInt());

	// Serial settings
	ui->serialCheckBox->setChecked(settings_.value(serial_enabled).toBool());
	on_serialCheckBox_toggled(ui->serialCheckBox->isChecked());

	// Port settings
	check_port_combobox();
	QString port_name = settings_.value(serial_port).toString();
	ui->serialPortComboBox->setCurrentText(port_name);

	set_simulated_device_options_visible(port_name.contains(virtual_device_option));
}

void SettingsDialog::check_port_combobox() {
	// Add option to select virtual serial device
	ui->serialPortComboBox->addItem(SettingsDialog::virtual_device_option);

	// Add actual serial devices
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	for (QSerialPortInfo port : ports) {
		ui->serialPortComboBox->addItem(port.systemLocation());
	}

	// Only enable port dropdown if checked
	ui->serialPortComboBox->setEnabled(ui->serialCheckBox->isChecked());
}

void SettingsDialog::on_buttonBox_accepted() {
	// Save Maestro settings
	settings_.setValue(refresh_rate, ui->refreshSpinBox->value());
	settings_.setValue(num_sections, ui->numSectionsSpinBox->value());

	// Save serial settings
	settings_.setValue(serial_enabled, ui->serialCheckBox->isChecked());
	settings_.setValue(serial_port, ui->serialPortComboBox->currentText());

	// Save interface settings
	settings_.setValue(pixel_padding, ui->paddingComboBox->currentIndex());
	settings_.setValue(pixel_shape, ui->pixelShapeComboBox->currentIndex());

	// Save virtual device size
	settings_.setValue(virtual_device_width, ui->simulatedWidthSpinBox->value());
	settings_.setValue(virtual_device_height, ui->simulatedHeightSpinBox->value());
}

void SettingsDialog::on_serialCheckBox_toggled(bool checked) {
	ui->serialPortComboBox->setEnabled(checked);
}

void SettingsDialog::set_simulated_device_options_visible(bool visible) {
	ui->simulatedDeviceHeightLabel->setVisible(visible);
	ui->simulatedDeviceWidthLabel->setVisible(visible);
	ui->simulatedHeightSpinBox->setVisible(visible);
	ui->simulatedWidthSpinBox->setVisible(visible);
}

SettingsDialog::~SettingsDialog() {
	delete ui;
}

void SettingsDialog::on_serialPortComboBox_currentTextChanged(const QString &arg1) {
	set_simulated_device_options_visible(arg1.contains(virtual_device_option));
}
