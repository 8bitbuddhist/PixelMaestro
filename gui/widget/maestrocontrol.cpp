#include "maestrocontrol.h"
#include "ui_maestrocontrol.h"
#include "drawingarea/simpledrawingarea.h"
#include <QPalette>
#include <QString>
#include "Section.h"

MaestroControl::MaestroControl(QWidget *parent, SimpleDrawingArea *drawingarea) : QWidget(parent), ui(new Ui::MaestroControl) {
	this->maestro_ = drawingarea->getMaestro();
	this->drawing_area_ = drawingarea;
	ui->setupUi(this);

	this->initialize();
}

void MaestroControl::initialize() {
	// Populate Section combo box
	for (int section = 0; section < maestro_->getNumSections(); section++) {
		ui->sectionComboBox->addItem("Section " + QString::number(section + 1));
	}
	ui->sectionComboBox->setCurrentIndex(active_section_);

	// Populate Animation combo box
	ui->animationComboBox->addItems({"Solid", "Blink", "Wave", "Pong", "Merge", "RandomIndex", "Sparkle", "Pattern", "Cycle"});

	// Populate color combo box
	ui->colorComboBox->addItems({"Custom", "Rainbow", "Color Wheel"});
	ui->colorComboBox->setCurrentIndex(2);

	// Set defaults
	ui->animationComboBox->setCurrentIndex(2);
	ui->cycleSlider->setValue((int)maestro_->getSection(active_section_)->getCycleSpeed());
}

void MaestroControl::on_cycleSlider_valueChanged(int value) {
	value = ui->cycleSlider->maximum() - value;
	maestro_->getSection(active_section_)->setCycleInterval((unsigned short)value);
	ui->cycleSlider->setToolTip(QString::number(value));
}

void MaestroControl::on_animationComboBox_currentIndexChanged(int index) {
	maestro_->getSection(active_section_)->setColorAnimation((Section::ColorAnimations)index, ui->reverseAnimationCheckBox->isChecked());
}

void MaestroControl::on_sectionComboBox_currentIndexChanged(int index) {
	this->active_section_ = index;
}

MaestroControl::~MaestroControl() {
	delete ui;
}

void MaestroControl::on_colorComboBox_currentIndexChanged(int index) {
	// TODO: Hide custom controls when a pre-defined scheme is selected
	switch (index) {
		case 0:
			this->on_custom_color_changed();
			break;
		case 1:
			maestro_->getSection(active_section_)->setColors(Colors::RAINBOW, 7);
			ui->numColorsSpinBox->setValue(7);
			break;
		default:
			maestro_->getSection(active_section_)->setColors(Colors::COLORWHEEL, 12);
			ui->numColorsSpinBox->setValue(12);
	}
}

void MaestroControl::on_reverseAnimationCheckBox_toggled(bool checked) {
	on_animationComboBox_currentIndexChanged(ui->animationComboBox->currentIndex());
}

void MaestroControl::on_custom_color_changed() {
	if (ui->colorComboBox->currentIndex() != 0) {
		return;
	}

	unsigned char r = ui->redDial->value();
	unsigned char g = ui->greenDial->value();
	unsigned char b = ui->blueDial->value();

	changeScalingColorArray(Colors::RGB {r, g, b});
}

void MaestroControl::on_ui_changed() {
	// Update UI elements based on current settings
}

void MaestroControl::changeScalingColorArray(Colors::RGB color) {
	unsigned int numColors = (unsigned int)ui->numColorsSpinBox->value();
	this->drawing_area_->colors_.resize(numColors);
	unsigned char threshold = 255 - (unsigned char)ui->thresholdSpinBox->value();
	Colors::generateScalingColorArray(&this->drawing_area_->colors_[0], color, numColors, threshold, true);
	maestro_->getSection(active_section_)->setColors(&this->drawing_area_->colors_[0], numColors);
}

void MaestroControl::on_redDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

void MaestroControl::on_greenDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

void MaestroControl::on_blueDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

void MaestroControl::on_numColorsSpinBox_valueChanged(int arg1) {
	this->on_custom_color_changed();
}

void MaestroControl::on_thresholdSpinBox_valueChanged(int arg1) {
	this->on_custom_color_changed();
}
