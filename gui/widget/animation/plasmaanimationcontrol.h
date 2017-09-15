#ifndef PLASMAANIMATIONCONTROL_H
#define PLASMAANIMATIONCONTROL_H

#include <QWidget>
#include "animation/plasmaanimation.h"

using namespace PixelMaestro;

namespace Ui {
	class PlasmaAnimationControl;
}

class PlasmaAnimationControl : public QWidget {
		Q_OBJECT

	public:
		explicit PlasmaAnimationControl(PlasmaAnimation* animation, QWidget *parent = 0);
		~PlasmaAnimationControl();

	private slots:
		void on_sizeDoubleSpinBox_valueChanged(double arg1);

		void on_resolutionDoubleSpinBox_valueChanged(double arg1);

	private:
		PlasmaAnimation* animation_;
		Ui::PlasmaAnimationControl *ui;
};

#endif // PLASMAANIMATIONCONTROL_H
