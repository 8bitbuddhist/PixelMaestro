#include "../catch/single_include/catch.hpp"
#include "../../src/animation/animation.h"
#include "../../src/animation/solidanimation.h"
#include "../../src/canvas/palettecanvas.h"
#include "../../src/canvas/colorcanvas.h"
#include "../../src/colorpresets.h"
#include "../../src/core/colors.h"
#include "../../src/core/maestro.h"
#include "../../src/core/point.h"
#include "../../src/core/section.h"
#include "sectiontest.h"

using namespace PixelMaestro;

TEST_CASE("Create and manipulate a section.", "[Section]") {
	Point dimensions = Point(1, 10);
	Section sections[] = {
		Section(dimensions.x, dimensions.y)
	};
	Maestro maestro(sections, 1);

	Section* section = maestro.get_section(0);

	Palette palette = ColorPresets::Colorwheel_Palette;

	int test_pixel = 0;

	SECTION("Verify that Section dimensions are set correctly.") {
		REQUIRE(*section->get_dimensions() == dimensions);
	}

	SECTION("Verify that Animations and Colors are set correctly.") {
		Animation* animation = section->set_animation(AnimationType::Solid);
		animation->set_palette(&palette);
		animation->set_timer(100);
		animation->set_fade(false);

		maestro.update(101);

		REQUIRE(*section->get_pixel(test_pixel, 0)->get_color() == ColorPresets::Colorwheel[test_pixel]);
	}

	SECTION("Verify that different Canvas types can be added.") {
		Animation* animation = section->set_animation(AnimationType::Solid);
		animation->set_palette(&palette);
		animation->set_timer(100);
		animation->set_fade(false);

		// Draw a filled in animation rectangle
		PaletteCanvas* palette_canvas = static_cast<PaletteCanvas*>(section->set_canvas(CanvasType::PaletteCanvas));
		palette_canvas->set_palette(&palette);
		palette_canvas->draw_rect(0, 0, 0, section->get_dimensions()->x, section->get_dimensions()->y, true);

		maestro.update(100);
		REQUIRE(section->get_pixel_color(0, 0) == *palette.get_color_at_index(0));

		// Delete the Canvas
		section->remove_canvas();
		REQUIRE(section->get_canvas() == nullptr);

		// Draw a color rectangle
		ColorCanvas* color_canvas = static_cast<ColorCanvas*>(section->set_canvas(CanvasType::ColorCanvas));
		color_canvas->draw_rect(ColorPresets::Chartreuse, 0, 0, section->get_dimensions()->x, section->get_dimensions()->y, true);

		REQUIRE(section->get_pixel_color(test_pixel, 0) == ColorPresets::Chartreuse);
	}

	SECTION("Verify that Layers work.") {
		Colors::RGB section_colors[] = {ColorPresets::White};
		Colors::RGB layer_colors[] = {ColorPresets::Black, ColorPresets::Blue};

		Palette section_palette = Palette(section_colors, 1);
		Palette layer_palette = Palette(layer_colors, 2);

		Animation* section_animation = section->set_animation(AnimationType::Solid);
		section_animation->set_palette(&section_palette);
		section_animation->set_timer(100);
		section_animation->set_fade(false);

		Section::Layer* layer = section->set_layer(Colors::MixMode::None);
		Animation* layer_animation = layer->section->set_animation(AnimationType::Solid);
		layer_animation->set_palette(&layer_palette);
		layer_animation->set_timer(100);
		layer_animation->set_fade(false);

		maestro.update(100);

		// Test no mix mode
		REQUIRE(section->get_pixel_color(0, 0) == section_colors[0]);

		// Test Alpha mix mode
		layer->mix_mode = Colors::MixMode::Alpha;
		layer->alpha = 127;
		REQUIRE(section->get_pixel_color(0, 0) == (section_colors[0] * 0.5));

		// Test Multiply mix mode
		layer->mix_mode = Colors::MixMode::Multiply;
		REQUIRE(section->get_pixel_color(0, 0) == layer_colors[0]);

		/*
		 * Test Overlay mix mode
		 * Since the Overlay is black, it registers as transparent, so we expect the Section color.
		 */
		layer->mix_mode = Colors::MixMode::Overlay;
		REQUIRE(section->get_pixel_color(0, 0) == section_colors[0]);
	}
}
