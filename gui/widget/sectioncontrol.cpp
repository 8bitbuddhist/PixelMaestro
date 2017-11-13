#include "sectioncontrol.h"
#include "ui_sectioncontrol.h"

SectionControl::SectionControl(MaestroController* maestro_controller, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SectionControl) {
	this->maestro_controller_ = maestro_controller;
	ui->setupUi(this);
	initialize();
}

void SectionControl::initialize() {
	ui->sectionsListWidget->blockSignals(true);
	ui->overlaysListWidget->blockSignals(true);

	// Add Maestro sections to widget
	for (int section = 1; section <= maestro_controller_->get_maestro()->get_num_sections(); section++) {
		ui->sectionsListWidget->addItem(QString("Section ") + QString::number(section));
	}

	ui->sectionsListWidget->blockSignals(false);
	ui->overlaysListWidget->blockSignals(false);
}

void SectionControl::on_addOverlayButton_clicked() {
	int index = 0;
	Section* section = maestro_controller_->get_maestro()->get_section(ui->sectionsListWidget->currentRow());

	while (section->get_overlay() != nullptr) {
		section = section->get_overlay()->section;
		index++;
	}

	section->set_overlay();
	ui->overlaysListWidget->addItem(QString("Overlay ") + QString::number(index + 1));
}

void SectionControl::on_addSectionButton_clicked() {
	maestro_controller_->add_section(Point(10, 10));
	populate_sections();
}

void SectionControl::on_removeOverlay_clicked() {
	int index = 0;
	Section* section = maestro_controller_->get_maestro()->get_section(ui->sectionsListWidget->currentRow());

	while (section->get_overlay() != nullptr) {
		section = section->get_overlay()->section;
		index++;
	}

	section->remove_overlay();
	populate_overlays();
}

void SectionControl::on_removeSectionButton_clicked() {
	maestro_controller_->remove_section(ui->sectionsListWidget->currentRow());
	populate_sections();
}

void SectionControl::on_sectionsListWidget_currentRowChanged(int currentRow) {
	populate_overlays();
}

void SectionControl::populate_overlays() {
	ui->overlaysListWidget->blockSignals(true);
	ui->overlaysListWidget->clear();
	Section* section = maestro_controller_->get_maestro()->get_section(ui->sectionsListWidget->currentRow());

	// Iterate through each Overlay and add it to the UI
	int index = 0;
	while (section->get_overlay() != nullptr) {
		section = section->get_overlay()->section;
		ui->overlaysListWidget->addItem(QString("Overlay ") + QString::number(index + 1));
		index++;
	}

	ui->overlaysListWidget->blockSignals(false);
}

void SectionControl::populate_sections() {
	ui->sectionsListWidget->blockSignals(true);
	ui->sectionsListWidget->clear();
	for (uint8_t section = 0; section < maestro_controller_->get_maestro()->get_num_sections(); section++) {
		ui->sectionsListWidget->addItem(QString("Section ") + QString::number(section + 1));
	}
	ui->sectionsListWidget->blockSignals(false);
}

SectionControl::~SectionControl() {
	delete ui;
}
