#ifndef SPARKLEANIMATIONCONTROL_H
#define SPARKLEANIMATIONCONTROL_H

#include <QWidget>
#include "animation/sparkleanimation.h"
#include "widget/maestrocontrol.h"

using namespace PixelMaestro;

namespace Ui {
	class SparkleAnimationControl;
}

class SparkleAnimationControl : public QWidget
{
		Q_OBJECT

	public:
		explicit SparkleAnimationControl(SparkleAnimation* animation, MaestroControl* controller, QWidget *parent = 0);
		~SparkleAnimationControl();

	private slots:
		void on_thresholdSpinBox_valueChanged(int arg1);

	private:
		SparkleAnimation* animation_;
		MaestroControl* maestro_control_;
		Ui::SparkleAnimationControl *ui;
};

#endif // SPARKLEANIMATIONCONTROL_H
