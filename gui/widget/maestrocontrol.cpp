#include "maestrocontrol.h"
#include "ui_maestrocontrol.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "drawingarea/simpledrawingarea.h"
#include <QPalette>
#include <QString>
#include "section.h"

/**
 * Constructor.
 * @param parent The QWidget containing this controller.
 * @param maestroController The MaestroController being controlled.
 */
MaestroControl::MaestroControl(QWidget *parent, MaestroController *maestroController) : QWidget(parent), ui(new Ui::MaestroControl) {

	// Assign easy reference variables for the Maestro
	this->maestro_controller_ = maestroController;

	// Initialize UI
	ui->setupUi(this);
	this->initialize();
}

/**
 * Build the initial UI.
 */
void MaestroControl::initialize() {
	// Add a new SectionController to the MaestroController. Later on this will allow us to add multiple Sections to a MaestroController.
	this->maestro_controller_->addSectionController(new Point(10, 10));
	this->active_section_controller_ = this->maestro_controller_->getSectionController(0);

	// Populate Animation combo box
	ui->animationComboBox->addItems({"Solid", "Blink", "Wave", "Pong", "Merge", "RandomIndex", "Sparkle", "Pattern", "Cycle"});

	// Populate color combo box
	ui->colorComboBox->addItems({"Custom", "Fire", "Deep Sea", "Color Wheel"});
	ui->colorComboBox->setCurrentIndex(2);
	this->setCustomColorControlsVisible(false);

	// Set default values
	ui->animationComboBox->setCurrentIndex(2);
	ui->cycleSlider->setValue(this->active_section_controller_->getSection()->getCycleSpeed());
	ui->rowsSpinBox->setValue(this->active_section_controller_->getSection()->getLayout()->y);
	ui->columnsSpinBox->setValue(this->active_section_controller_->getSection()->getLayout()->x);
	ui->sectionComboBox->addItem("Section 1");

	// Overlay controls
	ui->mixModeComboBox->addItems({"None", "Normal", "Alpha Blending", "Multiply"});
	ui->mixModeComboBox->setCurrentIndex(2);
}

/**
 * Updates the color array based on changes to the color scheme and settings.
 * @param color Base color to use when generating the array.
 */
void MaestroControl::changeScalingColorArray(Colors::RGB color) {
	unsigned int numColors = (unsigned int)ui->numColorsSpinBox->value();

	std::vector<Colors::RGB> tmpColors;
	tmpColors.resize(numColors);

	unsigned char threshold = 255 - (unsigned char)ui->thresholdSpinBox->value();
	Colors::generateScalingColorArray(&tmpColors[0], &color, numColors, threshold, true);
	this->active_section_controller_->setControllerColors(&tmpColors[0], numColors);

	// Release tmpColors
	std::vector<Colors::RGB>().swap(tmpColors);
}

/**
 * Returns the active SectionController being modified.
 * @return Active SectionController.
 */
SectionController *MaestroControl::getActiveSectionController() {
	return this->active_section_controller_;
}

void MaestroControl::setOverlayControlsVisible(bool visible) {
	// If visible, show Overlay controls
	ui->mixModeComboBox->setVisible(visible);
	ui->alphaSpinBox->setVisible(visible);

	// Invert Layout controls
	ui->gridSizeLabel->setVisible(!visible);
	ui->columnsSpinBox->setVisible(!visible);
	ui->rowsSpinBox->setVisible(!visible);
}

void MaestroControl::on_addOverlayButton_clicked() {
	// Get info about the current Section
	QStringList args = ui->sectionComboBox->currentText().split(" ");
	int num = args[1].toInt();
	int index = num - 1;

	// Check to see if an Overlay has already been added
	if(this->maestro_controller_->getSectionController(index)->getOverlayController()) {
		// Has an Overlay: let's remove it
		this->maestro_controller_->getSectionController(index)->unsetOverlay();
		ui->addOverlayButton->setText("Add Overlay");
		QString overlayText = "Overlay " + num;
		ui->sectionComboBox->removeItem(ui->sectionComboBox->findText(overlayText));
	}
	else {
		// No Overlay - let's add one
		this->maestro_controller_->getSectionController(index)->addOverlay(Colors::MixMode::NORMAL, 0.5);
		this->active_section_controller_ = this->maestro_controller_->getSectionController(index)->getOverlayController().get();
		QString overlayText = QString("Overlay %1").arg(num);
		ui->sectionComboBox->addItem(overlayText);

		// FIXME: Remove once Overlays can be removed dynamically
		ui->addOverlayButton->hide();
	}
}

void MaestroControl::on_alphaSpinBox_valueChanged(double arg1) {
	this->on_mixModeComboBox_currentIndexChanged(ui->mixModeComboBox->currentIndex());
}

/**
 * Changes the current animation.
 * @param index Index of the new animation.
 */
void MaestroControl::on_animationComboBox_currentIndexChanged(int index) {
	this->active_section_controller_->getSection()->setColorAnimation((Section::ColorAnimations)(index + 1), ui->reverseAnimationCheckBox->isChecked());
}

/**
 * Changes the color scheme.
 * If 'Custom' is selected, this sets the custom color controls to visible. Otherwise it hides them.
 * @param index Index of the new color scheme.
 */
