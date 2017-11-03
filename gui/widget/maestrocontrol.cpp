#include <QDataStream>
#include <QFile>
#include <QMessageBox>
#include <QSettings>
#include <QString>
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
#include "maestrocontrol.h"
#include "window/settingsdialog.h"
#include "widget/palettecontrol.h"
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

	initialize();

	initialize_cue_controller();

	// Open serial connection to Arduino (if configured)
	QSettings settings;
	if (settings.value(SettingsDialog::serial_enabled).toBool()) {
	serial_port_.setPortName(QString(settings.value(SettingsDialog::serial_port).toString()));
		serial_port_.setBaudRate(9600);

		// https://stackoverflow.com/questions/13312869/serial-communication-with-arduino-fails-only-on-the-first-message-after-restart
		serial_port_.setFlowControl(QSerialPort::FlowControl::NoFlowControl);
		serial_port_.setParity(QSerialPort::Parity::NoParity);
		serial_port_.setDataBits(QSerialPort::DataBits::Data8);
		serial_port_.setStopBits(QSerialPort::StopBits::OneStop);

		if (!serial_port_.open(QIODevice::WriteOnly)) {
			QMessageBox::warning(nullptr, QString("Serial Failure"), QString("Failed to open serial device: " + serial_port_.errorString()));
		}
	}

	// Create an initial Cue.
	if (cue_controller_ != nullptr) {
		section_handler->set_animation(get_section_index(), get_overlay_index(), AnimationType::Blink, false, &palette_controller_.get_palette(0)->colors[0], palette_controller_.get_palette(0)->colors.size());
		send_to_device();
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
 * Build the initial UI.
 */
void MaestroControl::initialize() {
	active_section_controller_ = maestro_controller_->get_section_controller(0);
	active_section_controller_->get_section()->set_animation(AnimationType::Solid, nullptr, 0);

	// There must be a better way to bulk block signals.
	ui->animationComboBox->blockSignals(true);
	ui->orientationComboBox->blockSignals(true);
	ui->sectionComboBox->blockSignals(true);
	ui->mix_modeComboBox->blockSignals(true);
	ui->alphaSpinBox->blockSignals(true);
	ui->canvasComboBox->blockSignals(true);

	ui->animationComboBox->clear();
	ui->orientationComboBox->clear();
	ui->sectionComboBox->clear();
	ui->mix_modeComboBox->clear();
	ui->alphaSpinBox->clear();
	ui->canvasComboBox->clear();

	// Unblock signals (*grumble grumble*)
	ui->animationComboBox->blockSignals(false);
	ui->orientationComboBox->blockSignals(false);
	ui->sectionComboBox->blockSignals(false);
	ui->mix_modeComboBox->blockSignals(false);
	ui->alphaSpinBox->blockSignals(false);
	ui->canvasComboBox->blockSignals(false);

	// Populate Animation combo box
	ui->animationComboBox->addItems({"Blink", "Cycle", "Lightning", "Mandelbrot", "Merge", "Plasma", "Radial", "Random", "Solid", "Sparkle", "Wave"});
	ui->orientationComboBox->addItems({"Horizontal", "Vertical"});

	// Set default values
	// TODO: Iterate over each SectionController in the MaestroController and add it to the drop-down, then select Section 1 (item 0)
	ui->sectionComboBox->addItem("Section 1");
	ui->sectionComboBox->addItem(QString("Overlay 1"));

	// Initialize Overlay controls
	ui->mix_modeComboBox->addItems({"None", "Alpha", "Multiply", "Overlay"});
	ui->alphaSpinBox->setVisible(false);

	// Initialize Canvas controls
	ui->canvasComboBox->addItems({"No Canvas", "Animation Canvas", "Color Canvas"});

	// Disable Edit Show Events box by default.
	ui->editEventsButton->setEnabled(false);

	initialize_palettes();

	// Hide Show controls (again)
	ui->showLabel->setVisible(false);
	ui->editEventsButton->setVisible(false);
	ui->enableShowCheckBox->setVisible(false);

	set_active_section_controller(maestro_controller_->get_section_controller(0));
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
	if (active_section_controller_->get_parent_controller() == nullptr) {
		return;
	}
	active_section_controller_->get_parent_controller()->get_overlay()->alpha = arg1;

	if (cue_controller_ != nullptr) {
		section_handler->set_overlay(get_section_index(), get_overlay_index(), active_section_controller_->get_parent_controller()->get_overlay()->mix_mode, arg1);
		send_to_device();
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
		send_to_device();
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

	if (cue_controller_ != nullptr) {
		section_handler->remove_canvas(get_section_index(), get_overlay_index());
		send_to_device();
	}

	// Add the new Canvas
	if (index > 0) {
		active_section_controller_->get_section()->set_canvas((CanvasType::Type)(index - 1));

		if (cue_controller_ != nullptr) {
			section_handler->set_canvas(get_section_index(), get_overlay_index(), (CanvasType::Type)(index - 1));
			send_to_device();
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
		send_to_device();
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
	ShowControl show_control(show_controller_, cue_controller_, this);
	show_control.exec();
}

void MaestroControl::on_enableShowCheckBox_toggled(bool checked) {
	ui->editEventsButton->setEnabled(checked);

	// Initialize Show and Cue controllers if necessary
	if (checked) {
		if (cue_controller_ == nullptr) {
			initialize_cue_controller();
		}

		if (show_controller_ == nullptr) {
			show_controller_ = new ShowController(maestro_controller_);
		}
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
		send_to_device();
	}
}

/**
 * Changes the Overlay's mix mode.
 * @param index
 */
void MaestroControl::on_mix_modeComboBox_currentIndexChanged(int index) {
	if (active_section_controller_->get_parent_controller() == nullptr) {
		return;
	}

	if ((Colors::MixMode)index != active_section_controller_->get_parent_controller()->get_overlay()->mix_mode) {
		active_section_controller_->get_parent_controller()->get_overlay()->mix_mode = (Colors::MixMode)index;

		// Show/hide spin box for alpha only
		if (ui->mix_modeComboBox->currentText().contains("Alpha")) {
			ui->alphaSpinBox->setVisible(true);
		}
		else {
			ui->alphaSpinBox->setVisible(false);
		}

		if (cue_controller_ != nullptr) {
			section_handler->set_overlay(get_section_index(), get_overlay_index(), (Colors::MixMode)index, ui->alphaSpinBox->value());
			send_to_device();
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
				send_to_device();
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
		send_to_device();
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
		// Hide Overlay controls
		set_overlay_controls_visible(false);

		// Set active controller
		set_active_section_controller(maestro_controller_->get_section_controller(id));
	}
	else {	// Overlay
		// Check to make sure the Section has an Overlay. If not, add one.
		if (active_section_controller_->get_overlay() == nullptr) {
			active_section_controller_->set_overlay(Colors::MixMode::None);
			active_section_controller_->get_overlay()->section->set_animation(AnimationType::Solid, nullptr, 0);

			if (cue_controller_ != nullptr) {
				section_handler->set_overlay(get_section_index(), get_overlay_index(), active_section_controller_->get_overlay()->mix_mode, active_section_controller_->get_overlay()->alpha);
				send_to_device();
			}
		}

		// Show Overlay controls
		set_overlay_controls_visible(true);

		// Set active controller to OverlayController
		set_active_section_controller(active_section_controller_->get_overlay_controller());
	}


}

/**
 * Sets the size of the active SectionController.
 * @param x Number of rows.
 * @param y Number of columns.
 */
void MaestroControl::on_section_resize(uint16_t x, uint16_t y) {
	// Check the Canvas
	/*
	 * Disabled due to an excessive amount of popups
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
		 * Disabled dynamic resizing on remote devices, because that would just be silly.
		 *
		if (cue_controller_ != nullptr) {
			section_handler->set_dimensions(get_section_index(), get_overlay_index(), ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
			send_to_device();
		}
		*/
	}
}

void MaestroControl::read_from_file(QString filename) {
	QFile file(filename);

	if (file.open(QFile::ReadOnly)) {
		// Reinitialize UI
		initialize();

		QByteArray bytes = file.readAll();
		for (int i = 0; i < bytes.size(); i++) {
			cue_controller_->read((uint8_t)bytes.at(i));
		}
		file.close();
	}

	/*
	 * FIXME:
	 * Colors:
	 *		The CueController will delete the current color array.
	 *		We need some way to detect a call to animation_handler::set_colors() and override it to create a new palette.
	 *		Or, add a "Blank" or "Default" palette that we set before reading in Cues.
	 * Cues:
	 *		SectionHandler::set_overlay() isn't working
	 */
	set_active_section_controller(maestro_controller_->get_section_controller(0));
}

void MaestroControl::save_to_file(QString filename) {
	if (!filename.endsWith(".pmc", Qt::CaseInsensitive)) {
		filename.append(".pmc");
	}
	QFile file(filename);
	if (file.open(QFile::WriteOnly)) {
		QDataStream datastream(&file);

		// Iterate through each Section and save its settings to file
		for (uint8_t i = 0; i < maestro_controller_->get_num_section_controllers(); i++) {
			save_section_settings(&datastream, i, 0);

			// Save Overlay(s)
			uint16_t overlay_count = 0;
			Section::Overlay* overlay = maestro_controller_->get_section_controller(i)->get_overlay();
			while (overlay != nullptr) {
				overlay_count++;
				save_section_settings(&datastream, i, overlay_count);
				overlay = overlay->section->get_overlay();
			}
		}

		file.flush();
		file.close();
	}
}

void MaestroControl::save_section_settings(QDataStream* datastream, uint8_t section_id, uint8_t overlay_id) {

	Section* section = maestro_controller_->get_section_controller(section_id)->get_section();

	if (overlay_id) {
		for (uint8_t i = 0; i < overlay_id; i++) {
			section = section->get_overlay()->section;
		}
	}

	// Check for Overlay
	if (section->get_overlay() != nullptr) {
		Section::Overlay* overlay = section->get_overlay();

		section_handler->set_overlay(section_id, overlay_id, overlay->mix_mode, overlay->alpha);
		write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());
	}

	// Dimensions
	section_handler->set_dimensions(section_id, overlay_id, ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
	write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

	// Animation & Colors
	section_handler->set_animation(section_id, overlay_id, (AnimationType::Type)ui->animationComboBox->currentIndex(), true, active_section_controller_->get_section()->get_animation()->get_colors(), active_section_controller_->get_section()->get_animation()->get_num_colors());
	write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

	animation_handler->set_orientation(section_id, overlay_id, section->get_animation()->get_orientation());
	write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

	animation_handler->set_reverse(section_id, overlay_id, ui->reverse_animationCheckBox->isChecked());
	write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

	animation_handler->set_fade(section_id, overlay_id, ui->fadeCheckBox->isChecked());
	write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

	animation_handler->set_speed(section_id, overlay_id, ui->cycleSlider->value(), ui->pauseSlider->value());
	write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

	switch(section->get_animation()->get_type()) {
		case AnimationType::Lightning:
			{
				LightningAnimation* animation = static_cast<LightningAnimation*>(section->get_animation());
				animation_handler->set_lightning_options(section_id, overlay_id, animation->get_bolt_count(), animation->get_down_threshold(), animation->get_up_threshold(), animation->get_fork_chance());
			}
			break;
		case AnimationType::Plasma:
			{
				PlasmaAnimation* animation = static_cast<PlasmaAnimation*>(section->get_animation());
				animation_handler->set_plasma_options(section_id, overlay_id, animation->get_size(), animation->get_resolution());
			}
			break;
		case AnimationType::Radial:
			{
				RadialAnimation* animation = static_cast<RadialAnimation*>(section->get_animation());
				animation_handler->set_radial_options(section_id, overlay_id, animation->get_resolution());
			}
			break;
		case AnimationType::Sparkle:
			{
				SparkleAnimation* animation = static_cast<SparkleAnimation*>(section->get_animation());
				animation_handler->set_sparkle_options(section_id, overlay_id, animation->get_threshold());
			}
			break;
		default:
			break;
	}
	write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

	// Canvas
	Canvas* canvas = active_section_controller_->get_section()->get_canvas();
	if (canvas != nullptr) {
		section_handler->set_canvas(section_id, overlay_id, canvas->get_type(), canvas->get_num_frames());
		write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());

		// Draw and save each frame
		for (uint16_t frame = 0; frame < canvas->get_num_frames(); frame++) {
			switch (canvas->get_type()) {
				case CanvasType::AnimationCanvas:
					canvas_handler->draw_frame(section_id, overlay_id, section->get_dimensions()->size(), static_cast<AnimationCanvas*>(canvas)->get_frame(frame));
					break;
				case CanvasType::ColorCanvas:
					canvas_handler->draw_frame(section_id, overlay_id, section->get_dimensions()->size(), static_cast<ColorCanvas*>(canvas)->get_frame(frame));
					break;
			}
			write_cue_to_stream(datastream, cue_controller_->get_cue(), cue_controller_->get_cue_size());
		}
	}
}

/**
 * Changes the active SectionController and sets all GUI controls to the Section's settings.
 * @param controller New active controller
 */
void MaestroControl::set_active_section_controller(SectionController *controller) {
	if (controller == nullptr) {
		return;
	}

	active_section_controller_ = controller;

	// Set dimensions
	ui->columnsSpinBox->blockSignals(true);
	ui->rowsSpinBox->blockSignals(true);
	ui->columnsSpinBox->setValue(controller->get_section()->get_dimensions()->x);
	ui->rowsSpinBox->setValue(controller->get_section()->get_dimensions()->y);
	ui->columnsSpinBox->blockSignals(false);
	ui->rowsSpinBox->blockSignals(false);

	// Apply animation options and speed
	Animation* animation = controller->get_section()->get_animation();
	ui->orientationComboBox->setCurrentIndex(animation->get_orientation());
	ui->reverse_animationCheckBox->setChecked(animation->get_reverse());
	ui->fadeCheckBox->setChecked(animation->get_fade());
	ui->cycleSlider->setValue(controller->get_section()->get_animation()->get_speed());
	ui->pauseSlider->setValue(controller->get_section()->get_animation()->get_pause());

	/*
	 * Get the animation type.
	 * We don't want to fire the signal and re-apply the animation.
	 */
	ui->animationComboBox->blockSignals(true);
	ui->animationComboBox->setCurrentIndex(controller->get_section()->get_animation()->get_type());
	ui->animationComboBox->blockSignals(false);

	show_extra_controls(controller->get_section()->get_animation());

	// Get Overlay MixMode and alpha from the Overlay's parent section
	if (controller->get_parent_controller() != nullptr) {
		ui->mix_modeComboBox->setCurrentIndex(controller->get_parent_controller()->get_overlay()->mix_mode);
		ui->alphaSpinBox->setValue(controller->get_parent_controller()->get_overlay()->alpha);
	}

	if (controller->palette_ != nullptr) {
		ui->colorComboBox->setCurrentText(QString::fromStdString(controller->palette_->name));
	}

	// Get Canvas
	ui->canvasComboBox->blockSignals(true);
	if (controller->get_section()->get_canvas() != nullptr) {
		Canvas* canvas = controller->get_section()->get_canvas();
		ui->canvasComboBox->setCurrentIndex((int)canvas->get_type() + 1);
	}
	else {
		ui->canvasComboBox->setCurrentIndex(0);
	}
	show_canvas_controls();
	ui->canvasComboBox->blockSignals(false);
}

/// Sets the speed and/or pause interval for the active Animation.
void MaestroControl::set_speed() {
	uint16_t pause = ui->pauseSpinBox->value();
	uint16_t speed = ui->cycleSpinBox->value();
	Animation* animation = active_section_controller_->get_section()->get_animation();
	if (speed != animation->get_speed() || pause != animation->get_pause()) {
		animation->set_speed(speed, pause);

		if (cue_controller_ != nullptr) {
			animation_handler->set_speed(get_section_index(), get_overlay_index(), speed, pause);
			send_to_device();
		}
	}
}

/**
 * Sends the last action performed to the configured serial device.
 */
void MaestroControl::send_to_device() {
	if (cue_controller_ != nullptr) {
		serial_port_.write((const char*)cue_controller_->get_cue(), cue_controller_->get_cue_size());
	}
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

	if (active_section_controller_->get_section()->get_canvas() != nullptr) {
		canvas_control_widget_ = std::unique_ptr<QWidget>(new CanvasControl(this));
		layout->addWidget(canvas_control_widget_.get());
	}
}

/**
 * Appends a Cue to a stream.
 * @param stream Stream to append to.
 * @param cue Cue to append.
 * @param cue_size Size of Cue.
 */
void MaestroControl::write_cue_to_stream(QDataStream* stream, uint8_t* cue, uint8_t cue_size) {
	for (uint8_t i = 0; i < cue_size; i++) {
		stream->writeBytes((const char*)cue, cue_size);
	}
}

/**
 * Destructor.
 */
MaestroControl::~MaestroControl() {
	if (serial_port_.isOpen()) {
		serial_port_.close();
	}
	delete cue_interpreter_;
	delete show_controller_;
	delete ui;
}
