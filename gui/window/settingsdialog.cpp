#include <QSerialPortInfo>
#include <QSettings>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

// Initialize strings
QString SettingsDialog::interface_padding = QStringLiteral("interface/padding");
QString SettingsDialog::serial_enabled = QStringLiteral("serial/enabled");
QString SettingsDialog::serial_port = QStringLiteral("serial/port");

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
	ui->setupUi(this);

	// Populate port box
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
	for (QSerialPortInfo port : ports) {
		ui->serialPortComboBox->addItem(port.systemLocation());
	}

	// Interface settings
	ui->paddingComboBox->setCurrentIndex(settings_.value(interface_padding).toInt());

	// Serial settings
	ui->serialPortComboBox->setCurrentText(settings_.value(serial_port).toString());
	ui->serialCheckBox->setChecked(settings_.value(serial_enabled).toBool());
	on_serialCheckBox_toggled(ui->serialCheckBox->isChecked());
}

void SettingsDialog::on_buttonBox_accepted() {
	settings_.setValue(serial_enabled, ui->serialCheckBox->isChecked());
	settings_.setValue(serial_port, ui->serialPortComboBox->currentText());
}

void SettingsDialog::on_paddingComboBox_currentIndexChanged(int index) {
	settings_.setValue(interface_padding, index);
}

void SettingsDialog::on_serialCheckBox_toggled(bool checked) {
	ui->serialPortComboBox->setEnabled(checked);
}

SettingsDialog::~SettingsDialog() {
	delete ui;
}
