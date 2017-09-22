#include "animation/waveanimation.h"
#include "canvas/colorcanvas.h"
#include "canvas/fonts/font5x8.h"
#include "colorcanvasdemo.h"

ColorCanvasDemo::ColorCanvasDemo(QWidget* parent, MaestroController* maestro_controller) : SimpleDrawingArea(parent, maestro_controller) {
	Point* layout = new Point(80, 80);

	maestro_controller_ = maestro_controller;
	maestro_controller_->add_section_controller(layout);

	SectionController *section_controller = maestro_controller_->get_section_controller(0);
	Section* section = section_controller->get_section();
	section->set_animation(new WaveAnimation(Colors::COLORWHEEL, 12));

	Section::Overlay* overlay = section->add_overlay(Colors::MixMode::OVERLAY);
	ColorCanvas* canvas = dynamic_cast<ColorCanvas*>(overlay->section->set_canvas(new ColorCanvas(section)));

	canvas->draw_circle(Colors::BLUE, 40, 40, 40, true);
	canvas->draw_circle(Colors::GREEN, 40, 40, 30, true);
	canvas->draw_circle(Colors::RED, 40, 40, 20, true);
	canvas->draw_triangle(Colors::VIOLET, 40, 10, 70, 70, 10, 70, false);

	// Not true black since the Overlay mix mode treats that as transparent
	canvas->draw_text({0, 0, 1}, 10, 37, new Font5x8(), "PixelMaestro");
}
