#include "canvas/animationcanvas.h"
#include "canvas/colorcanvas.h"
#include "canvas/fonts/font5x8.h"
#include "canvascontrol.h"
#include "ui_canvascontrol.h"
#include "utility/canvasutility.h"
#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QImageReader>
#include <QMessageBox>

CanvasControl::CanvasControl(MaestroControl* maestro_control, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::CanvasControl) {
	ui->setupUi(this);
	this->canvas_ = maestro_control->active_section_->get_canvas();
	this->maestro_control_ = maestro_control;
	this->initialize();
}

bool CanvasControl::confirm_clear() {
	QMessageBox::StandardButton confirm;
	confirm = QMessageBox::question(this, "Clear Canvas", "This action will clear the Canvas. Are you sure you want to continue?", QMessageBox::Yes|QMessageBox::No);
	if (confirm == QMessageBox::Yes) {
		canvas_->clear();
		if (maestro_control_ && maestro_control_->cue_controller_) {
			maestro_control_->send_to_device(maestro_control_->canvas_handler->clear(maestro_control_->get_section_index(), maestro_control_->get_overlay_index()));
		}

		return true;
	}

	return false;
}

void CanvasControl::initialize() {
	// Add radio buttons to groups
	shape_type_group_.addButton(ui->circleRadioButton);
	shape_type_group_.addButton(ui->lineRadioButton);
	shape_type_group_.addButton(ui->rectRadioButton);
	shape_type_group_.addButton(ui->textRadioButton);
	shape_type_group_.addButton(ui->triangleRadioButton);

	set_line_controls_visible(false);
	set_rect_controls_visible(false);
	set_text_controls_visible(false);
	set_triangle_controls_visible(false);

	ui->circleRadioButton->setChecked(true);
	set_circle_controls_visible(true);

	// Add fonts
	ui->fontComboBox->addItems({"5x8"});

	// Set color Canvas buttons
	switch (canvas_->get_type()) {
		case CanvasType::ColorCanvas:
			ui->colorLabel->setVisible(true);
			ui->selectColorButton->setVisible(true);
			break;
		default:
			ui->colorLabel->setVisible(false);
			ui->selectColorButton->setVisible(false);
	}
}

void CanvasControl::set_circle_controls_visible(bool visible) {
	if (visible) {
		set_line_controls_visible(false);
		set_rect_controls_visible(false);
		set_text_controls_visible(false);
		set_triangle_controls_visible(false);

		ui->targetLabel->setText("Radius");
		ui->targetLabel->setVisible(true);
		ui->targetXSpinBox->setVisible(true);
	}
	else {
		ui->targetLabel->setText("Target");
	}

	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);
	ui->fillCheckBox->setVisible(visible);
}

void CanvasControl::set_line_controls_visible(bool visible) {
	if (visible) {
		set_circle_controls_visible(false);
		set_rect_controls_visible(false);
		set_text_controls_visible(false);
		set_triangle_controls_visible(false);
	}

	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	ui->targetLabel->setVisible(visible);
	ui->targetXSpinBox->setVisible(visible);
	ui->targetYSpinBox->setVisible(visible);

	ui->fillCheckBox->setVisible(visible);
}

void CanvasControl::set_rect_controls_visible(bool visible) {
	if (visible) {
		set_circle_controls_visible(false);
		set_line_controls_visible(false);
		set_text_controls_visible(false);
		set_triangle_controls_visible(false);
		ui->targetLabel->setText(QString("Size"));
	}
	else {
		ui->targetLabel->setText(QString("Target"));
	}

	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	ui->targetLabel->setVisible(visible);
	ui->targetXSpinBox->setVisible(visible);
	ui->targetYSpinBox->setVisible(visible);

	ui->fillCheckBox->setVisible(visible);
}

void CanvasControl::set_text_controls_visible(bool visible) {
	if (visible) {
		set_circle_controls_visible(false);
		set_line_controls_visible(false);
		set_rect_controls_visible(false);
		set_triangle_controls_visible(false);
		ui->fillCheckBox->setVisible(false);
	}

	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	ui->fontLabel->setVisible(visible);
	ui->fontComboBox->setVisible(visible);

	ui->textLabel->setVisible(visible);
	ui->textLineEdit->setVisible(visible);
}

void CanvasControl::set_triangle_controls_visible(bool visible) {
	if (visible) {
		set_circle_controls_visible(false);
		set_line_controls_visible(false);
		set_rect_controls_visible(false);
		set_text_controls_visible(false);

		ui->originLabel->setText(QString("Point A"));
		ui->targetLabel->setText(QString("Point B"));
		ui->target2Label->setText(QString("Point C"));
	}
	else {
		ui->originLabel->setText(QString("Origin"));
		ui->targetLabel->setText(QString("Target"));
		ui->target2Label->setText(QString("Target 2"));
	}

	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	ui->targetLabel->setVisible(visible);
	ui->targetXSpinBox->setVisible(visible);
	ui->targetYSpinBox->setVisible(visible);

	ui->target2Label->setVisible(visible);
	ui->target2XSpinBox->setVisible(visible);
	ui->target2YSpinBox->setVisible(visible);

	ui->fillCheckBox->setVisible(visible);
}

