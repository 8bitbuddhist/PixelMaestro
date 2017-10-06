#include "window/mainwindow.h"
#include <QApplication>
#include <QFormLayout>
#include <QVBoxLayout>

int main(int argc, char* argv[]) {
	// Set application parameters for QSettings
	QCoreApplication::setOrganizationName("pixelmaestro");
	QCoreApplication::setApplicationName("pixelmaestro");

	QApplication a(argc, argv);
	MainWindow w;

	// Set default window size
	w.setWindowState(Qt::WindowState::WindowMaximized);

	// Add drawing area to form
	QVBoxLayout *main_layout = w.findChild<QVBoxLayout*>("mainLayout");
	Q_ASSERT(main_layout);

	// Enable high DPI output
	a.setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling, true);

	w.show();
	return a.exec();
}
