#include <QImageReader>
#include "animatedcanvasdemo.h"
#include "canvas/colorcanvas.h"
#include "utility/canvasutility.h"

AnimatedCanvasDemo::AnimatedCanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	// Load image
	QImageReader gif(":/resources/nyan.gif", "GIF");
	Point gif_size = Point(gif.size().width(), gif.size().height());

	Section* section = maestro_controller_->set_sections(1, gif_size);
	Canvas* canvas = section->set_canvas(CanvasType::ColorCanvas, gif.imageCount());
	CanvasUtility::load_image(QString(":/resources/nyan.gif"), canvas);

	// Lower refresh speed
	this->timer_.setInterval(125);
}
