#include <QColorDialog>
#include "palettecontrol.h"
#include "ui_palettecontrol.h"

PaletteControl::PaletteControl(PaletteController* controller, QWidget *parent) : QDialog(parent), ui(new Ui::PaletteControl) {
	this->controller_ = controller;
	ui->setupUi(this);

	// Initialize palette list
	for (PaletteController::Palette palette : controller->get_palettes()) {
		ui->paletteComboBox->addItem(palette.name);
	}
}

/// Updates the target color.
void PaletteControl::on_color_clicked() {
	QPushButton* sender = (QPushButton*)QObject::sender();
	Colors::RGB* source_color = &active_palette_->palette.at(sender->objectName().toInt());
	QColor new_color = QColorDialog::getColor(QColor(source_color->r, source_color->g, source_color->b), this, "Select Color");
	source_color->r = new_color.red();
	source_color->g = new_color.green();
	source_color->b = new_color.blue();
	set_button_color(sender, source_color->r, source_color->g, source_color->b);
}

/**
 * Switches the current Palette.
 * @param index Index of the new Palette.
 */
void PaletteControl::on_paletteComboBox_currentIndexChanged(int index) {
	active_palette_ = controller_->get_palette(index);
	QLayout* layout = ui->colorsGroupBox->findChild<QLayout*>("colorsLayout");

	// Delete existing color buttons
	QList<QPushButton*> buttons = ui->colorsGroupBox->findChildren<QPushButton*>(QString(), Qt::FindChildOption::FindDirectChildrenOnly);
	for (QPushButton* button : buttons) {
		disconnect(button, &QPushButton::clicked, this, &PaletteControl::on_color_clicked);
		delete button;
	}

	// Create new buttons and add an event handler that triggers on_color_clicked().
	for (uint8_t color_index = 0; color_index < active_palette_->palette.size(); color_index++) {
		Colors::RGB color = active_palette_->palette.at(color_index);
		QPushButton* button = new QPushButton();
		button->setVisible(true);
		button->setObjectName(QString::number(color_index));
		set_button_color(button, color.r, color.g, color.b);
		layout->addWidget(button);
		connect(button, &QPushButton::clicked, this, &PaletteControl::on_color_clicked);
	}
}

/**
 * Changes the color of a button.
 * @param button Button to change.
 * @param red Red value.
 * @param green Green value.
 * @param blue Blue value.
 */
void PaletteControl::set_button_color(QPushButton *button, uint8_t red, uint8_t green, uint8_t blue) {
	button->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(red).arg(green).arg(blue));
}

PaletteControl::~PaletteControl() {
	delete ui;
}
