#include "animation/blinkanimation.h"
#include "animation/cycleanimation.h"
#include "animation/lightninganimation.h"
#include "animation/lightninganimationcontrol.h"
#include "animation/mergeanimation.h"
#include "animation/mandelbrotanimation.h"
#include "animation/plasmaanimation.h"
#include "animation/plasmaanimationcontrol.h"
#include "animation/radialanimation.h"
#include "animation/randomanimation.h"
#include "animation/solidanimation.h"
#include "animation/sparkleanimation.h"
#include "animation/sparkleanimationcontrol.h"
#include "animation/waveanimation.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "core/section.h"
#include "drawingarea/simpledrawingarea.h"
#include "maestrocontrol.h"
#include <QPalette>
#include <QString>
#include "ui_maestrocontrol.h"

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
	// Get the animation type
	std::string type(typeid(*active_section_controller_->get_section()->get_animation()).name());
	for (unsigned int index = 0; index < (unsigned int)ui->animationComboBox->count(); index++) {
		if (type.find(ui->animationComboBox->itemText(index).toStdString()) != std::string::npos) {
			ui->animationComboBox->setCurrentIndex(index);
			continue;
		}
	}

	ui->orientationComboBox->setCurrentIndex(active_section_controller_->get_section()->get_animation()->get_orientation());

	ui->reverse_animationCheckBox->setChecked(active_section_controller_->get_section()->get_animation()->get_reverse());
	ui->fadeCheckBox->setChecked(active_section_controller_->get_section()->get_animation()->get_fade());
	ui->num_colorsSpinBox->setValue(active_section_controller_->get_section()->get_animation()->get_num_colors());
	ui->cycleSlider->setValue(this->active_section_controller_->get_section()->get_cycle_interval());

	QStringList section_type = ui->sectionComboBox->currentText().split(" ");
	if (QString::compare(section_type[0], "overlay", Qt::CaseInsensitive) == 0) {
		ui->mix_modeComboBox->setCurrentIndex(this->maestro_controller_->get_section_controller(section_type[1].toInt() - 1)->get_overlay()->mix_mode);
		ui->alphaSpinBox->setValue(this->maestro_controller_->get_section_controller(section_type[1].toInt() - 1)->get_overlay()->alpha);
	}

	Colors::RGB* first_color = active_section_controller_->get_section()->get_animation()->get_color_at_index(0);
	if (*first_color == Colors::RED){
		if (active_section_controller_->get_section()->get_animation()->get_num_colors() == 12) {
			// Colorwheel
			ui->colorComboBox->setCurrentIndex(3);
		}
		else {
			// Fire
			ui->colorComboBox->setCurrentIndex(1);
		}
	}
	else if (*first_color == Colors::BLUE) {
		ui->colorComboBox->setCurrentIndex(2);
	}
	else {
		ui->colorComboBox->setCurrentIndex(0);
		ui->redSlider->setValue(first_color->r);
		ui->greenSlider->setValue(first_color->g);
		ui->blueSlider->setValue(first_color->b);
		on_custom_color_changed();
	}
}

/**
 * Build the initial UI.
 */
void MaestroControl::initialize() {
	active_section_controller_ = maestro_controller_->get_section_controller(0);
	active_section_controller_->get_section()->set_animation(new SolidAnimation());

	// Populate Animation combo box
	ui->animationComboBox->addItems({"Solid", "Blink", "Cycle", "Wave", "Merge", "Random", "Sparkle", "Radial", "Mandelbrot", "Plasma", "Lightning"});
	ui->orientationComboBox->addItems({"Horizontal", "Vertical"});

	// Populate color combo box
	ui->colorComboBox->addItems({"Custom", "Fire", "Deep Sea", "Color Wheel"});
	ui->colorComboBox->setCurrentIndex(2);
	this->set_custom_color_controls_visible(false);

	// Set default values
	ui->sectionComboBox->addItem("Section 1");

	// Add an Overlay
	active_section_controller_->add_overlay(Colors::MixMode::NONE);
	active_section_controller_->get_overlay()->section->set_animation(new SolidAnimation());
	active_section_controller_->get_overlay_controller()->set_colors(Colors::COLORWHEEL, 12);
	ui->sectionComboBox->addItem(QString("Overlay 1"));

	// Initialize Overlay controls
	ui->mix_modeComboBox->addItems({"None", "Normal", "Alpha Blending", "Multiply", "Overlay"});

	get_section_settings();
}

