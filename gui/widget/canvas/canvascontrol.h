#ifndef CANVASCONTROL_H
#define CANVASCONTROL_H

#include "canvas/canvas.h"
#include <QButtonGroup>
#include <QWidget>

using namespace PixelMaestro;

namespace Ui {
	class CanvasControl;
}

class CanvasControl : public QWidget {
		Q_OBJECT

	public:
		explicit CanvasControl(Canvas* canvas, QWidget *parent = 0);
		~CanvasControl();
		bool confirm_clear();

	private slots:
		void on_circleRadioButton_toggled(bool checked);

		void on_lineRadioButton_toggled(bool checked);

		void on_rectRadioButton_toggled(bool checked);

		void on_textRadioButton_toggled(bool checked);

		void on_triangleRadioButton_toggled(bool checked);

		void on_drawButton_clicked();

		void on_eraseButton_clicked();

	private:
		Canvas* canvas_ = nullptr;
		Font* font_ = nullptr;
		Ui::CanvasControl *ui;

		QButtonGroup shape_type_group_;

		void initialize();
		void set_circle_controls_visible(bool visible);
		void set_line_controls_visible(bool visible);
		void set_rect_controls_visible(bool visible);
		void set_text_controls_visible(bool visible);
		void set_triangle_controls_visible(bool visible);
};

#endif // CANVASCONTROL_H
