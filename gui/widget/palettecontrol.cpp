#include <QAbstractButton>
#include <QColorDialog>
#include "palettecontrol.h"
#include "ui_palettecontrol.h"

PaletteControl::PaletteControl(PaletteController* controller, std::string initial_palette, QWidget *parent) : QDialog(parent), ui(new Ui::PaletteControl) {
	this->palette_controller_ = controller;
	ui->setupUi(this);

	// Initialize palette list
	for (PaletteController::Palette palette : controller->get_palettes()) {
		ui->paletteComboBox->addItem(QString::fromStdString(palette.name));
	}

	if (initial_palette.length() > 0) {
		ui->paletteComboBox->setCurrentText(QString::fromStdString(initial_palette));
	}

	// Initialize Palette creation types
	ui->typeComboBox->addItems({"Blank", "Scaling", "Random"});

	set_create_palette_controls_visible(false);
}

void PaletteControl::on_baseColorButton_clicked() {
	base_color_ = QColorDialog::getColor(Qt::white, this, "Select Base Color");
	set_button_color(ui->baseColorButton, base_color_.red(), base_color_.green(), base_color_.blue());
}

/// Updates the target color.
void PaletteControl::on_color_clicked() {
	QPushButton* sender = (QPushButton*)QObject::sender();
	Colors::RGB* source_color = &active_palette_->colors.at(sender->objectName().toInt());
	QColor new_color = QColorDialog::getColor(QColor(source_color->r, source_color->g, source_color->b), this, "Select Color");
	source_color->r = new_color.red();
	source_color->g = new_color.green();
	source_color->b = new_color.blue();
	set_button_color(sender, source_color->r, source_color->g, source_color->b);
}

/// Creates a new Palette.
void PaletteControl::on_createButtonBox_accepted() {
	uint8_t num_colors = ui->numColorsSpinBox->value();
	QString name = ui->nameLineEdit->text();

	// Only allow the Palette to be created if the name is set
	if (name.size()) {
		Colors::RGB colors[num_colors];

		// Handle generation method
		switch (ui->typeComboBox->currentIndex()) {
			case 0:	// Blank: Show all black
				{
					for (uint8_t i = 0; i < num_colors; i++) {
						colors[i] = Colors::BLACK;
					}
				}
				break;
			case 1: // Scaling
				{
					Colors::RGB base(base_color_.red(), base_color_.green(), base_color_.blue());
					Colors::RGB target(target_color_.red(), target_color_.green(), target_color_.blue());
					Colors::generate_scaling_color_array(colors, &base, &target, num_colors, ui->reverseCheckBox->isChecked());
				}
				break;
			case 2:	// Random
				{
					Colors::RGB color = Colors::generate_random_color();
					Colors::generate_random_color_array(colors, &color, num_colors);
				}
				break;
		}

		// Add the new Palette
		palette_controller_->add_palette(name.toStdString().c_str(), colors, num_colors);
		ui->paletteComboBox->addItem(name);
		ui->paletteComboBox->setCurrentText(name);

		set_create_palette_controls_visible(false);
	}
	else {
		// Highlight name label
		ui->nameLabel->setStyleSheet(QString("color: red;"));
	}
}

/// Cancels creating a new Palette.
void PaletteControl::on_createButtonBox_rejected() {
	set_create_palette_controls_visible(false);
}

/// Creates a new Palette.
void PaletteControl::on_createPaletteButton_clicked() {
	set_create_palette_controls_visible(true);
}

/**
 * Switches the current Palette.
 * @param index Index of the new Palette.
 */
void PaletteControl::on_paletteComboBox_currentIndexChanged(int index) {
	active_palette_ = palette_controller_->get_palette(index);

	// Delete existing color buttons
	QList<QPushButton*> buttons = ui->colorsGroupBox->findChildren<QPushButton*>(QString(), Qt::FindChildOption::FindDirectChildrenOnly);
	for (QPushButton* button : buttons) {
		disconnect(button, &QPushButton::clicked, this, &PaletteControl::on_color_clicked);
		delete button;
	}

	// Create new buttons and add an event handler that triggers on_color_clicked()
	QLayout* layout = ui->colorsGroupBox->findChild<QLayout*>("colorsLayout");
	for (uint8_t color_index = 0; color_index < active_palette_->colors.size(); color_index++) {
		Colors::RGB color = active_palette_->colors.at(color_index);
		QPushButton* button = new QPushButton();
		button->setVisible(true);
		button->setObjectName(QString::number(color_index));
		set_button_color(button, color.r, color.g, color.b);
		layout->addWidget(button);
		connect(button, &QPushButton::clicked, this, &PaletteControl::on_color_clicked);
	}
}

/// Deletes the current Palette.
void PaletteControl::on_removeButton_clicked() {
	uint16_t current_index = ui->paletteComboBox->currentIndex();
	palette_controller_->remove_palette(current_index);
	ui->paletteComboBox->removeItem(current_index);
}

/// Changes the target color.
void PaletteControl::on_targetColorButton_clicked() {
	target_color_ = QColorDialog::getColor(Qt::white, this, "Select Target Color");
	set_button_color(ui->targetColorButton, target_color_.red(), target_color_.green(), target_color_.blue());
}

/**
 * Changes the Palette generation method.
 * @param index Index of new method.
 */
void PaletteControl::on_typeComboBox_currentIndexChanged(int index) {
	ui->baseColorLabel->setVisible(false);
	ui->baseColorButton->setVisible(false);
	ui->targetColorLabel->setVisible(false);
	ui->targetColorButton->setVisible(false);
	ui->reverseCheckBox->setVisible(false);
	switch (index) {
		case 0:	// Blank
			break;
		case 1: // Scaling
			ui->baseColorLabel->setVisible(true);
			ui->baseColorButton->setVisible(true);
			ui->targetColorLabel->setVisible(true);
			ui->targetColorButton->setVisible(true);
			ui->reverseCheckBox->setVisible(true);
			break;
		case 2:	// Random
			ui->baseColorLabel->setVisible(true);
			ui->baseColorButton->setVisible(true);
			break;
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

/**
 * Sets the visibility of the Palette creation controls.
 * @param visible If true, show Palette controls.
 */
void PaletteControl::set_create_palette_controls_visible(bool visible) {
	ui->createPaletteButton->setVisible(!visible);
	ui->removeButton->setVisible(!visible);

	ui->nameLabel->setVisible(visible);
	ui->nameLineEdit->setVisible(visible);
	ui->numColorsLabel->setVisible(visible);
	ui->numColorsSpinBox->setVisible(visible);
	ui->typeLabel->setVisible(visible);
	ui->typeComboBox->setVisible(visible);

	if (!visible) {
		ui->baseColorLabel->setVisible(visible);
		ui->baseColorButton->setVisible(visible);

		ui->targetColorLabel->setVisible(visible);
		ui->targetColorButton->setVisible(visible);

		ui->reverseCheckBox->setVisible(visible);
	}

	ui->createButtonBox->setVisible(visible);
}

PaletteControl::~PaletteControl() {
	delete ui;
}
