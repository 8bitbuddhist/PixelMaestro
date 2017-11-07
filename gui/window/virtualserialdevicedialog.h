/*
 * VirtualSerialDeviceDialog - Manages a separate Maestro for testing serial output/Cue commands.
 */

#ifndef VIRTUALSERIALDEVICEDIALOG_H
#define VIRTUALSERIALDEVICEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <memory>
#include "controller/maestrocontroller.h"
#include "controller/cueinterpreter.h"
#include "drawingarea/simpledrawingarea.h"

using namespace PixelMaestro;

namespace Ui {
	class VirtualSerialDeviceDialog;
}

class VirtualSerialDeviceDialog : public QDialog {
		Q_OBJECT

	public:
		QLabel* interpreted = nullptr;

		explicit VirtualSerialDeviceDialog(QWidget *parent = 0);
		~VirtualSerialDeviceDialog();
		void display_cue(uint8_t* cue);
		Maestro* get_maestro();

	private:
		Ui::VirtualSerialDeviceDialog *ui;
		std::unique_ptr<CueInterpreter> cue_interpreter_;
		std::unique_ptr<MaestroController> maestro_controller_;
		std::unique_ptr<SimpleDrawingArea> drawing_area_;
};

#endif // VIRTUALSERIALDEVICEDIALOG_H