void CanvasControl::on_circleRadioButton_toggled(bool checked) {
	set_circle_controls_visible(checked);
}

void CanvasControl::on_drawButton_clicked() {
	QAbstractButton* checked_button = this->shape_type_group_.checkedButton();

	if (canvas_->get_type() == CanvasType::ColorCanvas) {
		ColorCanvas* canvas = static_cast<ColorCanvas*>(canvas_);
		if (checked_button == ui->circleRadioButton) {
			canvas->draw_circle(rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->fillCheckBox->isChecked());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_circle(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->fillCheckBox->isChecked());
		}
		else if (checked_button == ui->lineRadioButton) {
			canvas->draw_line(rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_line(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value());
		}
		else if (checked_button == ui->rectRadioButton) {
			canvas->draw_rect(rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value(), ui->fillCheckBox->isChecked());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_rect(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value(), ui->fillCheckBox->isChecked());
		}
		else if (checked_button == ui->textRadioButton) {
			// Reinitialize the font
			delete font_;
			switch ((Font::Type)ui->fontComboBox->currentIndex()) {
				case Font::Font5x8:
				default:
					font_ = new Font5x8();
					break;
			}
			canvas->draw_text(rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), font_, ui->textLineEdit->text().toLatin1().data(), ui->textLineEdit->text().size());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_text(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), (Font::Type)ui->fontComboBox->currentIndex(), ui->textLineEdit->text().toLatin1().data(), ui->textLineEdit->text().size());
		}
		else {	// Triangle
			canvas->draw_triangle(rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value(), ui->target2XSpinBox->value(), ui->target2YSpinBox->value(), ui->fillCheckBox->isChecked());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_triangle(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), rgb_color_, ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value(), ui->target2XSpinBox->value(), ui->target2YSpinBox->value(), ui->fillCheckBox->isChecked());
		}
	}
	else {
		if (checked_button == ui->circleRadioButton) {
			canvas_->draw_circle(ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->fillCheckBox->isChecked());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_circle(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->fillCheckBox->isChecked());
		}
		else if (checked_button == ui->lineRadioButton) {
			canvas_->draw_line(ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_line(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value());
		}
		else if (checked_button == ui->rectRadioButton) {
			canvas_->draw_rect(ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value(), ui->fillCheckBox->isChecked());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_rect(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value(), ui->fillCheckBox->isChecked());
		}
		else if (checked_button == ui->textRadioButton) {
			// Reinitialize the font
			delete font_;
			switch ((Font::Type)ui->fontComboBox->currentIndex()) {
				case Font::Font5x8:
				default:
					font_ = new Font5x8();
					break;
			}

			canvas_->draw_text(ui->originXSpinBox->value(), ui->originYSpinBox->value(), font_, ui->textLineEdit->text().toLatin1().data(), ui->textLineEdit->text().size());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_text(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), ui->originXSpinBox->value(), ui->originYSpinBox->value(), (Font::Type)ui->fontComboBox->currentIndex(), ui->textLineEdit->text().toLatin1().data(), ui->textLineEdit->text().size());
		}
		else {	// Triangle
			canvas_->draw_triangle(ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value(), ui->target2XSpinBox->value(), ui->target2YSpinBox->value(), ui->fillCheckBox->isChecked());
			if (maestro_control_ && maestro_control_->cue_controller_)
				maestro_control_->canvas_handler->draw_triangle(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), ui->originXSpinBox->value(), ui->originYSpinBox->value(), ui->targetXSpinBox->value(), ui->targetYSpinBox->value(), ui->target2XSpinBox->value(), ui->target2YSpinBox->value(), ui->fillCheckBox->isChecked());
		}
	}

	maestro_control_->send_to_device();
}

void CanvasControl::on_eraseButton_clicked() {
	confirm_clear();
}

void CanvasControl::on_lineRadioButton_toggled(bool checked) {
	set_line_controls_visible(checked);
}

void CanvasControl::on_openImageButton_clicked() {
	QString filename = QFileDialog::getOpenFileName(this,
		QString("Open Image"),
		QDir::home().path(),
		QString("Images (*.bmp *.gif *.jpg *.png)"));

	CanvasUtility::load_image(filename, canvas_, maestro_control_);
}

void CanvasControl::on_rectRadioButton_toggled(bool checked) {
	set_rect_controls_visible(checked);
}

void CanvasControl::on_selectColorButton_clicked() {
	QColor new_color = QColorDialog::getColor(qcolor_, parentWidget());

	if (new_color != qcolor_) {
		qcolor_ = new_color;
	}

	ui->selectColorButton->setStyleSheet("background-color: " + qcolor_.name());

	rgb_color_.r = qcolor_.red();
	rgb_color_.g = qcolor_.green();
	rgb_color_.b = qcolor_.blue();
}

void CanvasControl::on_textRadioButton_toggled(bool checked) {
	set_text_controls_visible(checked);
}

void CanvasControl::on_triangleRadioButton_toggled(bool checked) {
	set_triangle_controls_visible(checked);
}

CanvasControl::~CanvasControl() {
	delete ui;
	delete font_;
}
