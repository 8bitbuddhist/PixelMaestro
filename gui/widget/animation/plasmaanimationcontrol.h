#ifndef PLASMAANIMATIONCONTROL_H
#define PLASMAANIMATIONCONTROL_H

#include <QWidget>
#include "animation/plasmaanimation.h"
#include "widget/maestrocontrol.h"

using namespace PixelMaestro;

namespace Ui {
	class PlasmaAnimationControl;
}

class PlasmaAnimationControl : public QWidget {
		Q_OBJECT

	public:
		explicit PlasmaAnimationControl(PlasmaAnimation* animation, MaestroControl* controller, QWidget *parent = 0);
		~PlasmaAnimationControl();

	private slots:
		void on_sizeDoubleSpinBox_valueChanged(double arg1);

		void on_resolutionDoubleSpinBox_valueChanged(double arg1);

	private:
		PlasmaAnimation* animation_;
		MaestroControl* maestro_control_;
		Ui::PlasmaAnimationControl *ui;
};

#endif // PLASMAANIMATIONCONTROL_H
