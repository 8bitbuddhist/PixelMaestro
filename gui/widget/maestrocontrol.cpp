#include "animation/lightninganimation.h"
#include "animation/lightninganimationcontrol.h"
#include "animation/plasmaanimation.h"
#include "animation/plasmaanimationcontrol.h"
#include "animation/radialanimation.h"
#include "animation/radialanimationcontrol.h"
#include "animation/sparkleanimation.h"
#include "animation/sparkleanimationcontrol.h"
#include "canvas/animationcanvas.h"
#include "canvas/colorcanvas.h"
#include "canvas/canvascontrol.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "core/section.h"
#include "drawingarea/simpledrawingarea.h"
#include "window/settingsdialog.h"
#include "maestrocontrol.h"
#include "widget/palettecontrol.h"
#include <QFile>
#include <QSettings>
#include <QString>
#include <QTextStream>
#include "ui_maestrocontrol.h"

/**
 * Constructor.
 * @param parent The QWidget containing this controller.
 * @param maestro_controller The MaestroController being controlled.
 */
MaestroControl::MaestroControl(QWidget* parent, MaestroController* maestro_controller) : QWidget(parent), ui(new Ui::MaestroControl) {

	// Assign easy reference variables for the Maestro
	this->maestro_controller_ = maestro_controller;

	// Load settings
	QSettings settings;
	serial_enabled_ = settings.value(SettingsDialog::serial_enabled).toBool();
	serial_port_name_ = settings.value(SettingsDialog::serial_port).toString();

	// Initialize UI
	ui->setupUi(this);

	this->initialize();

	// Open serial connection to Arduino
	if (serial_enabled_) {
		initialize_cue_controller();

		serial_port_.setPortName(QString(serial_port_name_));
		serial_port_.setBaudRate(9600);

		// https://stackoverflow.com/questions/13312869/serial-communication-with-arduino-fails-only-on-the-first-message-after-restart
		serial_port_.setFlowControl(QSerialPort::FlowControl::NoFlowControl);
		serial_port_.setParity(QSerialPort::Parity::NoParity);
		serial_port_.setDataBits(QSerialPort::DataBits::Data8);
		serial_port_.setStopBits(QSerialPort::StopBits::OneStop);
		serial_port_.open(QIODevice::WriteOnly);

		// If the Serial port was configured successfully, send an initial animation.
		if (serial_port_.isOpen()) {
			section_handler->set_animation(get_section_index(), get_overlay_index(), AnimationType::Solid, false, &palette_controller_.get_palette(0)->colors[0], palette_controller_.get_palette(0)->colors.size());
			send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
		}
	}
}

/**
 * Returns the index of the current Overlay.
 * @return Overlay index.
 */
int16_t MaestroControl::get_overlay_index() {
	/*
	 * Find the depth of the current SectionController by iterating over each parent_controller.
	 * Once parent_controller = nullptr, we know we've hit the base Section.
	 */
	uint8_t depth = 0;
	SectionController* target_controller = active_section_controller_;
	while (target_controller->get_parent_controller() != nullptr) {
		target_controller = target_controller->get_parent_controller();
		depth++;
	}
	return depth;
}

/**
 * Returns the index of the current SectionController.
 * @return Current SectionController index. -1 if SectionController was not found.
 */
int16_t MaestroControl::get_section_index() {
	SectionController* target_controller = active_section_controller_;
	// If this is an Overlay, iterate until we find the parent ID
	while (target_controller->get_parent_controller() != nullptr) {
		target_controller = target_controller->get_parent_controller();
	}

	// Iterate until we find the SectionController that the Controller points to
	uint8_t index = 0;
	SectionController* test_controller = maestro_controller_->get_section_controller(0);
	while (test_controller != target_controller) {
		index++;
		test_controller = maestro_controller_->get_section_controller(index);
	}

	return index;
}

/**
 * Applies the active Section settings to the UI.
 */
