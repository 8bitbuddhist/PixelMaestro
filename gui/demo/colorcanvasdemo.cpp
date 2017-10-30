#include "animation/radialanimation.h"
#include "canvas/colorcanvas.h"
#include "canvas/fonts/font5x8.h"
#include "colorcanvasdemo.h"
#include "colorpresets.h"

ColorCanvasDemo::ColorCanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	Point* layout = new Point(80, 80);

	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(layout);

	SectionController *section_controller = maestro_controller_->get_section_controller(0);
	Section* section = section_controller->get_section();
	Animation* animation = section->set_animation(AnimationType::Radial, ColorPresets::COLORWHEEL, 12);
	animation->set_reverse(true);

	Section::Overlay* overlay = section->set_overlay(Colors::MixMode::Overlay);
	ColorCanvas* canvas = static_cast<ColorCanvas*>(overlay->section->set_canvas(CanvasType::Type::ColorCanvas));

	canvas->draw_circle(ColorPresets::BLUE, 40, 40, 40, true);
	canvas->draw_circle(ColorPresets::GREEN, 40, 40, 30, true);
	canvas->draw_circle(ColorPresets::RED, 40, 40, 20, true);

	// Not true black since the Overlay mix mode treats black as transparent
	canvas->draw_rect({0, 0, 1}, 9, 36, 62, 9, true);
	canvas->draw_text(ColorPresets::WHITE, 10, 37, new Font5x8(), (char*)"PixelMaestro", 12);
}
