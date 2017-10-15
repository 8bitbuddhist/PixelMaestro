#ifndef PALETTECONTROL_H
#define PALETTECONTROL_H

#include "controller/palettecontroller.h"
#include <QDialog>

namespace Ui {
	class PaletteControl;
}

class PaletteControl : public QDialog {
		Q_OBJECT

	public:
		explicit PaletteControl(PaletteController* controller, QWidget *parent = 0);
		~PaletteControl();

	private slots:
		void set_button_color(QPushButton* button, uint8_t red, uint8_t green, uint8_t blue);
		void on_paletteComboBox_currentIndexChanged(int index);
		void on_color_clicked();

	private:
		Ui::PaletteControl *ui;
		PaletteController::Palette* active_palette_ = nullptr;
		PaletteController* controller_ = nullptr;
};

#endif // PALETTECONTROL_H
