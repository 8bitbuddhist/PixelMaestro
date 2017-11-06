#include "colorpresets.h"
#include "core/colors.h"
#include "palettecontroller.h"

PaletteController::PaletteController() {
	initialize_palettes();
}

PaletteController::Palette* PaletteController::add_palette(QString name, Colors::RGB* colors, uint8_t num_colors) {
	palettes_.push_back(Palette(name, colors, num_colors));
	return &palettes_[palettes_.size() - 1];
}

PaletteController::Palette* PaletteController::get_palette(uint8_t index) {
	return &palettes_[index];
}

PaletteController::Palette* PaletteController::get_palette(QString name) {
	for (uint8_t i = 0; i < palettes_.size(); i++) {
		if (palettes_[i].name == name) {
			return &palettes_[i];
		}
	}
	return nullptr;
}

std::vector<PaletteController::Palette>* PaletteController::get_palettes() {
	return &palettes_;
}

void PaletteController::initialize_palettes() {
	uint8_t num_colors = 14;
	Colors::RGB colors[num_colors];

	palettes_.clear();

	Colors::generate_scaling_color_array(colors, &ColorPresets::RED, &ColorPresets::YELLOW, num_colors, true);
	palettes_.push_back(Palette("Fire", colors, num_colors));

	Colors::generate_scaling_color_array(colors, &ColorPresets::BLUE, &ColorPresets::GREEN, num_colors, true);
	palettes_.push_back(Palette("Deep Sea", colors, num_colors));

	palettes_.push_back(Palette("Color Wheel", ColorPresets::COLORWHEEL, 12));
}

void PaletteController::remove_palette(uint8_t index) {
	palettes_.erase(palettes_.begin() + index);
}
