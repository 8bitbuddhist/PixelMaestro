#ifndef LIGHTNINGANIMATIONCONTROL_H
#define LIGHTNINGANIMATIONCONTROL_H

#include <QWidget>
#include "animation/lightninganimation.h"

using namespace PixelMaestro;

namespace Ui {
	class LightningAnimationControl;
}

class LightningAnimationControl : public QWidget {
		Q_OBJECT

	public:
		explicit LightningAnimationControl(LightningAnimation* animation, QWidget *parent = 0);
		~LightningAnimationControl();

	private slots:
		void on_forkChanceSpinBox_valueChanged(int arg1);

		void on_spreadDownSpinBox_valueChanged(int arg1);

		void on_spreadUpSpinBox_valueChanged(int arg1);

		void on_boltCountSpinBox_valueChanged(int arg1);

	private:
		LightningAnimation* animation_;
		Ui::LightningAnimationControl *ui;
};

#endif // LIGHTNINGANIMATIONCONTROL_H
