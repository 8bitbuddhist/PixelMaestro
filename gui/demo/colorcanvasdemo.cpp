#include "animation/radialanimation.h"
#include "canvas/colorcanvas.h"
#include "canvas/fonts/font5x8.h"
#include "colorcanvasdemo.h"

ColorCanvasDemo::ColorCanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	Point* layout = new Point(80, 80);

	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(layout);

	SectionController *section_controller = maestro_controller_->get_section_controller(0);
	Section* section = section_controller->get_section();
	section->set_animation(new RadialAnimation(Colors::COLORWHEEL, 12));
	section->get_animation()->set_reverse(true);

	Section::Overlay* overlay = section->add_overlay(Colors::MixMode::Overlay);
	ColorCanvas* canvas = static_cast<ColorCanvas*>(overlay->section->add_canvas(CanvasType::Type::ColorCanvas));

	canvas->draw_circle(Colors::BLUE, 40, 40, 40, true);
	canvas->draw_circle(Colors::GREEN, 40, 40, 30, true);
	canvas->draw_circle(Colors::RED, 40, 40, 20, true);

	// Not true black since the Overlay mix mode treats black as transparent
	canvas->draw_rect({0, 0, 1}, 9, 36, 62, 9, true);
	canvas->draw_text(Colors::WHITE, 10, 37, new Font5x8(), "PixelMaestro");
}