void MaestroControl::get_section_settings() {
	// Apply animation options and speed
	Animation* animation = active_section_controller_->get_section()->get_animation();
	ui->orientationComboBox->setCurrentIndex(animation->get_orientation());
	ui->reverse_animationCheckBox->setChecked(animation->get_reverse());
	ui->fadeCheckBox->setChecked(animation->get_fade());
	ui->cycleSlider->setValue(ui->cycleSlider->maximum() - active_section_controller_->get_section()->get_animation()->get_speed());

	/*
	 * Get the animation type.
	 * We don't want to fire the signal and re-apply the animation.
	 */
	ui->animationComboBox->blockSignals(true);
	ui->animationComboBox->setCurrentIndex(active_section_controller_->get_section()->get_animation()->get_type());
	ui->animationComboBox->blockSignals(false);

	show_extra_controls(active_section_controller_->get_section()->get_animation());

	// Get Overlay MixMode and alpha from the Overlay's parent section
	QStringList section_type = ui->sectionComboBox->currentText().split(" ");
	if (QString::compare(section_type[0], "overlay", Qt::CaseInsensitive) == 0) {
		ui->mix_modeComboBox->setCurrentIndex(maestro_controller_->get_section_controller(section_type[1].toInt() - 1)->get_overlay()->mix_mode);
		ui->alphaSpinBox->setValue(maestro_controller_->get_section_controller(section_type[1].toInt() - 1)->get_overlay()->alpha);
	}

	if (active_section_controller_->palette_ != nullptr) {
		ui->colorComboBox->setCurrentText(QString::fromStdString(active_section_controller_->palette_->name));
	}
}

/**
 * Build the initial UI.
 */
void MaestroControl::initialize() {
	active_section_controller_ = maestro_controller_->get_section_controller(0);
	active_section_controller_->get_section()->set_animation(AnimationType::Solid, nullptr, 0);

	// Populate Animation combo box
	ui->animationComboBox->addItems({"Blink", "Cycle", "Lightning", "Mandelbrot", "Merge", "Plasma", "Radial", "Random", "Solid", "Sparkle", "Wave"});
	ui->orientationComboBox->addItems({"Horizontal", "Vertical"});

	// Set default values
	ui->sectionComboBox->addItem("Section 1");

	// Add an Overlay
	active_section_controller_->set_overlay(Colors::MixMode::None);
	active_section_controller_->get_overlay()->section->set_animation(AnimationType::Solid, nullptr, 0);
	ui->sectionComboBox->addItem(QString("Overlay 1"));

	// Initialize Overlay controls
	ui->mix_modeComboBox->addItems({"None", "Alpha", "Multiply", "Overlay"});
	ui->alphaSpinBox->setVisible(false);

	// Initialize Canvas controls
	ui->canvasComboBox->addItems({"No Canvas", "Animation Canvas", "Color Canvas"});

	// Show controls hidden for now
	ui->editEventsButton->setEnabled(false);
	ui->editEventsButton->setVisible(false);
	ui->showLabel->setVisible(false);
	ui->enableShowCheckBox->setVisible(false);

	initialize_palettes();

	get_section_settings();
}

/// Initializes Cue components.
void MaestroControl::initialize_cue_controller() {
	cue_controller_ = maestro_controller_->get_maestro()->set_cue_controller();
	cue_interpreter_ = new CueInterpreter();
	animation_handler = static_cast<AnimationCueHandler*>(cue_controller_->enable_handler(CueController::Handler::AnimationHandler));
	canvas_handler = static_cast<CanvasCueHandler*>(cue_controller_->enable_handler(CueController::Handler::CanvasHandler));
	maestro_handler = static_cast<MaestroCueHandler*>(cue_controller_->enable_handler(CueController::Handler::MaestroHandler));
	section_handler = static_cast<SectionCueHandler*>(cue_controller_->enable_handler(CueController::Handler::SectionHandler));
}

/// Reinitializes Palettes from Palette Dialog.
void MaestroControl::initialize_palettes() {
	ui->colorComboBox->clear();

	// Populate color combo box
	for (PaletteController::Palette palette : palette_controller_.get_palettes()) {
		ui->colorComboBox->addItem(QString::fromStdString(palette.name));
	}
}

