/*
 * DemoPreset.cpp - Demonstrates how to configure a Maestro in a preset (spoiler alert: it's exactly the same).
 * Displays the text "Hello world!" and alternates from black to white.
 */

#include "demopreset.h"
#include "../animation/cycleanimation.h"
#include "../canvas/canvas.h"
#include "../canvas/fonts/font5x8.h"
#include "../core/colors.h"

namespace PixelMaestro {
	void DemoPreset::apply(Maestro* maestro) {
		Section* section = maestro->get_section(0);
		section->set_animation(new CycleAnimation(new Colors::RGB[2] { Colors::BLACK, Colors::WHITE }, 2, 2500, 1000));

		Section::Overlay* overlay = section->add_overlay(Colors::MixMode::OVERLAY);
		// Since the Overlay mix mode ignores black, we pass a color that's almost-but-not-quite black.
		overlay->section->set_animation(new CycleAnimation(new Colors::RGB[2] { Colors::WHITE, {0, 0, 1} }, 2, 2500, 1000));

		Canvas* canvas = overlay->section->add_canvas();
		canvas->draw_text(1, 1, new Font5x8(), "Hello world!");
	}
}
