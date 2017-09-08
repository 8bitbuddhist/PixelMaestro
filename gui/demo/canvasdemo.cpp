/*
 * PatternDemo.cpp - Demonstrates PixelMaestro's Pattern features.
 */

#include "../drawingarea/simpledrawingarea.h"
#include "canvasdemo.h"
#include "animation/mergeanimation.h"
#include "canvas/fonts/font5x8.h"
#include "controller/maestrocontroller.h"
#include "controller/sectioncontroller.h"
#include "core/point.h"

CanvasDemo::CanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {

	// Create a new Pixel grid.
	Point* layout = new Point(80, 80);

	// Initializes our Canvas grid to the same size of the Pixel grid. All values default to false.
	canvas_grid_ = new bool[layout->x * layout->y] {0};

	// Create the new Canvas.
	canvas_ = new Canvas(&canvas_grid_[0]);

	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(layout);

	SectionController *sectionController = maestro_controller_->get_section_controller(0);
	std::shared_ptr<Section> section = sectionController->get_section();

	MergeAnimation* animation = new MergeAnimation(section.get(), Colors::COLORWHEEL, 12);
	section->set_color_animation(animation);

	section->set_canvas(canvas_);

	// Start drawing stuff
	Point* cursor = new Point(0, 0);
	Point* target = new Point(0, 0);
	// First, box off the Canvas into 4 quadrants
	cursor->set(40, 0);
	target->set(40, 80);
	canvas_->draw_line(cursor, target);

	cursor->set(0, 40);
	target->set(80, 40);
	canvas_->draw_line(cursor, target);

	// Draw "PixelMaestro" in the top-left corner
	cursor->set(2, 8);
	target->set(38, 8);
	canvas_->draw_line(cursor, target);

	Font *font = new Font5x8();
	cursor->set(7, 10);
	canvas_->draw_text(cursor, font, "Pixel", 5);

	cursor->set(2, 20);
	canvas_->draw_text(cursor, font, "Maestro", 7);

	cursor->set(2, 30);
	target->set(38, 30);
	canvas_->draw_line(cursor, target);

	// Draw a few concentric circles in the top-right corner
	cursor->set(60, 20);
	canvas_->draw_circle(cursor, 5, true);
	canvas_->draw_circle(cursor, 10, false);
	canvas_->draw_circle(cursor, 15, false);
	canvas_->draw_circle(cursor, 19, false);

	// Draw triangles in the bottom-left corner
	cursor->set(11, 71);
	target->set(31, 51);
	canvas_->draw_triangle(cursor, target, new Point(26, 66), true);

	cursor->set(9, 69);
	//target->set(9, 49);
	target->set(14, 54);
	canvas_->draw_triangle(cursor, target, new Point(29, 49), true);

	cursor->set(0, 80);
	target->set(40, 40);
	canvas_->draw_line(cursor, target);

	cursor->set(7, 47);
	canvas_->draw_rect(cursor, new Point(27, 27), false);

	// Draw a peace symbol in the final quadrant
	cursor->set(60, 60);
	canvas_->draw_circle(cursor, 15, false);

	cursor->set(60, 45);
	target->set(60, 75);
	canvas_->draw_line(cursor, target);

	// Draw v-lines
	target->set(60, 60);
	cursor->set(50, 50);
	canvas_->draw_line(cursor, target);

	cursor->set(70, 50);
	canvas_->draw_line(cursor, target);
}
