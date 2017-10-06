#ifndef RADIALANIMATIONCONTROL_H
#define RADIALANIMATIONCONTROL_H

#include <QWidget>
#include "animation/radialanimation.h"
#include "widget/maestrocontrol.h"

using namespace PixelMaestro;

namespace Ui {
	class RadialAnimationControl;
}

class RadialAnimationControl : public QWidget
{
		Q_OBJECT

	public:
		explicit RadialAnimationControl(RadialAnimation* animation, MaestroControl* maestro_control, QWidget *parent = 0);
		~RadialAnimationControl();

	private slots:
		void on_resolutionSpinBox_valueChanged(int arg1);

	private:
		RadialAnimation* animation_;
		MaestroControl* maestro_control_;
		Ui::RadialAnimationControl *ui;
};

#endif // RADIALANIMATIONCONTROL_H