/**
 * Updates the color array based on changes to the color scheme and settings.
 * @param color Base color to use when generating the array.
 */
void MaestroControl::change_scaling_color_array(Colors::RGB color) {
	unsigned int num_colors = (unsigned int)ui->num_colorsSpinBox->value();

	std::vector<Colors::RGB> tmp_colors;
	tmp_colors.resize(num_colors);

	unsigned char threshold = 255 - (unsigned char)ui->thresholdSpinBox->value();
	Colors::generate_scaling_color_array(&tmp_colors[0], &color, num_colors, threshold, true);
	active_section_controller_->set_colors(&tmp_colors[0], num_colors);

	// Release tmp_colors
	std::vector<Colors::RGB>().swap(tmp_colors);
}

/**
 * Sets the Overlay's transparency level.
 * @param arg1 Transparency level from 0 - 1.
 */
void MaestroControl::on_alphaSpinBox_valueChanged(double arg1) {
	if (arg1 != maestro_controller_->get_section_controller(0)->get_overlay()->alpha) {
		maestro_controller_->get_section_controller(0)->get_overlay()->alpha = arg1;
	}
}

/**
 * Changes the current animation.
 * @param index Index of the new animation.
 */
void MaestroControl::on_animationComboBox_currentIndexChanged(int index) {
	if (active_section_controller_->get_section()->get_animation() != nullptr) {
		// Only change if the animation is different
		std::string type(typeid(*active_section_controller_->get_section()->get_animation()).name());
		if (type.compare(ui->animationComboBox->itemText(index).toStdString()) == 0) {
			return;
		}

		delete active_section_controller_->get_section()->get_animation();

		// Remove any existing extra control widgets
		if (extra_control_widget_ != nullptr) {
			this->findChild<QLayout*>("extraControlsLayout")->removeWidget(extra_control_widget_.get());
			extra_control_widget_.reset();
		}
	}

	// Preserve the animation cycle between changes
	bool preserve_cycle_index = true;

	switch(index) {
		case 0:
			active_section_controller_->get_section()->set_animation(new SolidAnimation(), preserve_cycle_index);
			break;
		case 1:
			active_section_controller_->get_section()->set_animation(new BlinkAnimation(), preserve_cycle_index);
			break;
		case 2:
			active_section_controller_->get_section()->set_animation(new CycleAnimation(), preserve_cycle_index);
			break;
		case 3:
			active_section_controller_->get_section()->set_animation(new WaveAnimation(), preserve_cycle_index);
			break;
		case 4:
			active_section_controller_->get_section()->set_animation(new MergeAnimation(), preserve_cycle_index);
			break;
		case 5:
			active_section_controller_->get_section()->set_animation(new RandomAnimation(), preserve_cycle_index);
			break;
		case 6:
			{
				active_section_controller_->get_section()->set_animation(new SparkleAnimation(), preserve_cycle_index);
				QLayout* layout = this->findChild<QLayout*>("extraControlsLayout");
				extra_control_widget_ = std::unique_ptr<QWidget>(new SparkleAnimationControl((SparkleAnimation*)active_section_controller_->get_section()->get_animation(), layout->widget()));
				layout->addWidget(extra_control_widget_.get());
			}
			break;
		case 7:
			active_section_controller_->get_section()->set_animation(new RadialAnimation(), preserve_cycle_index);
			break;
		case 8:
			active_section_controller_->get_section()->set_animation(new MandelbrotAnimation(), preserve_cycle_index);
			break;
		case 9:
			{
				active_section_controller_->get_section()->set_animation(new PlasmaAnimation(), preserve_cycle_index);
				QLayout* layout = this->findChild<QLayout*>("extraControlsLayout");
				extra_control_widget_ = std::unique_ptr<QWidget>(new PlasmaAnimationControl((PlasmaAnimation*)active_section_controller_->get_section()->get_animation(), layout->widget()));
				layout->addWidget(extra_control_widget_.get());
				break;
			}
		case 10:
			{
				active_section_controller_->get_section()->set_animation(new LightningAnimation(), preserve_cycle_index);
				QLayout* layout = this->findChild<QLayout*>("extraControlsLayout");
				extra_control_widget_ = std::unique_ptr<QWidget>(new LightningAnimationControl((LightningAnimation*)active_section_controller_->get_section()->get_animation(), layout->widget()));
				layout->addWidget(extra_control_widget_.get());
			}
			break;
		default:
			return;
	}


	// Set orientation, fade, reverse, and color palette
	active_section_controller_->get_section()->get_animation()->set_orientation((Animation::Orientations)ui->orientationComboBox->currentIndex());
	active_section_controller_->get_section()->get_animation()->set_fade(ui->fadeCheckBox->isChecked());
	active_section_controller_->get_section()->get_animation()->set_reverse(ui->reverse_animationCheckBox->isChecked());
	on_colorComboBox_currentIndexChanged(ui->colorComboBox->currentIndex());
}

