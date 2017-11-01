#include "lightninganimationcontrol.h"
#include "ui_lightninganimationcontrol.h"

LightningAnimationControl::LightningAnimationControl(LightningAnimation* animation, MaestroControl* controller, QWidget *parent) :	QWidget(parent), ui(new Ui::LightningAnimationControl) {
	ui->setupUi(this);
	this->animation_ = animation;
	this->maestro_control_ = controller;
	ui->boltCountSpinBox->setValue(animation->get_bolt_count());
	ui->forkChanceSpinBox->setValue(animation->get_fork_chance());
	ui->spreadDownSpinBox->setValue(animation->get_down_threshold());
	ui->spreadUpSpinBox->setValue(animation->get_up_threshold());
}

LightningAnimationControl::~LightningAnimationControl() {
	delete ui;
}

void LightningAnimationControl::on_forkChanceSpinBox_valueChanged(int arg1) {
	animation_->set_fork_chance(arg1);

	if (maestro_control_->cue_controller_ != nullptr) {
		maestro_control_->animation_handler->set_lightning_options(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), ui->boltCountSpinBox->value(), ui->spreadDownSpinBox->value(), ui->spreadUpSpinBox->value(), (uint8_t)arg1);
		maestro_control_->send_to_device();
	}
}

void LightningAnimationControl::on_spreadDownSpinBox_valueChanged(int arg1) {
	animation_->set_thresholds(arg1, ui->spreadUpSpinBox->value());

	if (maestro_control_->cue_controller_ != nullptr) {
		maestro_control_->animation_handler->set_lightning_options(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), ui->boltCountSpinBox->value(), arg1, ui->spreadUpSpinBox->value(), ui->forkChanceSpinBox->value());
		maestro_control_->send_to_device();
	}
}

void LightningAnimationControl::on_spreadUpSpinBox_valueChanged(int arg1) {
	animation_->set_thresholds(ui->spreadDownSpinBox->value(), arg1);

	if (maestro_control_->cue_controller_ != nullptr) {
		maestro_control_->animation_handler->set_lightning_options(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), ui->boltCountSpinBox->value(), ui->spreadDownSpinBox->value(), arg1, ui->forkChanceSpinBox->value());
		maestro_control_->send_to_device();
	}
}

void LightningAnimationControl::on_boltCountSpinBox_valueChanged(int arg1) {
	animation_->set_bolt_count(arg1);

	if (maestro_control_->cue_controller_ != nullptr) {
		maestro_control_->animation_handler->set_lightning_options(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), arg1, ui->spreadDownSpinBox->value(), ui->spreadUpSpinBox->value(), ui->forkChanceSpinBox->value());
		maestro_control_->send_to_device();
	}
}
