#include "maestrocontrol.h"
#include "ui_maestrocontrol.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "drawingarea/simpledrawingarea.h"
#include <QPalette>
#include <QString>
#include "section.h"

/**
 * Constructor.
 * @param parent The QWidget containing this controller.
 * @param maestro_controller The MaestroController being controlled.
 */
MaestroControl::MaestroControl(QWidget* parent, MaestroController* maestro_controller) : QWidget(parent), ui(new Ui::MaestroControl) {

	// Assign easy reference variables for the Maestro
	this->maestro_controller_ = maestro_controller;

	// Initialize UI
	ui->setupUi(this);
	this->initialize();
}

/**
 * Applies the active Section settings to the UI.
 */
void MaestroControl::get_section_settings() {
	ui->animationComboBox->setCurrentIndex(active_section_controller_->get_section()->get_color_animation() - 1);
	ui->reverse_animationCheckBox->setChecked(active_section_controller_->get_section()->get_reverse());
	ui->fadeCheckBox->setChecked(active_section_controller_->get_section()->get_fade());
	ui->num_colorsSpinBox->setValue(active_section_controller_->get_section()->get_num_colors());

	ui->cycleSlider->setValue(this->active_section_controller_->get_section()->get_cycle_interval());
	ui->rowsSpinBox->setValue(this->active_section_controller_->get_section()->get_dimensions()->y);
	ui->columnsSpinBox->setValue(this->active_section_controller_->get_section()->get_dimensions()->x);

	QStringList section_type = ui->sectionComboBox->currentText().split(" ");
	if (QString::compare(section_type[0], "overlay", Qt::CaseInsensitive) == 0) {
		ui->mix_modeComboBox->setCurrentIndex(this->maestro_controller_->get_section_controller(section_type[1].toInt() - 1)->get_overlay()->mix_mode);
		ui->alphaSpinBox->setValue(this->maestro_controller_->get_section_controller(section_type[1].toInt() - 1)->get_overlay()->alpha);
	}
}

/**
 * Build the initial UI.
 */
void MaestroControl::initialize() {
	active_section_controller_ = maestro_controller_->get_section_controller(0);

	// Populate Animation combo box
	ui->animationComboBox->addItems({"Solid", "Blink", "Cycle", "Wave", "Pong", "Merge", "Random", "Sparkle"});

	// Populate color combo box
	ui->colorComboBox->addItems({"Custom", "Fire", "Deep Sea", "Color Wheel"});
	ui->colorComboBox->setCurrentIndex(2);
	this->setCustomColorControlsVisible(false);

	// Set default values
	ui->sectionComboBox->addItem("Section 1");


	// Add an Overlay
	active_section_controller_->add_overlay(Colors::MixMode::NONE);
	ui->sectionComboBox->addItem(QString("Overlay 1"));

	// Initialize Overlay controls
	ui->mix_modeComboBox->addItems({"None", "Normal", "Alpha Blending", "Multiply"});

	get_section_settings();
}

/**
 * Updates the color array based on changes to the color scheme and settings.
 * @param color Base color to use when generating the array.
 */
void MaestroControl::changeScalingColorArray(Colors::RGB color) {
	unsigned int num_colors = (unsigned int)ui->num_colorsSpinBox->value();

	std::vector<Colors::RGB> tmpColors;
	tmpColors.resize(num_colors);

	unsigned char threshold = 255 - (unsigned char)ui->thresholdSpinBox->value();
	Colors::generate_scaling_color_array(&tmpColors[0], &color, num_colors, threshold, true);
	this->active_section_controller_->set_controller_colors(&tmpColors[0], num_colors);

	// Release tmpColors
	std::vector<Colors::RGB>().swap(tmpColors);
}

void MaestroControl::on_alphaSpinBox_valueChanged(double arg1) {
	QStringList section = ui->sectionComboBox->currentText().split(" ");

	this->maestro_controller_->get_section_controller(section[1].toInt() - 1)->get_overlay()->alpha = arg1;
}

/**
 * Changes the current animation.
 * @param index Index of the new animation.
 */
void MaestroControl::on_animationComboBox_currentIndexChanged(int index) {
	this->active_section_controller_->get_section()->set_color_animation((Section::ColorAnimations)(index + 1), ui->reverse_animationCheckBox->isChecked());
}

/**
 * Changes the color scheme.
 * If 'Custom' is selected, this sets the custom color controls to visible. Otherwise it hides them.
 * @param index Index of the new color scheme.
 */
void MaestroControl::on_colorComboBox_currentIndexChanged(int index) {
	switch (index) {
		case 0:	// Custom
			this->on_custom_color_changed();
			this->setCustomColorControlsVisible(true);
			break;
		case 1:	// Fire
			{
				unsigned char num_colors = 14;
				Colors::RGB fire[num_colors];
				Colors::generate_scaling_color_array(fire, &Colors::RED, &Colors::ORANGE, num_colors, true);
				this->active_section_controller_->set_controller_colors(fire, num_colors);
				this->setCustomColorControlsVisible(false);
				break;
			}
		case 2:	// Deep Sea
			{
				unsigned char num_colors = 14;
				Colors::RGB deepSea[num_colors];
				Colors::generate_scaling_color_array(deepSea, &Colors::BLUE, &Colors::GREEN, num_colors, true);
				this->active_section_controller_->set_controller_colors(deepSea, num_colors);
				this->setCustomColorControlsVisible(false);
				break;
			}
		default:// Color Wheel
			this->active_section_controller_->get_section()->set_colors(Colors::COLORWHEEL, 12);
			this->setCustomColorControlsVisible(false);
	}
}

