#ifndef MAESTROCONTROL_H
#define MAESTROCONTROL_H

#include "Maestro.h"
#include "drawingarea/maestrodrawingarea.h"
#include <QWidget>

namespace Ui {
	class MaestroControl;
}

using namespace PixelMaestro;

class MaestroControl : public QWidget {
	Q_OBJECT

	public:
		explicit MaestroControl(QWidget *parent, MaestroDrawingArea *drawingarea);
		~MaestroControl();

	private:
		int active_section_ = 1;
		Maestro *maestro_;
		Ui::MaestroControl *ui;

	private slots:
		void on_refreshSlider_valueChanged(int value);
		void on_cycleSlider_valueChanged(int value);
		void on_animationComboBox_currentIndexChanged(int index);
		void on_sectionComboBox_currentIndexChanged(int index);
		void on_colorComboBox_currentIndexChanged(int index);
		void on_reverseAnimationCheckBox_toggled(bool checked);
};

#endif // MAESTROCONTROL_H
