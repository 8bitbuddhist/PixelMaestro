#include "maestrocontrol.h"
#include "ui_maestrocontrol.h"
#include "drawingarea/maestrodrawingarea.h"
#include <QString>
#include "Section.h"

MaestroControl::MaestroControl(QWidget *parent, MaestroDrawingArea *drawingarea) : QWidget(parent), ui(new Ui::MaestroControl) {
	this->maestro_ = drawingarea->getMaestro();
	ui->setupUi(this);

	// Populate Section combo box
	for (int section = 0; section < maestro_->getNumSections(); section++) {
		ui->sectionComboBox->addItem("Section " + QString::number(section + 1));
	}
	ui->sectionComboBox->setCurrentIndex(active_section_);

	// Populate Animation combo box
	ui->animationComboBox->addItems({"Solid", "Blink", "Wave", "Pong", "Merge", "RandomIndex", "Sparkle", "Pattern", "Cycle"});

	// Populate color combo box
	ui->colorComboBox->addItems({"Rainbow", "Color Wheel"});

	// Set defaults
	ui->animationComboBox->setCurrentIndex(2);
	ui->cycleSlider->setValue((int)maestro_->getSection(active_section_)->getCycleSpeed());
	ui->refreshSlider->setValue((int)maestro_->getSection(active_section_)->getRefreshRate());
}

void MaestroControl::on_refreshSlider_valueChanged(int value) {
	maestro_->getSection(active_section_)->setRefreshInterval((unsigned short)value);
	ui->refreshSlider->setToolTip(QString::number(value));
}

void MaestroControl::on_cycleSlider_valueChanged(int value) {
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
	switch (index) {
		case 0:
			maestro_->getSection(active_section_)->setColors(Colors::RAINBOW, 7);
			break;
		default:
			maestro_->getSection(active_section_)->setColors(Colors::COLORWHEEL, 12);
	}
}

void MaestroControl::on_reverseAnimationCheckBox_toggled(bool checked) {
	on_animationComboBox_currentIndexChanged(ui->animationComboBox->currentIndex());
}
