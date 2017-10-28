#include <QImageReader>
#include "animatedcanvasdemo.h"
#include "controller/sectioncontroller.h"

AnimatedCanvasDemo::AnimatedCanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	// Load image
	QImageReader gif(":/resources/nyan.gif", "GIF");
	Point gif_size = Point(gif.size().width(), gif.size().height());

	maestro_controller_ = maestro_controller;
	SectionController* section_controller = maestro_controller_->add_section_controller(&gif_size).get();

	canvas_controller_ = std::unique_ptr<CanvasController>(new CanvasController(section_controller, CanvasType::ColorCanvas, gif.imageCount()));
	canvas_controller_->load_image(":/resources/nyan.gif", "GIF");

	// Lower refresh speed
	this->timer_.setInterval(125);
}