/**
 * Sets the Overlay's transparency level.
 * @param arg1 Transparency level from 0 - 255.
 */
void MaestroControl::on_alphaSpinBox_valueChanged(int arg1) {
	maestro_controller_->get_section_controller(get_section_index())->get_overlay()->alpha = arg1;

	if (cue_controller_ != nullptr) {
		section_handler->set_overlay(get_section_index(), get_overlay_index(), maestro_controller_->get_section_controller(get_section_index())->get_overlay()->mix_mode, arg1);
		if (cue_controller_ != nullptr) {
			send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
		}
	}
}

/**
 * Changes the current animation.
 * @param index Index of the new animation.
 */
void MaestroControl::on_animationComboBox_currentIndexChanged(int index) {

	if (active_section_controller_->get_section()->get_animation() != nullptr) {
		// Only change if the animation is different
		if (active_section_controller_->get_section()->get_animation()->get_type() == index) {
			return;
		}
	}

	// Preserve the animation cycle between changes
	bool preserve_cycle_index = true;

	Animation* animation = active_section_controller_->get_section()->set_animation((AnimationType::Type)index, 0, preserve_cycle_index);

	show_extra_controls(animation);

	if (cue_controller_ != nullptr) {
		section_handler->set_animation(get_section_index(), get_overlay_index(), (AnimationType::Type)index, preserve_cycle_index, nullptr, 0);
		if (serial_port_.isOpen()) {
			send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
		}
	}

	// Reapply animation settings
	on_colorComboBox_currentIndexChanged(ui->colorComboBox->currentIndex());
	on_orientationComboBox_currentIndexChanged(ui->orientationComboBox->currentIndex());
	on_fadeCheckBox_toggled(ui->fadeCheckBox->isChecked());
	on_reverse_animationCheckBox_toggled(ui->reverse_animationCheckBox->isChecked());
	on_cycleSlider_valueChanged(ui->cycleSlider->value());
}

/**
 * Changes the current Canvas.
 * @param index Index of the new Canvas type.
 */
void MaestroControl::on_canvasComboBox_currentIndexChanged(int index) {
	// Remove the existing Canvas.
	active_section_controller_->get_section()->remove_canvas();
	canvas_controller_.reset();

	// Add the new Canvas
	if (index > 0) {
		canvas_controller_ = std::unique_ptr<CanvasController>(new CanvasController(active_section_controller_, (CanvasType::Type)(index - 1)));

		if (cue_controller_ != nullptr) {
			section_handler->set_canvas(get_section_index(), get_overlay_index(), (CanvasType::Type)index);
			if (serial_port_.isOpen()) {
				send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
			}
		}
	}

	show_canvas_controls();
}

/**
 * Changes the color scheme.
 * If 'Custom' is selected, this also displays controls for adjusting the custom color scheme.
 * @param index Index of the new color scheme.
 */
void MaestroControl::on_colorComboBox_currentIndexChanged(int index) {
	if (index < 0) {
		return;
	}

	PaletteController::Palette* palette = palette_controller_.get_palette(index);
	active_section_controller_->get_section()->get_animation()->set_colors(&palette->colors[0], palette->colors.size());
	active_section_controller_->palette_ = palette;


	if (cue_controller_ != nullptr) {
		animation_handler->set_colors(get_section_index(), get_overlay_index(), &palette->colors[0], palette->colors.size());
		if (serial_port_.isOpen()) {
			send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
		}
	}
}

/**
 * Changes the number of columns in the display grid.
 */