/**
 * Changes the color scheme.
 * If 'Custom' is selected, this also displays controls for adjusting the custom color scheme.
 * @param index Index of the new color scheme.
 */
void MaestroControl::on_colorComboBox_currentIndexChanged(int index) {
	switch (index) {
		case 0:	// Custom
			on_custom_color_changed();
			set_custom_color_controls_visible(true);
			break;
		case 1:	// Fire
			{
				unsigned char num_colors = 14;
				Colors::RGB fire[num_colors];
				Colors::generate_scaling_color_array(fire, &Colors::RED, &Colors::YELLOW, num_colors, true);
				active_section_controller_->set_colors(fire, num_colors);
				set_custom_color_controls_visible(false);
				break;
			}
		case 2:	// Deep Sea
			{
				unsigned char num_colors = 14;
				Colors::RGB deep_sea[num_colors];
				Colors::generate_scaling_color_array(deep_sea, &Colors::BLUE, &Colors::GREEN, num_colors, true);
				active_section_controller_->set_colors(deep_sea, num_colors);
				set_custom_color_controls_visible(false);
				break;
			}
		default:// Color Wheel
			active_section_controller_->set_colors(Colors::COLORWHEEL, 12);
			set_custom_color_controls_visible(false);
	}
}

/**
 * Changes the number of columns in the display grid.
 */
void MaestroControl::on_columnsSpinBox_valueChanged(int arg1) {
	// Got the names backwards
	on_section_resize(ui->rowsSpinBox->value(), arg1);
}


/**
 * Changes the custom color scheme.
 */
void MaestroControl::on_custom_color_changed() {
	// Verify that the custom color scheme option is selected, and that the color is different from the one used in the Section.
	if (ui->colorComboBox->currentIndex() != 0) {
		return;
	}

	Colors::RGB new_color = {
		(unsigned char)ui->redSlider->value(),
		(unsigned char)ui->greenSlider->value(),
		(unsigned char)ui->blueSlider->value()
	};

	if (active_section_controller_->get_section()->get_animation()->get_num_colors() == 0 || (new_color != *active_section_controller_->get_section()->get_animation()->get_color_at_index(0))) {
		change_scaling_color_array(new_color);

		ui->baseColorPreviewLabel->setText(QString("{%1, %2, %3}").arg(new_color.r).arg(new_color.g).arg(new_color.b));
		ui->baseColorPreviewLabel->setStyleSheet(QString("QLabel { color: rgb(%1, %2, %3); font-weight: bold; }").arg(new_color.r).arg(new_color.g).arg(new_color.b));
	}
}

/**
 * Changes the cycle speed.
 * @param value New cycle speed.
 */
void MaestroControl::on_cycleSlider_valueChanged(int value) {
	if (value != active_section_controller_->get_section()->get_cycle_interval()) {
		value = ui->cycleSlider->maximum() - value;
		active_section_controller_->get_section()->set_cycle_interval((unsigned short)value);
		ui->cycleSlider->setToolTip(QString::number(value));
	}
}

/**
 * Handles changes to the blue custom color slider.
 * @param value New value of the blue slider.
 */
void MaestroControl::on_blueSlider_valueChanged(int value) {
	on_custom_color_changed();
}

/**
 * Toggles fading.
 * @param checked If true, fading is enabled.
 */
void MaestroControl::on_fadeCheckBox_toggled(bool checked) {
	if (checked != active_section_controller_->get_section()->get_animation()->get_fade()) {
		active_section_controller_->get_section()->get_animation()->set_fade(checked);
	}
}

/**
 * Handles changes to the green custom color slider.
 * @param value New value of the green slider.
 */
