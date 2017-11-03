#include <QImageReader>
#include "animatedcanvasdemo.h"
#include "canvas/colorcanvas.h"
#include "controller/sectioncontroller.h"
#include "utility/canvasutility.h"

AnimatedCanvasDemo::AnimatedCanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	// Load image
	QImageReader gif(":/resources/nyan.gif", "GIF");
	Point gif_size = Point(gif.size().width(), gif.size().height());

	maestro_controller_ = maestro_controller;
	SectionController* section_controller = maestro_controller_->add_section_controller(&gif_size).get();
	Canvas* canvas = section_controller->get_section()->set_canvas(CanvasType::ColorCanvas, gif.imageCount());
	CanvasUtility::load_image(QString(":/resources/nyan.gif"), canvas);

	// Lower refresh speed
	this->timer_.setInterval(125);
}
