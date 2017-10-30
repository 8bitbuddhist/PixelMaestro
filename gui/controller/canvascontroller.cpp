#include <QByteArray>
#include <QImageReader>
#include <QString>
#include "canvascontroller.h"
#include "canvas/colorcanvas.h"

CanvasController::CanvasController(SectionController* section_controller, CanvasType::Type canvas_type, uint16_t num_frames) {
	this->section_controller_ = section_controller;
	this->canvas_ = section_controller->get_section()->set_canvas(canvas_type, num_frames);
}

CanvasController::CanvasController(SectionController *section_controller, MaestroControl* maestro_control, CanvasType::Type canvas_type, uint16_t num_frames) : CanvasController(section_controller, canvas_type, num_frames) {
	this->maestro_control_ = maestro_control;
}

Canvas* CanvasController::get_canvas() {
	return canvas_;
}

void CanvasController::load_image(QString filename, QByteArray filetype) {
	QImageReader image(filename, filetype);
	Point image_size = Point(image.size().width(), image.size().height());

	canvas_->set_num_frames(image.imageCount());
	if (maestro_control_ && maestro_control_->serial_port_.isOpen()) {
		maestro_control_->canvas_handler->set_num_frames(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), image.imageCount());
		maestro_control_->send_to_device();
	}

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
								if (color != Colors::RGB {0, 0, 0}) {
									canvas_->draw_point(x, y);

									if (maestro_control_ && maestro_control_->serial_port_.isOpen()) {
										maestro_control_->canvas_handler->draw_point(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), x, y);
									}
								}
							}
							break;
						case CanvasType::ColorCanvas:
							{
								static_cast<ColorCanvas*>(canvas_)->draw_point(color, x, y);

								if (maestro_control_ && maestro_control_->serial_port_.isOpen())
									maestro_control_->canvas_handler->draw_point(maestro_control_->get_section_index(), maestro_control_->get_overlay_index(), color, x, y);
							}
							break;
					}

					if (maestro_control_ && maestro_control_->serial_port_.isOpen()) {
						maestro_control_->send_to_device();
					}
				}
			}
		}
		canvas_->next_frame();
		image.jumpToNextImage();

		if (maestro_control_ && maestro_control_->serial_port_.isOpen()) {
			maestro_control_->canvas_handler->next_frame(maestro_control_->get_section_index(), maestro_control_->get_overlay_index());
			maestro_control_->send_to_device();
		}
	}
}

CanvasController::~CanvasController() {
	section_controller_->get_section()->remove_canvas();
}
