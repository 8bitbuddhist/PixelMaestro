#include "lightninganimationcontrol.h"
#include "ui_lightninganimationcontrol.h"

LightningAnimationControl::LightningAnimationControl(LightningAnimation* animation, QWidget *parent) :	QWidget(parent), ui(new Ui::LightningAnimationControl) {
	ui->setupUi(this);
	this->animation_ = animation;
}

LightningAnimationControl::~LightningAnimationControl() {
	delete ui;
}

void LightningAnimationControl::on_forkChanceSpinBox_valueChanged(int arg1) {
	animation_->set_fork_chance(arg1);
}

void LightningAnimationControl::on_spreadDownSpinBox_valueChanged(int arg1) {
	animation_->set_thresholds(arg1, ui->spreadUpSpinBox->value());
}

void LightningAnimationControl::on_spreadUpSpinBox_valueChanged(int arg1) {
	animation_->set_thresholds(ui->spreadDownSpinBox->value(), arg1);
}

void LightningAnimationControl::on_boltCountSpinBox_valueChanged(int arg1) {
	animation_->set_bolt_count(arg1);
}
