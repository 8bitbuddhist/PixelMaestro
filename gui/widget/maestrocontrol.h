/*
 * MaestroControl - Widget for interacting with a MaestroController.
 */

#ifndef MAESTROCONTROL_H
#define MAESTROCONTROL_H

#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "core/colors.h"
#include "core/maestro.h"
#include "cue/animationcuehandler.h"
#include "cue/canvascuehandler.h"
#include "cue/maestrocuehandler.h"
#include "cue/sectioncuehandler.h"
#include "drawingarea/simpledrawingarea.h"
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <fstream>
#include <QWidget>

namespace Ui {
	class MaestroControl;
}

using namespace PixelMaestro;

class MaestroControl : public QWidget {
	Q_OBJECT

	public:
		explicit MaestroControl(QWidget* parent, MaestroController* maestro_controller);
		~MaestroControl();

	private:
		Ui::MaestroControl *ui;

		/// Stores the actively controlled SectionController.
		SectionController *active_section_controller_ = nullptr;

		/// MaestroController that this widget is controlling.
		MaestroController* maestro_controller_ = nullptr;

		/// Stores extra animation controls
		std::unique_ptr<QWidget> extra_control_widget_;

		/// Stores Canvas controls
		std::unique_ptr<QWidget> canvas_control_widget_;

		// Load Serial connection to Arduino.
		bool serial_enabled_ = false;
		const char* port_num_ = "/dev/ttyACM0";
		boost::asio::io_service io_service_;
		boost::asio::serial_port serial_port_;

		// Initialize CueController
		CueController* controller_;
		AnimationCueHandler* animation_handler;
		CanvasCueHandler* canvas_handler;
		MaestroCueHandler* maestro_handler;
		SectionCueHandler* section_handler;

		/// True if UI is done loading. This prevents some (i.e. serial-related) events from firing before the UI is done loading.
		bool ui_initialized_ = false;

		void change_scaling_color_array(Colors::RGB color);
		void get_section_settings();
		void initialize();
		void on_custom_color_changed();
		void on_ui_changed();
		void on_section_resize(uint16_t x, uint16_t y);
		void send_to_device(uint8_t* out, uint8_t size);
		void set_custom_color_controls_visible(bool visible);
		void show_extra_controls(Animation* animation);
		void show_canvas_controls(Canvas* canvas);
		void set_overlay_controls_visible(bool visible);

	private slots:
		void on_alphaSpinBox_valueChanged(int arg1);
		void on_animationComboBox_currentIndexChanged(int index);
		void on_blueSlider_valueChanged(int value);
		void on_canvasComboBox_currentIndexChanged(int index);
		void on_colorComboBox_currentIndexChanged(int index);
		void on_columnsSpinBox_editingFinished();
		void on_cycleSlider_valueChanged(int value);
		void on_greenSlider_valueChanged(int value);
		void on_fadeCheckBox_toggled(bool checked);
		void on_mix_modeComboBox_currentIndexChanged(int index);
		void on_num_colorsSpinBox_valueChanged(int arg1);
		void on_orientationComboBox_currentIndexChanged(int index);
		void on_reverse_animationCheckBox_toggled(bool checked);
		void on_redSlider_valueChanged(int value);
		void on_rowsSpinBox_editingFinished();
		void on_sectionComboBox_currentIndexChanged(const QString &arg1);
		void on_thresholdSpinBox_valueChanged(int arg1);
};

#endif // MAESTROCONTROL_H
