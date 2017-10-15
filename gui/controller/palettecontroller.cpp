#include "core/colors.h"
#include "palettecontroller.h"

PaletteController::PaletteController() {
	uint8_t num_colors = 14;
	Colors::RGB colors[num_colors] = {Colors::BLACK};

	Colors::generate_scaling_color_array(colors, &Colors::RED, &Colors::YELLOW, num_colors, true);
	palettes_.push_back(Palette("Fire", colors, num_colors));

	Colors::generate_scaling_color_array(colors, &Colors::BLUE, &Colors::GREEN, num_colors, true);
	palettes_.push_back(Palette("Deep Sea", colors, num_colors));

	palettes_.push_back(Palette("Color Wheel", Colors::COLORWHEEL, 12));
}

PaletteController::Palette* PaletteController::add_palette(const char* name, Colors::RGB* colors, uint8_t num_colors) {
	palettes_.push_back(Palette(name, colors, num_colors));
	return &palettes_[palettes_.size() - 1];
}

PaletteController::Palette* PaletteController::get_palette(uint8_t index) {
	return &palettes_[index];
}

PaletteController::Palette* PaletteController::get_palette(std::string name) {
	for (uint8_t i = 0; i < palettes_.size(); i++) {
		if (palettes_[i].name == name) {
			return &palettes_[i];
		}
	}
	return nullptr;
}

std::vector<PaletteController::Palette> PaletteController::get_palettes() {
	return palettes_;
}

void PaletteController::remove_palette(uint8_t index) {
	palettes_.erase(palettes_.begin() + index);
}