void MaestroControl::on_columnsSpinBox_editingFinished() {
	on_section_resize(ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
}

/**
 * Changes the cycle speed.
 * @param value New cycle speed.
 */
void MaestroControl::on_cycleSlider_valueChanged(int value) {
	ui->cycleSpinBox->blockSignals(true);
	ui->cycleSpinBox->setValue(value);
	ui->cycleSpinBox->blockSignals(false);

	set_speed();
}

void MaestroControl::on_cycleSpinBox_editingFinished() {
	ui->cycleSlider->blockSignals(true);
	ui->cycleSlider->setValue(ui->cycleSpinBox->value());
	ui->cycleSlider->blockSignals(false);

	set_speed();
}

void MaestroControl::on_editEventsButton_clicked() {
	ShowControl show_control(show_controller_.get(), cue_controller_, this);
	show_control.exec();
}

void MaestroControl::on_enableShowCheckBox_toggled(bool checked) {
	ui->editEventsButton->setEnabled(checked);

	if (show_controller_ == nullptr) {
		show_controller_ = std::unique_ptr<ShowController>(new ShowController(maestro_controller_));
	}
}

/**
 * Toggles fading.
 * @param checked If true, fading is enabled.
 */
void MaestroControl::on_fadeCheckBox_toggled(bool checked) {
	active_section_controller_->get_section()->get_animation()->set_fade(checked);

	if (cue_controller_ != nullptr) {
		animation_handler->set_fade(get_section_index(), get_overlay_index(), checked);
		if (serial_port_.isOpen()) {
			send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
		}
	}
}

/**
 * Changes the Overlay's mix mode.
 * @param index
 */
void MaestroControl::on_mix_modeComboBox_currentIndexChanged(int index) {
	if ((Colors::MixMode)index != maestro_controller_->get_section_controller(get_section_index())->get_overlay()->mix_mode) {
		if (maestro_controller_->get_section_controller(get_section_index())->get_overlay_controller()) {
			maestro_controller_->get_section_controller(get_section_index())->get_overlay()->mix_mode = (Colors::MixMode)index;

			// Show/hide spin box for alpha only
			if (ui->mix_modeComboBox->currentText().contains("Alpha")) {
				ui->alphaSpinBox->setVisible(true);
			}
			else {
				ui->alphaSpinBox->setVisible(false);
			}

			if (cue_controller_ != nullptr) {
				section_handler->set_overlay(get_section_index(), get_overlay_index(), (Colors::MixMode)index, ui->alphaSpinBox->value());
				if (serial_port_.isOpen()) {
					send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
				}
			}
		}
	}
}

/**
 * Sets the animation's orientation.
 * @param index New orientation.
 */
void MaestroControl::on_orientationComboBox_currentIndexChanged(int index) {
	if ((Animation::Orientation)index != active_section_controller_->get_section()->get_animation()->get_orientation()) {
		if (active_section_controller_->get_section()->get_animation()) {
			active_section_controller_->get_section()->get_animation()->set_orientation((Animation::Orientation)index);

			if (cue_controller_ != nullptr) {
				animation_handler->set_orientation(get_section_index(), get_overlay_index(), (Animation::Orientation)index);
				if (serial_port_.isOpen()) {
					send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
				}
			}
		}
	}
}

/**
 * Opens the Palette Editor.
 */
void MaestroControl::on_paletteControlButton_clicked() {
	std::string palette_name = active_section_controller_->palette_->name;

	PaletteControl palette_control(&this->palette_controller_, active_section_controller_->palette_->name);
	palette_control.exec();
	initialize_palettes();
	ui->colorComboBox->setCurrentText(QString::fromStdString(palette_name));
}

/**
 * Sets the delay between Animation cycles.
 * @param value New pause interval.
 */
void MaestroControl::on_pauseSlider_valueChanged(int value) {
	ui->pauseSpinBox->blockSignals(true);
	ui->pauseSpinBox->setValue(value);
	ui->pauseSpinBox->blockSignals(false);

	set_speed();
}

/**
 * Sets the delay between Animation cycles.
 * @param arg1 New pause interval.
 */
void MaestroControl::on_pauseSpinBox_valueChanged(int arg1) {
	ui->pauseSlider->blockSignals(true);
	ui->pauseSlider->setValue(arg1);
	ui->pauseSlider->blockSignals(false);

	set_speed();
}

/**
 * Toggles whether the color animation is shown in reverse.
 * @param checked If true, reverse the animation.
 */
void MaestroControl::on_reverse_animationCheckBox_toggled(bool checked) {
	active_section_controller_->get_section()->get_animation()->set_reverse(checked);

	if (cue_controller_ != nullptr) {
		animation_handler->set_reverse(get_section_index(), get_overlay_index(), checked);
		if (serial_port_.isOpen()) {
			send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
		}
	}
}

/**
 * Changes the number of rows in the displayed grid.
 */
void MaestroControl::on_rowsSpinBox_editingFinished() {
	on_section_resize(ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
}

/**
 * Changes the currently selected Section.
 * @param arg1 Index of the Section to switch to.
 */
void MaestroControl::on_sectionComboBox_currentIndexChanged(const QString &arg1) {
	QString type = arg1.split(" ")[0];
	int id = arg1.split(" ")[1].toInt() - 1;

	if(QString::compare(type, "section", Qt::CaseInsensitive) == 0) {
		// Set active controller
		active_section_controller_ = maestro_controller_->get_section_controller(id);

		// Hide Overlay controls
		this->set_overlay_controls_visible(false);
	}
	else {	// Overlay
		// Set active controller to OverlayController
		active_section_controller_ = active_section_controller_->get_overlay_controller();

		// Show Overlay controls
		set_overlay_controls_visible(true);
	}

	get_section_settings();
}

/**
 * Sets the size of the active SectionController.
 * @param x Number of rows.
 * @param y Number of columns.
 */
void MaestroControl::on_section_resize(uint16_t x, uint16_t y) {
	// Check the Canvas
	/*
	 * Disabled due to too many popups
	if (canvas_control_widget_ != nullptr) {
		CanvasControl* widget = qobject_cast<CanvasControl*>(canvas_control_widget_.get());
		if (!widget->confirm_clear()) {
			return;
		}
	}
	*/

	if ((x != active_section_controller_->get_section()->get_dimensions()->x) || (y != active_section_controller_->get_section()->get_dimensions()->y)) {
		active_section_controller_->get_section()->set_dimensions(x, y);

		/*
		 * Disabled dynamic resizing on remote devices.
		if (serial_.isOpen()) {
			section_handler->set_dimensions(get_section_index(), get_overlay_index(), ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
			if (serial_port_.isOpen()) {
				send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
			}
		}
		*/
	}
}

void MaestroControl::read_from_file(QString filename) {
	// Not yet finalized
	QFile file(filename);
	if (file.open(QFile::ReadOnly)) {
		while (file.atEnd() == false) {
			file.getChar((char*)cue_controller_->get_cue());
		}
		file.close();
	}
	get_section_settings();
}

void MaestroControl::save_to_file(QString filename) {
	QFile file(filename);
	if (file.open(QFile::WriteOnly)) {
		QTextStream textstream(&file);

		/*
		 * Implement serialization for:
		 * - Animation-specific options
		 * - Handle multiple Overlays
		 * - Palettes
		 */

		// Overlay
		if (active_section_controller_->get_overlay()->mix_mode != Colors::MixMode::None) {
			section_handler->set_overlay(0, 0, active_section_controller_->get_overlay()->mix_mode, active_section_controller_->get_overlay()->alpha);
			write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

			section_handler->set_animation(0, 1, (AnimationType::Type)ui->animationComboBox->currentIndex(), true, active_section_controller_->get_section()->get_animation()->get_colors(), active_section_controller_->get_section()->get_animation()->get_num_colors());
			write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

			animation_handler->set_orientation(0, 1, (Animation::Orientation)ui->orientationComboBox->currentIndex());
			write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

			animation_handler->set_reverse(0, 1, ui->reverse_animationCheckBox->isChecked());
			write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

			animation_handler->set_fade(0, 1, ui->fadeCheckBox->isChecked());
			write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

			animation_handler->set_speed(0, 1, ui->cycleSlider->maximum() - ui->cycleSlider->value(), 0);
		}

		// Dimensions
		section_handler->set_dimensions(0, 0, ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
		write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

		// Animaton & Colors
		section_handler->set_animation(0, 0, (AnimationType::Type)ui->animationComboBox->currentIndex(), true, active_section_controller_->get_section()->get_animation()->get_colors(), active_section_controller_->get_section()->get_animation()->get_num_colors());
		write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

		animation_handler->set_orientation(0, 0, (Animation::Orientation)ui->orientationComboBox->currentIndex());
		write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

		animation_handler->set_reverse(0, 0, ui->reverse_animationCheckBox->isChecked());
		write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

		animation_handler->set_fade(0, 0, ui->fadeCheckBox->isChecked());
		write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

		animation_handler->set_speed(0, 0, ui->cycleSlider->maximum() - ui->cycleSlider->value(), 0);
		write_cue_to_stream(&textstream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

		file.flush();
		file.close();
	}
}

/// Sets the speed and/or pause interval for the active Animation.
void MaestroControl::set_speed() {
	uint16_t pause = ui->pauseSpinBox->value();
	uint16_t speed = ui->cycleSpinBox->value();
	Animation* animation = active_section_controller_->get_section()->get_animation();
	if (speed != animation->get_speed() || pause != animation->get_pause()) {
		animation->set_speed(speed, pause);

		if (cue_controller_ != nullptr) {
			animation_handler->set_speed(get_section_index(), get_overlay_index(), speed, 0);
			if (serial_port_.isOpen()) {
				send_to_device(cue_controller_->get_cue(), cue_controller_->get_cue_size());
			}
		}
	}
}

/**
 * Appends a Cue to a stream, followed by a newline.
 * @param stream Stream to append to.
 * @param cue Cue to append.
 * @param cue_size Size of Cue.
 */
void MaestroControl::write_cue_to_stream(QTextStream* stream, uint8_t *cue, uint8_t cue_size) {
	for (uint8_t i = 0; i < cue_size; i++) {
		*stream << cue[i];
	}
	*stream << "\n";
}

void MaestroControl::send_to_device(uint8_t* out, uint8_t size) {
	serial_port_.write((const char*)out, size);
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
 * Displays extra controls for animations that take custom parameters.
 * @param index Index of the animation in the animations list.
 * @param animation Pointer to the animation.
 */
void MaestroControl::show_extra_controls(Animation* animation) {
	// First, remove any existing extra control widgets
	if (extra_control_widget_ != nullptr) {
		this->findChild<QLayout*>("extraControlsLayout")->removeWidget(extra_control_widget_.get());
		extra_control_widget_.reset();
	}

	QLayout* layout = this->findChild<QLayout*>("extraControlsLayout");

	switch(animation->get_type()) {
		case AnimationType::Lightning:
			extra_control_widget_ = std::unique_ptr<QWidget>(new LightningAnimationControl((LightningAnimation*)animation, this, layout->widget()));
			break;
		case AnimationType::Plasma:
			extra_control_widget_ = std::unique_ptr<QWidget>(new PlasmaAnimationControl((PlasmaAnimation*)animation, this, layout->widget()));
			break;
		case AnimationType::Radial:
			extra_control_widget_ = std::unique_ptr<QWidget>(new RadialAnimationControl((RadialAnimation*)animation, this, layout->widget()));
			break;
		case AnimationType::Sparkle:
			extra_control_widget_ = std::unique_ptr<QWidget>(new SparkleAnimationControl((SparkleAnimation*)animation, this, layout->widget()));
			break;
		default:
			break;
	}

	if (extra_control_widget_) {
		layout->addWidget(extra_control_widget_.get());
	}
}

void MaestroControl::show_canvas_controls() {
	QLayout* layout = this->findChild<QLayout*>("canvasControlsLayout");

	// Remove the Canvas controls.
	// If a Canvas is set, re-initialize and re-add the controls.
	layout->removeWidget(canvas_control_widget_.get());
	canvas_control_widget_.reset();

	if (canvas_controller_ != nullptr && canvas_controller_->get_canvas() != nullptr) {
		canvas_control_widget_ = std::unique_ptr<QWidget>(new CanvasControl(canvas_controller_.get()));
		layout->addWidget(canvas_control_widget_.get());
	}
}

/**
 * Destructor.
 */
MaestroControl::~MaestroControl() {
	if (cue_controller_ != nullptr) {
		serial_port_.close();
	}
	delete cue_interpreter_;
	delete ui;
}
