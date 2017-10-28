#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../controller/maestrocontroller.h"
#include "../widget/maestrocontrol.h"
#include <QMainWindow>

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow {
	Q_OBJECT

	public:
		explicit MainWindow(QWidget* parent = 0);
		~MainWindow();

	private slots:
		void on_action_Online_Help_triggered();
		void on_action_Exit_triggered();
		void on_action_About_triggered();
		void on_action_Blink_Demo_triggered();
		void on_action_Show_Demo_triggered();
		void on_action_Canvas_Demo_triggered();
		void on_action_Open_Animation_Editor_triggered();
		void on_actionDrawing_Demo_triggered();
		void on_action_Close_Workspace_triggered();
		void on_action_Color_Canvas_Demo_triggered();
		void on_actionCommand_Demo_triggered();

		void on_action_Preferences_triggered();

		void on_action_Save_Maestro_triggered();

		void on_actionOpen_Maestro_triggered();

		void on_action_Animated_Canvas_Demo_triggered();

	private:
		MaestroController* controller_ = nullptr;
		QWidget* drawing_area_ = nullptr;
		MaestroControl* maestro_control_ = nullptr;
		QLayout* main_layout_ = nullptr;
		Ui::MainWindow* ui;

		void reset_drawing_area();
};

#endif // MAINWINDOW_H
