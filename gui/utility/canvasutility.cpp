/*
 * CanvasUtility - Tools for managing Canvases.
 */

#include <QColor>
#include <QImage>
#include <QImageReader>
#include "canvasutility.h"
#include "canvas/animationcanvas.h"
#include "canvas/colorcanvas.h"
#include "core/point.h"

/**
 * Loads an image into the Canvas.
 * @param filename Image location.
 * @param canvas Canvas to load the image into.
 * @param maestro_control Optional MaestroControl for generating Cues.
 */
void CanvasUtility::load_image(QString filename, Canvas *canvas, MaestroControl* maestro_control) {
	QImageReader image(filename, filename.right(3).toLocal8Bit());
	Point image_size = Point(image.size().width(), image.size().height());

	canvas->set_num_frames(image.imageCount());
	if (maestro_control && maestro_control->serial_port_.isOpen()) {
		maestro_control->canvas_handler->set_num_frames(maestro_control->get_section_index(), maestro_control->get_overlay_index(), image.imageCount());
		maestro_control->send_to_device();
	}

	Point cursor(0, 0);
	for (uint16_t i = 0; i < image.imageCount(); i++) {
		QImage frame = image.read();
		for (uint16_t y = 0; y < image_size.y; y++) {
			for (uint16_t x = 0; x < image_size.x; x++) {
				cursor.set(x, y);
				if (canvas->in_bounds(&cursor)) {
					QColor pix_color = frame.pixelColor(x, y);
					Colors::RGB color(pix_color.red(), pix_color.green(), pix_color.blue());

					switch (canvas->get_type()) {
						case CanvasType::AnimationCanvas:
							{
								// Only draw if the Pixel is not completely black
								if (color != Colors::RGB {0, 0, 0}) {
									canvas->draw_point(x, y);

									if (maestro_control && maestro_control->serial_port_.isOpen()) {
										maestro_control->canvas_handler->draw_point(maestro_control->get_section_index(), maestro_control->get_overlay_index(), x, y);
									}
								}
							}
							break;
						case CanvasType::ColorCanvas:
							{
								static_cast<ColorCanvas*>(canvas)->draw_point(color, x, y);

								if (maestro_control && maestro_control->serial_port_.isOpen())
									maestro_control->canvas_handler->draw_point(maestro_control->get_section_index(), maestro_control->get_overlay_index(), color, x, y);
							}
							break;
					}

					if (maestro_control && maestro_control->serial_port_.isOpen()) {
						maestro_control->send_to_device();
					}
				}
			}
		}
		canvas->next_frame();
		image.jumpToNextImage();

		if (maestro_control && maestro_control->serial_port_.isOpen()) {
			maestro_control->canvas_handler->next_frame(maestro_control->get_section_index(), maestro_control->get_overlay_index());
			maestro_control->send_to_device();
		}
	}
}
