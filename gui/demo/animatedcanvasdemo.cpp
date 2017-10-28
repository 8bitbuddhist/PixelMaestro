#include <QColor>
#include <QImage>
#include <QImageReader>
#include "animatedcanvasdemo.h"
#include "canvas/colorcanvas.h"

AnimatedCanvasDemo::AnimatedCanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	// Load image
	QImageReader gif(":/resources/nyan.gif", "GIF");
	Point gif_size = Point(gif.size().width(), gif.size().height());

	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(&gif_size);

	// Reduce refresh interval
	this->timer_.setInterval(125);

	SectionController *section_controller = this->maestro_controller_->get_section_controller(0);
	Section* section(section_controller->get_section());
	ColorCanvas* canvas = static_cast<ColorCanvas*>(section->set_canvas(CanvasType::Type::ColorCanvas, gif.imageCount()));

	// Copy each frame to the Canvas
	for (uint16_t i = 0; i < gif.imageCount(); i++) {
		QImage frame = gif.read();
		for (uint16_t y = 0; y < gif_size.y; y++) {
			for (uint16_t x = 0; x < gif_size.x; x++) {
				QColor pix_color = frame.pixelColor(x, y);
				Colors::RGB color(pix_color.red(), pix_color.green(), pix_color.blue());
				canvas->draw_point(color, x, y);
			}
		}
		canvas->next_frame();
		gif.jumpToNextImage();
	}
}
