#include "sparkleanimationcontrol.h"
#include "ui_sparkleanimationcontrol.h"

SparkleAnimationControl::SparkleAnimationControl(SparkleAnimation* animation, MaestroControl* controller, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::SparkleAnimationControl) {
	ui->setupUi(this);
	this->animation_ = animation;
	this->maestro_control_ = controller;
	ui->thresholdSpinBox->setValue(animation->get_threshold());
}

SparkleAnimationControl::~SparkleAnimationControl() {
	delete ui;
}

void SparkleAnimationControl::on_thresholdSpinBox_valueChanged(int arg1) {
	animation_->set_threshold(arg1);

	if (maestro_control_->serial_.isOpen()) {
		maestro_control_->animation_handler->set_sparkle_options(0, maestro_control_->active_section_controller_->is_overlay_, arg1);
		maestro_control_->send_to_device(maestro_control_->cue_controller_->get_cue(), maestro_control_->cue_controller_->get_cue_size());
	}
}
