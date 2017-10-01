#include "../catch/single_include/catch.hpp"
#include "../../src/animation/animation.h"
#include "../../src/animation/solidanimation.h"
#include "../../src/canvas/animationcanvas.h"
#include "../../src/canvas/colorcanvas.h"
#include "../../src/core/colors.h"
#include "../../src/core/maestro.h"
#include "../../src/core/point.h"
#include "../../src/core/section.h"
#include "sectiontest.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a section.", "[Section]") {
	Point dimensions(1, 10);
	Section sections[] = {
		Section(dimensions)
	};
	Maestro maestro(sections, 1);
	
	Section* section = &sections[0];
	
	int test_pixel = 0;
	
	SECTION("Verify that Section dimensions are set correctly.") {
		REQUIRE(*section->get_dimensions() == dimensions);
	}
	
	SECTION("Verify that Animations and Colors are set correctly.") {
		Animation* animation = section->set_animation(new SolidAnimation());
		animation->set_colors(Colors::COLORWHEEL, 12);
		animation->set_speed(100);
		animation->set_fade(false);
		
		maestro.update(101);

		REQUIRE(*section->get_pixel(test_pixel)->get_color() == Colors::COLORWHEEL[test_pixel]);
	}
	
	SECTION("Verify that different Canvas types can be added.") {
		Animation* animation = section->set_animation(new SolidAnimation(Colors::COLORWHEEL, 12), 100);
		animation->set_fade(false);
		
		// Draw a filled in animation rectangle
		AnimationCanvas* animation_canvas = static_cast<AnimationCanvas*>(section->add_canvas(CanvasType::Type::AnimationCanvas));
		animation_canvas->draw_rect(0, 0, section->get_dimensions()->x, section->get_dimensions()->y, true);
		
		maestro.update(101);
		REQUIRE(section->get_pixel_color(test_pixel) == Colors::COLORWHEEL[test_pixel]);
		
		// Delete the Canvas
		section->remove_canvas();
		REQUIRE(section->get_canvas() == nullptr);
		
		// Draw a color rectangle
		ColorCanvas* color_canvas = static_cast<ColorCanvas*>(section->add_canvas(CanvasType::Type::ColorCanvas));
		color_canvas->draw_rect(Colors::CHARTREUSE, 0, 0, section->get_dimensions()->x, section->get_dimensions()->y, true);
		
		REQUIRE(section->get_pixel_color(test_pixel) == Colors::CHARTREUSE);
	}
	
	SECTION("Verify that Overlays work.") {
		Colors::RGB section_colors[] = {Colors::WHITE};
		Colors::RGB overlay_colors[] = {Colors::BLACK, Colors::BLUE};
		
		Section::Overlay* overlay = section->add_overlay(Colors::MixMode::None);
		Animation* section_animation = section->set_animation(new SolidAnimation(section_colors, 1), 100);
		Animation* overlay_animation = overlay->section->set_animation(new SolidAnimation(overlay_colors, 2), 100);
		section_animation->set_fade(false);
		overlay_animation->set_fade(false);
		
		maestro.update(101);
		
		// Test no mix mode
		REQUIRE(section->get_pixel_color(0) == section_colors[0]);
		
		// Test Alpha mix mode
		overlay->mix_mode = Colors::MixMode::Alpha;
		overlay->alpha = 127;
		REQUIRE(section->get_pixel_color(0) == (section_colors[0] / 2));
		
		// Test Multiply mix mode
		overlay->mix_mode = Colors::MixMode::Multiply;
		REQUIRE(section->get_pixel_color(0) == overlay_colors[1]);
		
		// Test Overlay mix mode
		overlay->mix_mode = Colors::MixMode::Overlay;
		REQUIRE(section->get_pixel_color(0) == overlay_colors[0]);
		maestro.update(201);
		REQUIRE(section->get_pixel_color(0) == overlay_colors[1]);
	}
}
