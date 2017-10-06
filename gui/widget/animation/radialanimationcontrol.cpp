#include "radialanimationcontrol.h"
#include "ui_radialanimationcontrol.h"

RadialAnimationControl::RadialAnimationControl(RadialAnimation* animation, MaestroControl* maestro_control, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::RadialAnimationControl) {
	this->animation_ = animation;
	this->maestro_control_ = maestro_control;
	ui->setupUi(this);
}

void RadialAnimationControl::on_resolutionSpinBox_valueChanged(int arg1) {
	animation_->set_resolution(arg1);

	if (maestro_control_->serial_.isOpen()) {
		maestro_control_->animation_handler->set_radial_options(0, maestro_control_->active_section_controller_->is_overlay_, arg1);
		maestro_control_->send_to_device(maestro_control_->cue_controller_->get_cue(), maestro_control_->cue_controller_->get_cue_size());
	}
}

RadialAnimationControl::~RadialAnimationControl() {
	delete ui;
}
