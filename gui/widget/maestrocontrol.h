/*
 * MaestroControl - Widget for interacting with a MaestroController.
 */

#ifndef MAESTROCONTROL_H
#define MAESTROCONTROL_H

#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "core/colors.h"
#include "core/maestro.h"
#include "drawingarea/simpledrawingarea.h"
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
		/// Index of the actively controlled SectionController.
		SectionController *active_section_controller_;
		Ui::MaestroControl *ui;

		/// MaestroController that this widget is controlling.
		MaestroController* maestro_controller_;

		/// Stores any extra animation controllers
		std::unique_ptr<QWidget> extra_control_widget_;

		void change_scaling_color_array(Colors::RGB color);
		void get_section_settings();
		void initialize();
		void on_custom_color_changed();
		void on_ui_changed();
		void on_section_resize(unsigned short x, unsigned short y);
		void set_custom_color_controls_visible(bool visible);
		void show_extra_controls(int index, Animation* animation);
		void set_overlay_controls_visible(bool visible);

	private slots:
		void on_alphaSpinBox_valueChanged(int arg1);
		void on_animationComboBox_currentIndexChanged(int index);
		void on_blueSlider_valueChanged(int value);
		void on_colorComboBox_currentIndexChanged(int index);
		void on_columnsSpinBox_valueChanged(int arg1);
		void on_cycleSlider_valueChanged(int value);
		void on_greenSlider_valueChanged(int value);
		void on_fadeCheckBox_toggled(bool checked);
		void on_mix_modeComboBox_currentIndexChanged(int index);
		void on_num_colorsSpinBox_valueChanged(int arg1);
		void on_orientationComboBox_currentIndexChanged(int index);
		void on_reverse_animationCheckBox_toggled(bool checked);
		void on_redSlider_valueChanged(int value);
		void on_rowsSpinBox_valueChanged(int arg1);
		void on_sectionComboBox_currentIndexChanged(const QString &arg1);
		void on_thresholdSpinBox_valueChanged(int arg1);
};

#endif // MAESTROCONTROL_H
