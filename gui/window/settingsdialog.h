#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
	class SettingsDialog;
}

class SettingsDialog : public QDialog
{
		Q_OBJECT

	public:
		static QString num_sections;
		static QString pixel_padding;
		static QString pixel_shape;
		static QString refresh_rate;
		static QString serial_enabled;
		static QString serial_port;
		static QString virtual_device_option;
		static QString virtual_device_width;
		static QString virtual_device_height;

		explicit SettingsDialog(QWidget *parent = 0);
		~SettingsDialog();

	private slots:
		void on_buttonBox_accepted();
		void on_serialCheckBox_toggled(bool checked);

		void on_serialPortComboBox_currentTextChanged(const QString &arg1);

	private:
		QSettings settings_;
		Ui::SettingsDialog *ui;

		void check_port_combobox();
		void set_simulated_device_options_visible(bool visible);
};

#endif // SETTINGSDIALOG_H
