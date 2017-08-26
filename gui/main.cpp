#include "widget/maestrocontrol.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFormLayout>
#include <QVBoxLayout>

#include "demo/canvasdemo.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainWindow w;
	MaestroController controller;

	// Set default window size
	w.resize(400, 400);

	// Add drawing area to form
	QVBoxLayout *main_layout = w.findChild<QVBoxLayout*>("mainLayout");
	Q_ASSERT(main_layout);

	SimpleDrawingArea *drawing_area = new SimpleDrawingArea(main_layout->widget(), &controller);
	//CanvasDemo *drawing_area = new CanvasDemo(main_layout->widget(), &controller);
	main_layout->addWidget(drawing_area);
	main_layout->addWidget(new MaestroControl(main_layout->widget(), &controller));

	// Enable high DPI output
	a.setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling, true);

	w.show();
	return a.exec();
}
