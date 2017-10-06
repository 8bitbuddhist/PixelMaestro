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
		static QString interface_padding;
		static QString serial_enabled;
		static QString serial_port;

		explicit SettingsDialog(QWidget *parent = 0);
		~SettingsDialog();

	private slots:
		void on_buttonBox_accepted();
		void on_paddingComboBox_currentIndexChanged(int index);
		void on_serialCheckBox_toggled(bool checked);

	private:
		QSettings settings_;
		Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
