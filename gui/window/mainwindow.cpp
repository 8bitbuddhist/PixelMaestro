#include "animation/waveanimation.h"
#include "canvas/animationcanvas.h"
#include "colorpresets.h"
#include "demo/animatedcanvasdemo.h"
#include "demo/blinkdemo.h"
#include "demo/canvasdemo.h"
#include "demo/colorcanvasdemo.h"
#include "demo/cuedemo.h"
#include "demo/showdemo.h"
#include "drawingarea/canvasdrawingarea.h"
#include "widget/canvas/canvascontrol.h"
#include "mainwindow.h"
#include <memory>
#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QUrl>
#include "settingsdialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);
	this->main_layout_ = this->findChild<QLayout*>("mainLayout");
	setWindowTitle("PixelMaestro Studio");
	reset_drawing_area();
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_action_About_triggered() {
	QMessageBox::about(this, QString("PixelMaestro GUI"), QString("PixelMaestro v0.8\n\nPixelMaestro is a library for creating and rendering 2D animations and patterns.\n\n© 2017"));
}

void MainWindow::on_action_Exit_triggered() {
	close();
}

void MainWindow::on_action_Online_Help_triggered() {
	QDesktopServices::openUrl(QUrl("https://github.com/Anewman2/PixelMaestro/tree/master/docs", QUrl::TolerantMode));
}

void MainWindow::reset_drawing_area() {
	// Remove status bar label
	for (QLabel* label : statusBar()->findChildren<QLabel*>(QString(), Qt::FindDirectChildrenOnly)) {
		delete label;
	}

	main_layout_->removeWidget(drawing_area_);
	main_layout_->removeWidget(maestro_control_);
	removeEventFilter(drawing_area_);

	ui->action_Save_Maestro->setEnabled(false);

	ui->action_Animated_Canvas_Demo->setEnabled(true);
	ui->action_Blink_Demo->setEnabled(true);
	ui->action_Canvas_Demo->setEnabled(true);
	ui->action_Color_Canvas_Demo->setEnabled(true);
	ui->actionCommand_Demo->setEnabled(true);
	ui->action_Close_Workspace->setEnabled(false);
	ui->action_Open_Animation_Editor->setEnabled(true);
	ui->action_Show_Demo->setEnabled(true);
	ui->actionDrawing_Demo->setEnabled(true);

	if (drawing_area_) {
		delete drawing_area_;
		drawing_area_ = nullptr;
	}
	if (maestro_control_) {
		delete maestro_control_;
		maestro_control_ = nullptr;
	}
	if (controller_) {
		delete controller_;
		controller_ = nullptr;
	}

	controller_ = new MaestroController();
}

void MainWindow::on_action_Animated_Canvas_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new AnimatedCanvasDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);
	ui->action_Animated_Canvas_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->addWidget(new QLabel("Demonstrates using animated images in Canvases"));
}

void MainWindow::on_action_Blink_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new BlinkDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);
	ui->action_Blink_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->addWidget(new QLabel("Demonstrates a simple Blink animation"));
}

void MainWindow::on_action_Show_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new ShowDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);
	ui->action_Show_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->addWidget(new QLabel("Demonstrates using a Show to update a Maestro"));
}

void MainWindow::on_action_Canvas_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new CanvasDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);

	// Update UI
	ui->action_Canvas_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->addWidget(new QLabel("Demonstrates drawing shapes on a Canvas"));
}

void MainWindow::on_actionCommand_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new CueDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);

	// Update UI
	ui->actionCommand_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->addWidget(new QLabel("Demonstrates configuring a Maestro using Cues"));
}

void MainWindow::on_action_Open_Animation_Editor_triggered() {
	reset_drawing_area();

	maestro_control_ = new MaestroControl(main_layout_->widget(), controller_);
	drawing_area_ = new SimpleDrawingArea(main_layout_->widget(), controller_);

	main_layout_->addWidget(drawing_area_);
	main_layout_->addWidget(maestro_control_);

	ui->action_Open_Animation_Editor->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	ui->action_Save_Maestro->setEnabled(true);
}

void MainWindow::on_action_Close_Workspace_triggered() {
	reset_drawing_area();
}

void MainWindow::on_actionDrawing_Demo_triggered() {
	reset_drawing_area();

	// Initialize a new 50x50 drawing grid
	Section* section = controller_->set_sections(1, Point(50, 50));
	section->set_animation(AnimationType::Wave, ColorPresets::COLORWHEEL, 12);

	AnimationCanvas* canvas = static_cast<AnimationCanvas*>(section->set_canvas(CanvasType::Type::AnimationCanvas));

	drawing_area_ = new CanvasDrawingArea(main_layout_->widget(), controller_, canvas);
	installEventFilter(drawing_area_);
	main_layout_->addWidget(drawing_area_);
	ui->actionDrawing_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->addWidget(new QLabel("Demonstrates an interactive Canvas. Left-click = draw, right-click = erase, Delete =  clear"));
}

void MainWindow::on_action_Color_Canvas_Demo_triggered() {
	reset_drawing_area();

	drawing_area_ = new ColorCanvasDemo(main_layout_->widget(), controller_);
	main_layout_->addWidget(drawing_area_);

	// Update UI
	ui->action_Color_Canvas_Demo->setEnabled(false);
	ui->action_Close_Workspace->setEnabled(true);
	statusBar()->addWidget(new QLabel("Demonstrates drawing on a Color Canvas"));
}

void MainWindow::on_actionOpen_Maestro_triggered() {
	QString filename = QFileDialog::getOpenFileName(this,
		QString("Open PixelMaestro Cue File"),
		QDir::home().path(),
		QString("PixelMaestro Cue File (*.pmc)"));

	// Initialize the Animation editor and immediately read in the Cue file.
	on_action_Open_Animation_Editor_triggered();
	maestro_control_->read_from_file(filename);
}

void MainWindow::on_action_Preferences_triggered() {
	SettingsDialog settings;
	settings.exec();
}

void MainWindow::on_action_Save_Maestro_triggered() {
	QString filename = QFileDialog::getSaveFileName(this,
		QString("Save PixelMaestro Cue"),
		QDir::home().path(),
		QString("PixelMaestro Cue (*.pmc)"));

	maestro_control_->save_to_file(filename);
}