/**
 * Changes the number of columns in the display grid.
 * @param arg1 New number of columns.
 */
void MaestroControl::on_columnsSpinBox_valueChanged(int arg1) {
	// This is intentionally backwards
	this->active_section_controller_->set_dimensions(ui->rowsSpinBox->value(), ui->columnsSpinBox->value());

	// Set Overlay if applicable
	if (this->active_section_controller_->get_overlay_controller() != nullptr) {
		this->active_section_controller_->get_overlay_controller()->set_dimensions(ui->columnsSpinBox->value(), ui->rowsSpinBox->value());
	}
}


/**
 * Changes the custom color scheme.
 */
void MaestroControl::on_custom_color_changed() {
	if (ui->colorComboBox->currentIndex() != 0) {
		return;
	}

	unsigned char r = ui->redDial->value();
	unsigned char g = ui->greenDial->value();
	unsigned char b = ui->blueDial->value();

	changeScalingColorArray(Colors::RGB {r, g, b});
}

/**
 * Changes the cycle speed.
 * @param value New cycle speed.
 */
void MaestroControl::on_cycleSlider_valueChanged(int value) {
	value = ui->cycleSlider->maximum() - value;
	this->active_section_controller_->get_section()->set_cycle_interval((unsigned short)value);
	ui->cycleSlider->setToolTip(QString::number(value));
}

/**
 * Handles changes to the blue dial.
 * @param value New value of the blue dial.
 */
void MaestroControl::on_blueDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

/**
 * Toggles fading.
 * @param checked If true, fading is enabled.
 */
void MaestroControl::on_fadeCheckBox_toggled(bool checked) {
	this->active_section_controller_->get_section()->toggle_fade();
}

/**
 * Handles changes to the green dial.
 * @param value New value of the green dial.
 */
void MaestroControl::on_greenDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

void MaestroControl::on_mix_modeComboBox_currentIndexChanged(int index) {
	QStringList args = ui->sectionComboBox->currentText().split(" ");
	int sectionIndex = args[1].toInt() -1;

	if (this->maestro_controller_->get_section_controller(sectionIndex)->get_overlay_controller()) {
		this->maestro_controller_->get_section_controller(sectionIndex)->get_overlay()->mix_mode = (Colors::MixMode)index;

		// Show/hide spin box for alpha only
		if (index == 2) {
			ui->alphaSpinBox->setVisible(true);
		}
		else {
			ui->alphaSpinBox->setVisible(false);
		}
	}
}

/**
 * Sets the number of colors in the color scheme.
 * @param arg1 New color count.
 */
void MaestroControl::on_num_colorsSpinBox_valueChanged(int arg1) {
	this->on_custom_color_changed();
}

/**
 * Handles changes to the red dial.
 * @param value New value of the red dial.
 */
void MaestroControl::on_redDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

/**
 * Toggles whether the color animation is shown in reverse.
 * @param checked If true, reverse the animation.
 */
void MaestroControl::on_reverse_animationCheckBox_toggled(bool checked) {
	on_animationComboBox_currentIndexChanged(ui->animationComboBox->currentIndex());
}

/**
 * Changes the number of rows in the display grid.
 * @param arg1 New number of rows.
 */
void MaestroControl::on_rowsSpinBox_valueChanged(int arg1) {
	this->on_columnsSpinBox_valueChanged(arg1);
}

void MaestroControl::on_sectionComboBox_currentIndexChanged(const QString &arg1) {
	QStringList args = arg1.split(" ");
	QString type = args[0];
	int num = args[1].toInt();

	if(QString::compare(type, "section", Qt::CaseInsensitive) == 0) {
		// Set active controller using MaestroController's SectionControllers list
		this->active_section_controller_ = this->maestro_controller_->get_section_controller(num - 1);

		// Hide Overlay controls
		this->setOverlayControlsVisible(false);
	}
	else {	// Overlay
		// Set active controller to OverlayController
		this->active_section_controller_ = this->maestro_controller_->get_section_controller(num - 1)->get_overlay_controller().get();

		// Show Overlay controls
		this->setOverlayControlsVisible(true);
	}

	get_section_settings();
}

/**
 * Sets the variance of the colors in the color scheme.
 * @param arg1 New variance between colors (0-255).
 */
void MaestroControl::on_thresholdSpinBox_valueChanged(int arg1) {
	this->on_custom_color_changed();
}

/**
 * Toggles the visibility of the custom color scheme controls.
 * @param enabled If true, display custom controls.
 */
void MaestroControl::setCustomColorControlsVisible(bool enabled) {
	ui->redDial->setVisible(enabled);
	ui->greenDial->setVisible(enabled);
	ui->blueDial->setVisible(enabled);
	ui->num_colorsSpinBox->setVisible(enabled);
	ui->num_colorsLabel->setVisible(enabled);
	ui->thresholdSpinBox->setVisible(enabled);
	ui->thresholdLabel->setVisible(enabled);
}

/**
 * Sets the visibility of Overlay-related controls.
 * @param visible True if you want to show the controls.
 */
void MaestroControl::setOverlayControlsVisible(bool visible) {
	// If visible, show Overlay controls
	ui->mixModeLabel->setVisible(visible);
	ui->mix_modeComboBox->setVisible(visible);
	ui->alphaSpinBox->setVisible(visible);

	// Invert layout controls
	ui->gridSizeLabel->setVisible(!visible);
	ui->columnsSpinBox->setVisible(!visible);
	ui->rowsSpinBox->setVisible(!visible);
}

/**
 * Destructor.
 */
MaestroControl::~MaestroControl() {
	delete ui;
}
