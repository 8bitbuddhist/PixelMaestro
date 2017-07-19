#include "widget/maestrocontrol.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFormLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;

	// Set a starting window size
	w.resize(410, 800);

	// Add drawing area to form
	QVBoxLayout *mainLayout = w.findChild<QVBoxLayout*>("mainLayout");
	Q_ASSERT(mainLayout);

	MaestroController controller;

	SimpleDrawingArea *drawingArea = new SimpleDrawingArea(mainLayout->widget(), &controller);
	mainLayout->addWidget(drawingArea);
	mainLayout->addWidget(new MaestroControl(mainLayout->widget(), &controller));

	// Enable high DPI output
	a.setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling, true);

	w.show();
	return a.exec();
}
