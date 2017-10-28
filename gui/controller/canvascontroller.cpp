#include <QByteArray>
#include <QImageReader>
#include <QString>
#include "canvascontroller.h"
#include "canvas/colorcanvas.h"

CanvasController::CanvasController(SectionController *section_controller, CanvasType::Type canvas_type, uint16_t num_frames) {
	section_controller_ = section_controller;
	canvas_ = section_controller->get_section()->set_canvas(canvas_type, num_frames);
}

Canvas* CanvasController::get_canvas() {
	return canvas_;
}

void CanvasController::load_image(QString filename, QByteArray filetype) {
	QImageReader image(filename, filetype);
	Point image_size = Point(image.size().width(), image.size().height());

	canvas_->set_num_frames(image.imageCount());
	Point cursor(0, 0);
	for (uint16_t i = 0; i < image.imageCount(); i++) {
		QImage frame = image.read();
		for (uint16_t y = 0; y < image_size.y; y++) {
			for (uint16_t x = 0; x < image_size.x; x++) {
				cursor.set(x, y);
				if (canvas_->in_bounds(&cursor)) {
					QColor pix_color = frame.pixelColor(x, y);
					Colors::RGB color(pix_color.red(), pix_color.green(), pix_color.blue());

					switch (canvas_->get_type()) {
						case CanvasType::AnimationCanvas:
							{
								// Only draw if the Pixel is not completely black
								if (color != Colors::BLACK) {
									canvas_->draw_point(x, y);
								}
							}
							break;
						case CanvasType::ColorCanvas:
							static_cast<ColorCanvas*>(canvas_)->draw_point(color, x, y);
							break;
					}
				}
			}
		}
		canvas_->next_frame();
		image.jumpToNextImage();
	}
}

CanvasController::~CanvasController() {
	section_controller_->get_section()->remove_canvas();
}
