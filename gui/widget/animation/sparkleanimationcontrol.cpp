#include "sparkleanimationcontrol.h"
#include "ui_sparkleanimationcontrol.h"

SparkleAnimationControl::SparkleAnimationControl(SparkleAnimation* animation, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SparkleAnimationControl) {
	ui->setupUi(this);
	this->animation_ = animation;
	ui->thresholdSpinBox->setValue(animation->get_threshold());
}

SparkleAnimationControl::~SparkleAnimationControl() {
	delete ui;
}

void SparkleAnimationControl::on_thresholdSpinBox_valueChanged(int arg1) {
	animation_->set_threshold(arg1);
}
