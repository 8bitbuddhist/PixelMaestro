/*
 * SectionControl - Dialog for modifying Sections and Overlays in a Maestro.
 */

#ifndef SECTIONCONTROL_H
#define SECTIONCONTROL_H

#include <QDialog>
#include "controller/maestrocontroller.h"

namespace Ui {
	class SectionControl;
}

class SectionControl : public QDialog {
		Q_OBJECT

	public:
		explicit SectionControl(MaestroController* maestro_controller, QWidget *parent = 0);
		~SectionControl();

	private slots:
		void on_sectionsListWidget_currentRowChanged(int currentRow);

		void on_addSectionButton_clicked();

		void on_removeSectionButton_clicked();

		void on_addOverlayButton_clicked();

		void on_removeOverlay_clicked();

	private:
		MaestroController* maestro_controller_ = nullptr;
		Ui::SectionControl *ui;

		void initialize();
		void populate_overlays();
		void populate_sections();
};

#endif // SECTIONCONTROL_H
