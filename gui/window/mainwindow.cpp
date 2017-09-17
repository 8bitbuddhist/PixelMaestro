#include "../demo/blinkdemo.h"
#include "../demo/canvasdemo.h"
#include "../demo/showdemo.h"
#include "../drawingarea/canvasdrawingarea.h"
#include "mainwindow.h"
#include "QDesktopServices"
#include "QMessageBox"
#include "QUrl"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->main_layout_ = this->findChild<QLayout*>("mainLayout");
	reset_drawing_area();
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_action_About_triggered() {
	QMessageBox::about(this, QString("PixelMaestro GUI"), QString("PixelMaestro v0.5\n\nPixelMaestro is a library for creating and rendering 2D animations and patterns.\n\n© 2017"));
}

void MainWindow::on_action_Exit_triggered() {
	close();
}

void MainWindow::on_action_Online_Help_triggered() {
	QDesktopServices::openUrl(QUrl("https://github.com/Anewman2/PixelMaestro/tree/master/docs", QUrl::TolerantMode));
}

void MainWindow::reset_drawing_area() {
	main_layout_->removeWidget(drawing_area_);
	main_layout_->removeWidget(maestro_control_);
	removeEventFilter(drawing_area_);

	ui->action_Blink_Demo->setEnabled(true);
	ui->action_Canvas_Demo->setEnabled(true);
	ui->action_Close_Workspace->setEnabled(false);
	ui->action_Open_Animation_Editor->setEnabled(true);
	ui->action_Show_Demo->setEnabled(true);
	ui->actionDrawing_Demo->setEnabled(true);

	if (maestro_control_) {
		delete maestro_control_;
		maestro_control_ = nullptr;
	}
	if (drawing_area_) {
		delete drawing_area_;
		drawing_area_ = nullptr;
	}
	if (controller_) {
		delete controller_;
		controller_ = nullptr;
	}

	controller_ = new MaestroController();
}

void MainWindow::on_action_Blink_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new BlinkDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);
	ui->action_Blink_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->showMessage(QString("Demonstrates the Blink animation."));
}

void MainWindow::on_action_Show_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new ShowDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);
	ui->action_Show_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->showMessage(QString("Demonstrates using Shows to change animations."));
}

void MainWindow::on_action_Canvas_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new CanvasDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);
	ui->action_Canvas_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->showMessage(QString("Demonstrates the shapes you can draw on a Canvas."));
}

void MainWindow::on_action_Open_Animation_Editor_triggered() {
	reset_drawing_area();

	controller_->add_section_controller(new Point(10, 10));
	maestro_control_ = new MaestroControl(main_layout_->widget(), controller_);

	drawing_area_ = new SimpleDrawingArea(main_layout_->widget(), controller_);

	main_layout_->addWidget(drawing_area_);
	main_layout_->addWidget(maestro_control_);

	ui->action_Open_Animation_Editor->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);

	statusBar()->showMessage(QString("Use the controls to modify the Section."));
}

void MainWindow::on_action_Close_Workspace_triggered() {
	reset_drawing_area();
}

void MainWindow::on_actionDrawing_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new CanvasDrawingArea(main_layout_->widget(), controller_);
	installEventFilter(drawing_area_);
	main_layout_->addWidget(drawing_area_);
	ui->actionDrawing_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->showMessage(QString("Left-click to draw, right-click to erase, Delete to clear."));
}