void MaestroControl::on_colorComboBox_currentIndexChanged(int index) {
	switch (index) {
		case 0:	// Custom
			this->on_custom_color_changed();
			this->setCustomColorControlsVisible(true);
			break;
		case 1:	// Fire
			{
				unsigned char numColors = 14;
				Colors::RGB fire[numColors];
				Colors::generateScalingColorArray(fire, &Colors::RED, &Colors::ORANGE, numColors, true);
				this->active_section_controller_->setControllerColors(fire, numColors);
				this->setCustomColorControlsVisible(false);
				break;
			}
		case 2:	// Deep Sea
			{
				unsigned char numColors = 14;
				Colors::RGB deepSea[numColors];
				Colors::generateScalingColorArray(deepSea, &Colors::BLUE, &Colors::GREEN, numColors, true);
				this->active_section_controller_->setControllerColors(deepSea, numColors);
				this->setCustomColorControlsVisible(false);
				break;
			}
		default:// Color Wheel
			this->active_section_controller_->getSection()->setColors(Colors::COLORWHEEL, 12);
			this->setCustomColorControlsVisible(false);
	}
}

/**
 * Changes the number of columns in the display grid.
 * @param arg1 New number of columns.
 */
void MaestroControl::on_columnsSpinBox_valueChanged(int arg1) {
	this->active_section_controller_->setLayout(ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
}


/**
 * Changes the custom color scheme.
 */
void MaestroControl::on_custom_color_changed() {
	if (ui->colorComboBox->currentIndex() != 0) {
		return;
	}

	unsigned char r = ui->redDial->value();
	unsigned char g = ui->greenDial->value();
	unsigned char b = ui->blueDial->value();

	changeScalingColorArray(Colors::RGB {r, g, b});
}

/**
 * Changes the cycle speed.
 * @param value New cycle speed.
 */
void MaestroControl::on_cycleSlider_valueChanged(int value) {
	value = ui->cycleSlider->maximum() - value;
	this->active_section_controller_->getSection()->setCycleInterval((unsigned short)value);
	ui->cycleSlider->setToolTip(QString::number(value));
}

/**
 * Handles changes to the blue dial.
 * @param value New value of the blue dial.
 */
void MaestroControl::on_blueDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

/**
 * Toggles fading.
 * @param checked If true, fading is enabled.
 */
void MaestroControl::on_fadeCheckBox_toggled(bool checked) {
	this->active_section_controller_->getSection()->toggleFade();
}

/**
 * Handles changes to the green dial.
 * @param value New value of the green dial.
 */
void MaestroControl::on_greenDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

void MaestroControl::on_mixModeComboBox_currentIndexChanged(int index) {
	QStringList args = ui->sectionComboBox->currentText().split(" ");
	int sectionIndex = args[1].toInt() -1;

	if (this->maestro_controller_->getSectionController(sectionIndex)->getOverlayController()) {
		this->maestro_controller_->getSectionController(sectionIndex)->getOverlay()->mixMode = (Colors::MixMode)index;

		// Show/hide spin box for alpha only
		if (index == 2) {
			ui->alphaSpinBox->setVisible(true);
		}
		else {
			ui->alphaSpinBox->setVisible(false);
		}
	}
}

/**
 * Sets the number of colors in the color scheme.
 * @param arg1 New color count.
 */
void MaestroControl::on_numColorsSpinBox_valueChanged(int arg1) {
	this->on_custom_color_changed();
}

/**
 * Handles changes to the red dial.
 * @param value New value of the red dial.
 */
void MaestroControl::on_redDial_valueChanged(int value) {
	this->on_custom_color_changed();
}

/**
 * Toggles whether the color animation is shown in reverse.
 * @param checked If true, reverse the animation.
 */
void MaestroControl::on_reverseAnimationCheckBox_toggled(bool checked) {
	on_animationComboBox_currentIndexChanged(ui->animationComboBox->currentIndex());
}

/**
 * Changes the number of rows in the display grid.
 * @param arg1 New number of rows.
 */
void MaestroControl::on_rowsSpinBox_valueChanged(int arg1) {
	this->active_section_controller_->setLayout(ui->rowsSpinBox->value(), ui->columnsSpinBox->value());
}

void MaestroControl::on_sectionComboBox_currentIndexChanged(const QString &arg1) {
	QStringList args = arg1.split(" ");
	QString type = args[0];
	int num = args[1].toInt();

	if(QString::compare(type, "section", Qt::CaseInsensitive) == 0) {
		// Set active controller using MaestroController's SectionControllers list
		this->active_section_controller_ = this->maestro_controller_->getSectionController(num - 1);

		// Check to see if an Overlay's already been added: if so, change the text of the Button
		// FIXME: Fix removing Overlays. For now, just hide the button
		//ui->addOverlayButton->show();
		this->setOverlayControlsVisible(false);
		if (this->active_section_controller_->getOverlayController()) {
			//ui->addOverlayButton->setText(QString("Remove Overlay"));
		}
		else {
			ui->addOverlayButton->setText(QString("Add Overlay"));
		}
	}
	else {	// Overlay
		ui->addOverlayButton->hide();
		// Set active controller to OverlayController
		this->active_section_controller_ = this->maestro_controller_->getSectionController(num - 1)->getOverlayController().get();
		// Hide layout buttons
		this->setOverlayControlsVisible(true);
	}
}

/**
 * Sets the variance of the colors in the color scheme.
 * @param arg1 New variance between colors (0-255).
 */
void MaestroControl::on_thresholdSpinBox_valueChanged(int arg1) {
	this->on_custom_color_changed();
}

/**
 * Toggles the visibility of the custom color scheme controls.
 * @param enabled If true, display custom controls.
 */
void MaestroControl::setCustomColorControlsVisible(bool enabled) {
	ui->redDial->setVisible(enabled);
	ui->greenDial->setVisible(enabled);
	ui->blueDial->setVisible(enabled);
	ui->numColorsSpinBox->setVisible(enabled);
	ui->numColorsLabel->setVisible(enabled);
	ui->thresholdSpinBox->setVisible(enabled);
	ui->thresholdLabel->setVisible(enabled);
}

/**
 * Destructor.
 */
MaestroControl::~MaestroControl() {
	delete ui;
}
