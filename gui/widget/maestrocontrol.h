/*
 * MaestroControl - Widget for interacting with a MaestroController.
 */

#ifndef MAESTROCONTROL_H
#define MAESTROCONTROL_H

#include <memory>
#include <QSerialPort>
#include <QTextStream>
#include <QWidget>
#include "controller/canvascontroller.h"
#include "controller/cueinterpreter.h"
#include "controller/maestrocontroller.h"
#include "controller/palettecontroller.h"
#include "controller/sectioncontroller.h"
#include "controller/showcontroller.h"
#include "core/colors.h"
#include "core/maestro.h"
#include "cue/animationcuehandler.h"
#include "cue/canvascuehandler.h"
#include "cue/maestrocuehandler.h"
#include "cue/sectioncuehandler.h"
#include "widget/showcontrol.h"

namespace Ui {
	class MaestroControl;
}

using namespace PixelMaestro;

class CanvasController;

class MaestroController;

class SectionController;

class ShowControl;

class ShowController;

class MaestroControl : public QWidget {
	Q_OBJECT

	public:
		/// The actively controlled SectionController.
		SectionController *active_section_controller_ = nullptr;

		/// The controller for managing Palettes.
		PaletteController palette_controller_;

		// Cue components
		CueInterpreter* cue_interpreter_ = nullptr;
		CueController* cue_controller_ = nullptr;
		AnimationCueHandler* animation_handler = nullptr;
		CanvasCueHandler* canvas_handler = nullptr;
		MaestroCueHandler* maestro_handler = nullptr;
		SectionCueHandler* section_handler = nullptr;

		/// Connection to an Arduino or other device.
		QSerialPort serial_port_;

		/// If true, only generate Cues instead of modifying the Maestro.
		bool show_mode_ = false;

		explicit MaestroControl(QWidget* parent, MaestroController* maestro_controller);
		~MaestroControl();
		int16_t get_overlay_index();
		int16_t get_section_index();
		void read_from_file(QString filename);
		void save_to_file(QString filename);
		void send_to_device();

	private:
		Ui::MaestroControl *ui;

		/// MaestroController that this widget is controlling.
		MaestroController* maestro_controller_ = nullptr;

		/// Stores extra animation controls
		std::unique_ptr<QWidget> extra_control_widget_;

		/// Stores Canvas controls
		std::unique_ptr<QWidget> canvas_control_widget_;

		/// Dialog for modifying Shows.
		std::unique_ptr<ShowControl> show_control_dialog_;

		/// Controller for managing Shows.
		std::unique_ptr<ShowController> show_controller_;

		void get_section_settings();
		void initialize();
		void initialize_cue_controller();
		void initialize_palettes();
		void on_ui_changed();
		void on_section_resize(uint16_t x, uint16_t y);
		void set_overlay_controls_visible(bool visible);
		void set_speed();
		void show_extra_controls(Animation* animation);
		void show_canvas_controls();
		void write_cue_to_stream(QTextStream* stream, uint8_t* cue, uint8_t cue_size);

	private slots:
		void on_alphaSpinBox_valueChanged(int arg1);
		void on_animationComboBox_currentIndexChanged(int index);
		void on_canvasComboBox_currentIndexChanged(int index);
		void on_colorComboBox_currentIndexChanged(int index);
		void on_columnsSpinBox_editingFinished();
		void on_cycleSlider_valueChanged(int value);
		void on_fadeCheckBox_toggled(bool checked);
		void on_mix_modeComboBox_currentIndexChanged(int index);
		void on_orientationComboBox_currentIndexChanged(int index);
		void on_paletteControlButton_clicked();
		void on_reverse_animationCheckBox_toggled(bool checked);
		void on_rowsSpinBox_editingFinished();
		void on_sectionComboBox_currentIndexChanged(const QString &arg1);
		void on_cycleSpinBox_editingFinished();
		void on_enableShowCheckBox_toggled(bool checked);
		void on_editEventsButton_clicked();
		void on_pauseSlider_valueChanged(int value);
		void on_pauseSpinBox_valueChanged(int arg1);
};

#endif // MAESTROCONTROL_H
