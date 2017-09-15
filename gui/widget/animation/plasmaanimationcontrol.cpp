#include "plasmaanimationcontrol.h"
#include "ui_plasmaanimationcontrol.h"

PlasmaAnimationControl::PlasmaAnimationControl(PlasmaAnimation* animation, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::PlasmaAnimationControl) {
	ui->setupUi(this);
	this->animation_ = animation;
}

PlasmaAnimationControl::~PlasmaAnimationControl() {
	delete ui;
}

void PlasmaAnimationControl::on_resolutionDoubleSpinBox_valueChanged(double arg1) {
	animation_->set_resolution(arg1);
}

void PlasmaAnimationControl::on_sizeDoubleSpinBox_valueChanged(double arg1) {
	animation_->set_size(arg1);
}
