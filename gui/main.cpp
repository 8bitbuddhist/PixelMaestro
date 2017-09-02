#include "window/mainwindow.h"
#include <QApplication>
#include <QFormLayout>
#include <QVBoxLayout>

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	MainWindow w;

	// Set default window size
	w.resize(400, 500);

	// Add drawing area to form
	QVBoxLayout *main_layout = w.findChild<QVBoxLayout*>("mainLayout");
	Q_ASSERT(main_layout);

	// Enable high DPI output
	a.setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling, true);

	w.show();
	return a.exec();
}
