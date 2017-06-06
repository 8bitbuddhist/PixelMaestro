#include "maestrocontrol.h"
#include "ui_maestrocontrol.h"
#include "drawingarea/controller/maestrocontroller.h"
#include "drawingarea/controller/sectioncontroller.h"
#include "drawingarea/simpledrawingarea.h"
#include <QPalette>
#include <QString>
#include "Section.h"

MaestroControl::MaestroControl(QWidget *parent, SimpleDrawingArea *drawingarea) : QWidget(parent), ui(new Ui::MaestroControl) {
	this->maestro_ = drawingarea->getMaestro();
	this->drawing_area_ = drawingarea;
	this->maestro_controller_ = this->drawing_area_->getMaestroController();
	ui->setupUi(this);

	this->initialize();
}

void MaestroControl::initialize() {
	this->maestro_controller_->addSectionController();

	// Populate Section combo box
	for (int section = 0; section < this->maestro_controller_->getNumSectionControllers(); section++) {
		ui->sectionComboBox->addItem("Section " + QString::number(section + 1));
	}
	ui->sectionComboBox->setCurrentIndex(active_section_);

	// Populate Animation combo box
	ui->animationComboBox->addItems({"Solid", "Blink", "Wave", "Pong", "Merge", "RandomIndex", "Sparkle", "Pattern", "Cycle"});

	// Populate color combo box
	ui->colorComboBox->addItems({"Custom", "Fire", "Deep Sea", "Color Wheel"});
	ui->colorComboBox->setCurrentIndex(2);

	// Set defaults
	ui->animationComboBox->setCurrentIndex(2);
	ui->cycleSlider->setValue((int)getActiveSectionController()->getSection()->getCycleSpeed());

	ui->rowsSpinBox->setValue(getActiveSectionController()->getSection()->getLayout()->rows);
	ui->columnsSpinBox->setValue(getActiveSectionController()->getSection()->getLayout()->columns);
}

void MaestroControl::on_cycleSlider_valueChanged(int value) {
	value = ui->cycleSlider->maximum() - value;
	getActiveSectionController()->getSection()->setCycleInterval((unsigned short)value);
	ui->cycleSlider->setToolTip(QString::number(value));
}

void MaestroControl::on_animationComboBox_currentIndexChanged(int index) {
	getActiveSectionController()->getSection()->setColorAnimation((Section::ColorAnimations)index, ui->reverseAnimationCheckBox->isChecked());
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
		case 0:	// Custom
			this->on_custom_color_changed();
			break;
		case 1:	// Fire
			{
				unsigned char numColors = 14;
				Colors::RGB fire[numColors];
				Colors::generateScalingColorArray(fire, Colors::RED, Colors::ORANGE, numColors, true);
				getActiveSectionController()->setControllerColors(fire, numColors);
				break;
			}
		case 2:	// Deep Sea
			{
				unsigned char numColors = 14;
				Colors::RGB deepSea[numColors];
				Colors::generateScalingColorArray(deepSea, Colors::BLUE, Colors::GREEN, numColors, true);
				getActiveSectionController()->setControllerColors(deepSea, numColors);
				break;
			}
		default:// Color Wheel
			getActiveSectionController()->getSection()->setColors(Colors::COLORWHEEL, 12);
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

	std::vector<Colors::RGB> tmpColors;
	tmpColors.resize(numColors);

	unsigned char threshold = 255 - (unsigned char)ui->thresholdSpinBox->value();
	Colors::generateScalingColorArray(&tmpColors[0], color, numColors, threshold, true);
	getActiveSectionController()->setControllerColors(&tmpColors[0], numColors);

	// Release tmpColors
	std::vector<Colors::RGB>().swap(tmpColors);
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

SectionController *MaestroControl::getActiveSectionController() {
	return this->maestro_controller_->getSectionController(active_section_);
}

void MaestroControl::on_fadeCheckBox_toggled(bool checked) {
	getActiveSectionController()->getSection()->toggleFade();
}

void MaestroControl::on_columnsSpinBox_valueChanged(int arg1) {
	getActiveSectionController()->setLayout(ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
	this->drawing_area_->resizePixels();
}

void MaestroControl::on_rowsSpinBox_valueChanged(int arg1) {
	getActiveSectionController()->setLayout(ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
	this->drawing_area_->resizePixels();
}
