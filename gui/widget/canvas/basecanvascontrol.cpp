#include "canvas/animationcanvas.h"
#include "basecanvascontrol.h"
#include "ui_basecanvascontrol.h"

BaseCanvasControl::BaseCanvasControl(Section* section, QWidget *parent) :
	QWidget(parent),
	ui(new Ui::BaseCanvasControl) {
	ui->setupUi(this);
	this->section_ = section;
	this->initialize();
}

void BaseCanvasControl::initialize() {
	ui->canvasEnableCheckBox->setChecked(true);

	// Add radio buttons to groups
	canvas_type_group_.addButton(ui->basicCanvasRadioButton);
	canvas_type_group_.addButton(ui->colorCanvasRadioButton);

	shape_type_group_.addButton(ui->circleRadioButton);
	shape_type_group_.addButton(ui->lineRadioButton);
	shape_type_group_.addButton(ui->rectRadioButton);
	shape_type_group_.addButton(ui->textRadioButton);
	shape_type_group_.addButton(ui->triangleRadioButton);

	set_circle_controls_visible(false);
	set_line_controls_visible(false);
	set_rect_controls_visible(false);
	set_text_controls_visible(false);
	set_triangle_controls_visible(false);
}

void BaseCanvasControl::set_circle_controls_visible(bool visible) {
	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	if (visible) {
		set_line_controls_visible(false);
		set_rect_controls_visible(false);
		set_text_controls_visible(false);
		set_triangle_controls_visible(false);
	}
}

void BaseCanvasControl::set_line_controls_visible(bool visible) {
	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	ui->targetLabel->setVisible(visible);
	ui->targetXSpinBox->setVisible(visible);
	ui->targetYSpinBox->setVisible(visible);

	if (visible) {
		set_circle_controls_visible(false);
		set_rect_controls_visible(false);
		set_text_controls_visible(false);
		set_triangle_controls_visible(false);
	}
}

void BaseCanvasControl::set_rect_controls_visible(bool visible) {
	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	if (visible) {
		ui->targetLabel->setText(QString("Size"));
		set_circle_controls_visible(false);
		set_line_controls_visible(false);
		set_text_controls_visible(false);
		set_triangle_controls_visible(false);
	}
	else {
		ui->targetLabel->setText(QString("Target"));
	}
	ui->targetLabel->setVisible(visible);
	ui->targetXSpinBox->setVisible(visible);
	ui->targetYSpinBox->setVisible(visible);
}

void BaseCanvasControl::set_text_controls_visible(bool visible) {
	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	ui->fontLabel->setVisible(visible);
	ui->fontComboBox->setVisible(visible);

	ui->textLabel->setVisible(visible);
	ui->textLineEdit->setVisible(visible);

	if (visible) {
		set_circle_controls_visible(false);
		set_line_controls_visible(false);
		set_rect_controls_visible(false);
		set_triangle_controls_visible(false);
	}
}

void BaseCanvasControl::set_triangle_controls_visible(bool visible) {
	ui->originLabel->setVisible(visible);
	ui->originXSpinBox->setVisible(visible);
	ui->originYSpinBox->setVisible(visible);

	ui->targetLabel->setVisible(visible);
	ui->targetXSpinBox->setVisible(visible);
	ui->targetYSpinBox->setVisible(visible);

	ui->target2Label->setVisible(true);
	ui->target2XSpinBox->setVisible(true);
	ui->target2YSpinBox->setVisible(true);

	if (visible) {
		ui->originLabel->setText(QString("Point A"));
		ui->targetLabel->setText(QString("Point B"));
		ui->target2Label->setText(QString("Point C"));

		set_circle_controls_visible(false);
		set_line_controls_visible(false);
		set_rect_controls_visible(false);
		set_text_controls_visible(false);
	}
	else {
		ui->originLabel->setText(QString("Origin"));
		ui->targetLabel->setText(QString("Target"));
		ui->target2Label->setText(QString("Target 2"));
	}
}

void BaseCanvasControl::on_basicCanvasRadioButton_toggled(bool checked) {
	delete canvas_;

	canvas_ = dynamic_cast<AnimationCanvas*>(new AnimationCanvas(section_));
}

void BaseCanvasControl::on_circleRadioButton_toggled(bool checked) {
	set_circle_controls_visible(true);
	set_line_controls_visible(false);
	set_rect_controls_visible(false);
}

BaseCanvasControl::~BaseCanvasControl() {
	delete ui;
}
