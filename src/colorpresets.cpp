/*
 * ColorPresets - Provides pre-defined colors and color palettes.
 */

#include "colorpresets.h"

namespace PixelMaestro {
	// Simple color set
	Colors::RGB ColorPresets::RED			= {255, 0,   0};
	Colors::RGB ColorPresets::GREEN			= {0,   255, 0};
	Colors::RGB ColorPresets::BLUE			= {0,   0,   255};
	Colors::RGB ColorPresets::WHITE			= {255, 255, 255};
	Colors::RGB ColorPresets::BLACK			= {0,   0,   0};

	// Extended color set
	Colors::RGB ColorPresets::ORANGE 		= {255, 128, 0};
	Colors::RGB ColorPresets::YELLOW 		= {255, 255, 0};
	Colors::RGB ColorPresets::CHARTREUSE	= {128, 255, 0};
	Colors::RGB ColorPresets::SPRING 		= {0,   255, 128};
	Colors::RGB ColorPresets::CYAN			= {0,   255, 255};
	Colors::RGB ColorPresets::AZURE 		= {0,   128, 255};
	Colors::RGB ColorPresets::VIOLET 		= {143, 0,   255};
	Colors::RGB ColorPresets::MAGENTA		= {255, 0,   255};
	Colors::RGB ColorPresets::ROSE			= {255, 0,   128};
	Colors::RGB ColorPresets::INDIGO 		= {75,  0,   130};

	// Color collections
	Colors::RGB ColorPresets::COLORWHEEL[12] = {
		ColorPresets::RED,
		ColorPresets::ORANGE,
		ColorPresets::YELLOW,
		ColorPresets::CHARTREUSE,
		ColorPresets::GREEN,
		ColorPresets::SPRING,
		ColorPresets::CYAN,
		ColorPresets::AZURE,
		ColorPresets::BLUE,
		ColorPresets::VIOLET,
		ColorPresets::MAGENTA,
		ColorPresets::ROSE
	};

	Colors::RGB ColorPresets::RAINBOW[7] = {
		ColorPresets::RED,
		ColorPresets::ORANGE,
		ColorPresets::YELLOW,
		ColorPresets::GREEN,
		ColorPresets::BLUE,
		ColorPresets::INDIGO,
		ColorPresets::VIOLET
	};
}
