#ifndef MAESTROCONTROL_H
#define MAESTROCONTROL_H

#include "Colors.h"
#include "Maestro.h"
#include "drawingarea/controller/maestrocontroller.h"
#include "drawingarea/controller/sectioncontroller.h"
#include "drawingarea/simpledrawingarea.h"
#include <QWidget>

namespace Ui {
	class MaestroControl;
}

using namespace PixelMaestro;

class MaestroControl : public QWidget {
	Q_OBJECT

	public:
		explicit MaestroControl(QWidget *parent, SimpleDrawingArea *drawingarea);
		~MaestroControl();

	private:
		int active_section_ = 0;
		Maestro *maestro_;
		SimpleDrawingArea *drawing_area_;
		Ui::MaestroControl *ui;

		MaestroController *maestro_controller_;

		SectionController *getActiveSectionController();

		void changeScalingColorArray(Colors::RGB color);
		void initialize();
		void on_ui_changed();
		void on_custom_color_changed();

	private slots:
		void setCustomColorControlsVisible(bool enabled);
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
};

#endif // MAESTROCONTROL_H