void MaestroControl::on_greenSlider_valueChanged(int value) {
	on_custom_color_changed();
}

/**
 * Changes the Overlay's mix mode.
 * @param index
 */
void MaestroControl::on_mix_modeComboBox_currentIndexChanged(int index) {
	if ((Colors::MixMode)index != maestro_controller_->get_section_controller(0)->get_overlay()->mix_mode) {
		if (maestro_controller_->get_section_controller(0)->get_overlay_controller()) {
			maestro_controller_->get_section_controller(0)->get_overlay()->mix_mode = (Colors::MixMode)index;

			// Show/hide spin box for alpha only
			if (index == 2) {
				ui->alphaSpinBox->setVisible(true);
			}
			else {
				ui->alphaSpinBox->setVisible(false);
			}
		}
	}
}

/**
 * Sets the number of colors in the color scheme.
 * @param arg1 New color count.
 */
void MaestroControl::on_num_colorsSpinBox_valueChanged(int arg1) {
	on_custom_color_changed();
}

/**
 * Sets the animation's orientation
 * @param index New orientation.
 */
void MaestroControl::on_orientationComboBox_currentIndexChanged(int index) {
	if ((Animation::Orientations)index != active_section_controller_->get_section()->get_animation()->get_orientation()) {
		if (active_section_controller_->get_section()->get_animation()) {
			active_section_controller_->get_section()->get_animation()->set_orientation((Animation::Orientations)index);
		}
	}
}

/**
 * Handles changes to the red custom color slider.
 * @param value New value of the red slider.
 */
void MaestroControl::on_redSlider_valueChanged(int value) {
	on_custom_color_changed();
}

/**
 * Toggles whether the color animation is shown in reverse.
 * @param checked If true, reverse the animation.
 */
void MaestroControl::on_reverse_animationCheckBox_toggled(bool checked) {
	if (checked != active_section_controller_->get_section()->get_animation()->get_reverse()) {
		active_section_controller_->get_section()->get_animation()->set_reverse(checked);
	}
}

/**
 * Changes the number of rows in the display grid.
 * @param arg1 New number of rows.
 */
void MaestroControl::on_rowsSpinBox_valueChanged(int arg1) {
	// Got the names backwards
	on_section_resize(arg1, ui->columnsSpinBox->value());
}

void MaestroControl::on_sectionComboBox_currentIndexChanged(const QString &arg1) {
	QString type = arg1.split(" ")[0];

	if(QString::compare(type, "section", Qt::CaseInsensitive) == 0) {
		// Set active controller
		active_section_controller_ = maestro_controller_->get_section_controller(0);

		// Hide Overlay controls
		this->set_overlay_controls_visible(false);
	}
	else {	// Overlay
		// Set active controller to OverlayController
		active_section_controller_ = active_section_controller_->get_overlay_controller().get();

		// Show Overlay controls
		set_overlay_controls_visible(true);
	}

	get_section_settings();
}

/**
 * Sets the variance of the colors in the color scheme.
 * @param arg1 New variance between colors (0-255).
 */
void MaestroControl::on_thresholdSpinBox_valueChanged(int arg1) {
	on_custom_color_changed();
}

/**
 * Sets the size of the active SectionController.
 * @param x Number of rows.
 * @param y Number of columns.
 */
void MaestroControl::on_section_resize(unsigned short x, unsigned short y) {
	if ((x != active_section_controller_->get_dimensions().x) || (y != active_section_controller_->get_dimensions().y)) {
		active_section_controller_->set_dimensions(x, y);
	}
}

/**
 * Toggles the visibility of the custom color scheme controls.
 * @param visible If true, display custom controls.
 */
void MaestroControl::set_custom_color_controls_visible(bool visible) {
	ui->baseColorLabel->setVisible(visible);
	ui->baseColorPreviewLabel->setVisible(visible);
	ui->redSlider->setVisible(visible);
	ui->greenSlider->setVisible(visible);
	ui->blueSlider->setVisible(visible);
	ui->num_colorsSpinBox->setVisible(visible);
	ui->num_colorsLabel->setVisible(visible);
	ui->thresholdSpinBox->setVisible(visible);
	ui->thresholdLabel->setVisible(visible);
}

/**
 * Sets the visibility of Overlay-related controls.
 * @param visible True if you want to show the controls.
 */
void MaestroControl::set_overlay_controls_visible(bool visible) {
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
