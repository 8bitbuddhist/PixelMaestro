#include <QSerialPortInfo>
#include <QSettings>
#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
	ui->setupUi(this);
	QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

	// Populate port box
	for (QSerialPortInfo port : ports) {
		ui->serialPortComboBox->addItem(port.systemLocation());
	}

	QSettings settings;
	ui->serialPortComboBox->setCurrentText(settings.value("serial/port").toString());
	ui->serialCheckBox->setChecked(settings.value("serial/enabled").toBool());

	on_serialCheckBox_toggled(ui->serialCheckBox->isChecked());
}

void SettingsDialog::on_buttonBox_accepted() {
	QSettings settings;
	settings.setValue("serial/enabled", ui->serialCheckBox->isChecked());
	settings.setValue("serial/port", ui->serialPortComboBox->currentText());
}

void SettingsDialog::on_serialCheckBox_toggled(bool checked) {
	ui->serialPortComboBox->setEnabled(checked);
}

SettingsDialog::~SettingsDialog() {
	delete ui;
}
