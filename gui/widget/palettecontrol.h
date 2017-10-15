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
		explicit PaletteControl(PaletteController* controller, std::string initial_palette = "", QWidget *parent = 0);
		~PaletteControl();

	private slots:
		void on_color_clicked();
		void on_createButtonBox_accepted();
		void on_createPaletteButton_clicked();
		void on_paletteComboBox_currentIndexChanged(int index);
		void on_removeButton_clicked();
		void set_button_color(QPushButton* button, uint8_t red, uint8_t green, uint8_t blue);

		void on_createButtonBox_rejected();

		void on_typeComboBox_currentIndexChanged(int index);

		void on_baseColorButton_clicked();

		void on_targetColorButton_clicked();

	private:
		Ui::PaletteControl *ui;
		PaletteController::Palette* active_palette_ = nullptr;
		PaletteController* palette_controller_ = nullptr;

		QColor base_color_ = Qt::black;
		QColor target_color_ = Qt::black;

		void set_create_palette_controls_visible(bool visible);
};

#endif // PALETTECONTROL_H
