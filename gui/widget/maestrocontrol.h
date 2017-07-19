/*
 * MaestroControl - Widget for interacting with a MaestroController.
 */

#ifndef MAESTROCONTROL_H
#define MAESTROCONTROL_H

#include "Colors.h"
#include "Maestro.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "drawingarea/simpledrawingarea.h"
#include <QWidget>

namespace Ui {
	class MaestroControl;
}

using namespace PixelMaestro;

class MaestroControl : public QWidget {
	Q_OBJECT

	public:
		explicit MaestroControl(QWidget *parent, MaestroController *maestroController);
		~MaestroControl();

	private:
		/// Index of the actively controlled SectionController.
		int active_section_ = 0;
		/// Pointer to Maestro being controlled.
		Maestro *maestro_;
		Ui::MaestroControl *ui;

		/// MaestroController that this widget is controlling.
		MaestroController *maestro_controller_;

		SectionController *getActiveSectionController();
		void changeScalingColorArray(Colors::RGB color);
		void initialize();
		void on_ui_changed();
		void on_custom_color_changed();

	private slots:
		void on_cycleSlider_valueChanged(int value);
		void on_animationComboBox_currentIndexChanged(int index);
		void on_colorComboBox_currentIndexChanged(int index);
		void on_reverseAnimationCheckBox_toggled(bool checked);
		void on_redDial_valueChanged(int value);
		void on_greenDial_valueChanged(int value);
		void on_blueDial_valueChanged(int value);
		void on_numColorsSpinBox_valueChanged(int arg1);
		void on_thresholdSpinBox_valueChanged(int arg1);
		void on_fadeCheckBox_toggled(bool checked);
		void on_columnsSpinBox_valueChanged(int arg1);
		void on_rowsSpinBox_valueChanged(int arg1);
		void setCustomColorControlsVisible(bool enabled);
};

#endif // MAESTROCONTROL_H
