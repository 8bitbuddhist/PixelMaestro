#ifndef BASECANVASCONTROL_H
#define BASECANVASCONTROL_H

#include "core/section.h"
#include <QButtonGroup>
#include <QWidget>

using namespace PixelMaestro;

namespace Ui {
	class BaseCanvasControl;
}

class BaseCanvasControl : public QWidget {
		Q_OBJECT

	public:
		explicit BaseCanvasControl(Section* section, QWidget *parent = 0);
		~BaseCanvasControl();

	private slots:
		void on_basicCanvasRadioButton_toggled(bool checked);

		void on_circleRadioButton_toggled(bool checked);

	private:
		Section* section_;
		Canvas* canvas_;
		Ui::BaseCanvasControl *ui;

		// Radio button groups
		QButtonGroup canvas_type_group_;
		QButtonGroup shape_type_group_;

		void initialize();
		void set_circle_controls_visible(bool visible);
		void set_line_controls_visible(bool visible);
		void set_rect_controls_visible(bool visible);
		void set_text_controls_visible(bool visible);
		void set_triangle_controls_visible(bool visible);
};

#endif // BASECANVASCONTROL_H
