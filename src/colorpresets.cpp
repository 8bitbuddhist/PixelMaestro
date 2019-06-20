/*
 * ColorPresets - Provides pre-defined colors and color palettes.
 */

#include "colorpresets.h"

namespace PixelMaestro {
	// Basic color set
	Colors::RGB ColorPresets::Red		= {255, 0,   0};
	Colors::RGB ColorPresets::Green		= {0,   255, 0};
	Colors::RGB ColorPresets::Blue		= {0,   0,   255};
	Colors::RGB ColorPresets::White		= {255, 255, 255};
	Colors::RGB ColorPresets::Black		= {0,   0,   0};

	// Extended color set
	Colors::RGB ColorPresets::Orange 	= {255, 128, 0};
	Colors::RGB ColorPresets::Yellow 	= {255, 255, 0};
	Colors::RGB ColorPresets::Chartreuse	= {128, 255, 0};
	Colors::RGB ColorPresets::Spring 	= {0,   255, 128};
	Colors::RGB ColorPresets::Cyan		= {0,   255, 255};
	Colors::RGB ColorPresets::Azure 	= {0,   128, 255};
	Colors::RGB ColorPresets::Violet 	= {143, 0,   255};
	Colors::RGB ColorPresets::Magenta	= {255, 0,   255};
	Colors::RGB ColorPresets::Rose		= {255, 0,   128};
	Colors::RGB ColorPresets::Indigo 	= {75,  0,   130};

	// Color collections
	Colors::RGB ColorPresets::Colorwheel[12] = {
		ColorPresets::Red,
		ColorPresets::Orange,
		ColorPresets::Yellow,
		ColorPresets::Chartreuse,
		ColorPresets::Green,
		ColorPresets::Spring,
		ColorPresets::Cyan,
		ColorPresets::Azure,
		ColorPresets::Blue,
		ColorPresets::Violet,
		ColorPresets::Magenta,
		ColorPresets::Rose
	};

	Colors::RGB ColorPresets::Rainbow[7] = {
		ColorPresets::Red,
		ColorPresets::Orange,
		ColorPresets::Yellow,
		ColorPresets::Green,
		ColorPresets::Blue,
		ColorPresets::Indigo,
		ColorPresets::Violet
	};

	Palette ColorPresets::Colorwheel_Palette = Palette(Colorwheel, 12);
	Palette ColorPresets::Rainbow_Palette = Palette(Rainbow, 7);
}
