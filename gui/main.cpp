#include "demo/blinkdemo.h"
#include "widget/maestrocontrol.h"
#include "mainwindow.h"
#include <QApplication>
#include <QFormLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	MainWindow w;

	// Set a basic window size
	w.resize(410, 800);

	// Add drawing area to form
	QVBoxLayout *mainLayout = w.findChild<QVBoxLayout*>("mainLayout");
	Q_ASSERT(mainLayout);
	BlinkDemo *demo = new BlinkDemo(mainLayout->widget());
	mainLayout->addWidget(demo);

	// Add control area to form
	mainLayout->addWidget(new MaestroControl(mainLayout->widget(), demo));

	// Enable high DPI output
	a.setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling, true);

	w.show();
	return a.exec();
}
