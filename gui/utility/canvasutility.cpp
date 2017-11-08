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
 * Copies all frames to or from an AnimationCanvas.
 * @param canvas AnimationCanvas to copy from.
 * @param target Target frameset.
 * @param target_x Target width.
 * @param target_y Target height.
 * @param copy_from_canvas If true, copy from the Canvas to the target. Otherwise, copy from the target to the Canvas.
 * @param maestro_control If copying to Canvas and serial is enabled, rebuild the Canvas on the serial device.
 */
void CanvasUtility::copy_frameset(AnimationCanvas *canvas, bool** target, uint16_t target_x, uint16_t target_y, bool copy_from_canvas, MaestroControl* maestro_control) {
	for (uint16_t frame = 0; frame < canvas->get_num_frames(); frame++) {
		if (copy_from_canvas) {
			Point target_bounds(target_x, target_y);
			for (uint16_t y = 0; y < canvas->get_section()->get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < canvas->get_section()->get_dimensions()->x; x++) {
					if (x <= target_x && y <= target_y) {
						target[frame][target_bounds.get_inline_index(x, y)] = canvas->get_frame(frame)[canvas->get_section()->get_dimensions()->get_inline_index(x, y)];
					}
				}
			}
		}
		else {
			canvas->draw_frame(target[frame], target_x, target_y);
			canvas->next_frame();

			if (maestro_control && maestro_control->cue_controller_) {
				uint8_t section = maestro_control->get_section_index();
				uint8_t overlay = maestro_control->get_overlay_index();
				maestro_control->canvas_handler->draw_frame(section, overlay, target_x, target_y, target[frame]);
				maestro_control->send_to_device();

				maestro_control->canvas_handler->next_frame(section, overlay);
				maestro_control->send_to_device();
			}
		}
	}
}

/**
 * Copies all frames from a ColorCanvas.
 * @param canvas ColorCanvas to copy from.
 * @param target Target frameset.
 * @param target_x Target width.
 * @param target_y Target height.
 * @param copy_from_canvas If true, copy from the Canvas to the target. Otherwise, copy from the target to the Canvas.
 * @param maestro_control If copying to Canvas and serial is enabled, rebuild the Canvas on the serial device.
 */
void CanvasUtility::copy_frameset(ColorCanvas *canvas, Colors::RGB** target, uint16_t target_x, uint16_t target_y, bool copy_from_canvas, MaestroControl* maestro_control) {
	for (uint16_t frame = 0; frame < canvas->get_num_frames(); frame++) {
		if (copy_from_canvas) {
			Point target_bounds(target_x, target_y);
			for (uint16_t y = 0; y < canvas->get_section()->get_dimensions()->y; y++) {
				for (uint16_t x = 0; x < canvas->get_section()->get_dimensions()->x; x++) {
					if (x <= target_x && y <= target_y) {
						target[frame][target_bounds.get_inline_index(x, y)] = canvas->get_frame(frame)[canvas->get_section()->get_dimensions()->get_inline_index(x, y)];
					}
				}
			}
		}
		else {
			canvas->draw_frame(target[frame], target_x, target_y);
			canvas->next_frame();

			if (maestro_control && maestro_control->cue_controller_) {
				uint8_t section = maestro_control->get_section_index();
				uint8_t overlay = maestro_control->get_overlay_index();
				maestro_control->canvas_handler->draw_frame(section, overlay, target_x, target_y, target[frame]);
				maestro_control->send_to_device();

				maestro_control->canvas_handler->next_frame(section, overlay);
				maestro_control->send_to_device();
			}
		}
	}
}

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
	if (maestro_control && maestro_control->cue_controller_) {
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

									if (maestro_control && maestro_control->cue_controller_) {
										maestro_control->canvas_handler->draw_point(maestro_control->get_section_index(), maestro_control->get_overlay_index(), x, y);
									}
								}
							}
							break;
						case CanvasType::ColorCanvas:
							{
								static_cast<ColorCanvas*>(canvas)->draw_point(color, x, y);

								if (maestro_control && maestro_control->cue_controller_)
									maestro_control->canvas_handler->draw_point(maestro_control->get_section_index(), maestro_control->get_overlay_index(), color, x, y);
							}
							break;
					}

					if (maestro_control && maestro_control->cue_controller_) {
						maestro_control->send_to_device();
					}
				}
			}
		}
		canvas->next_frame();
		image.jumpToNextImage();

		if (maestro_control && maestro_control->cue_controller_) {
			maestro_control->canvas_handler->next_frame(maestro_control->get_section_index(), maestro_control->get_overlay_index());
			maestro_control->send_to_device();
		}
	}
}
