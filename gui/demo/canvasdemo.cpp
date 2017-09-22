/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */

#include "canvas/animationcanvas.h"
#include "drawingarea/simpledrawingarea.h"
#include "canvasdemo.h"
#include "animation/mergeanimation.h"
#include "canvas/fonts/font5x8.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "core/point.h"

CanvasDemo::CanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {

	// Create a new Pixel grid.
	Point* layout = new Point(80, 80);

	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(layout);

	SectionController *section_controller = maestro_controller_->get_section_controller(0);
	Section* section = section_controller->get_section();

	section->set_animation(new MergeAnimation(Colors::COLORWHEEL, 12));

	Canvas* canvas = section->set_canvas(new AnimationCanvas(section));

	// Start drawing
	// First, box off the Canvas into 4 quadrants
	canvas->draw_line(40, 0, 40, 80);
	canvas->draw_line(0, 40, 80, 40);

	// Draw "PixelMaestro" in the top-left corner
	canvas->draw_line(2, 8, 38, 8);

	Font *font = new Font5x8();
	canvas->draw_text(7, 10, font, "Pixel");
	canvas->draw_text(2, 20, font, "Maestro");
	canvas->draw_line(2, 30, 38, 30);

	// Draw a few concentric circles in the top-right corner
	canvas->draw_circle(60, 20, 5, true);
	canvas->draw_circle(60, 20, 10, false);
	canvas->draw_circle(60, 20, 15, false);
	canvas->draw_circle(60, 20, 19, false);

	// Draw triangles in the bottom-left corner
	canvas->draw_triangle(11, 71, 31, 51, 26, 66, true);
	canvas->draw_triangle(9, 69, 14, 54, 29, 49, true);

	canvas->draw_line(0, 80, 40, 40);

	canvas->draw_rect(7, 47, 27, 27, false);

	// Draw a peace symbol in the final quadrant
	canvas->draw_circle(60, 60, 15, false);
	canvas->draw_line(60, 45, 60, 75);

	// Draw v-lines
	canvas->draw_line(50, 50, 60, 60);
	canvas->draw_line(70, 50, 60, 60);
}
