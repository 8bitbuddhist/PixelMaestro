#include "widget/maestrocontrol.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFormLayout>
#include <QVBoxLayout>

#include "demo/blinkdemo.h"
#include "demo/canvasdemo.h"
#include "demo/showdemo.h"
#include "drawingarea/canvasdrawingarea.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	MaestroController controller;

	// Set default window size
	w.resize(400, 400);

	// Add drawing area to form
	QVBoxLayout *main_layout = w.findChild<QVBoxLayout*>("mainLayout");
	Q_ASSERT(main_layout);

	BlinkDemo *drawing_area = new BlinkDemo(main_layout->widget(), &controller);
	// CanvasDemo *drawing_area = new CanvasDemo(main_layout->widget(), &controller);
	// ShowDemo *drawing_area = new ShowDemo(main_layout->widget(), &controller);

	//CanvasDrawingArea *drawing_area = new CanvasDrawingArea(main_layout->widget(), &controller);
	// Note: Be sure to include the following line when adding a CanvasDrawingArea
	//w.installEventFilter(drawing_area);

	main_layout->addWidget(drawing_area);

	// Uncomment the following line to add user controls
	main_layout->addWidget(new MaestroControl(main_layout->widget(), &controller));

	// Enable high DPI output
	a.setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling, true);

	w.show();
	return a.exec();
}
