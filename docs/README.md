## Contents
1. [Structure](#structure)
2. [Quick Start](#quick-start)

# Structure
PixelMaestro has three main components:
* [Maestro](maestro.md): Main class. Handles synchronizing one or more Sections.
* [Section](section.md): Manages a grid of Pixels. All actions that change the display output are performed through a Section. Sections also manage Animations and Canvases.
* [Pixel](pixel.md): A single RGB output. Each Pixel stores a color value that you can send to an output device.

PixelMaestro also includes the following support classes:
* [Animation](animation.md): Various animations that can be displayed using a Section.
* [Canvas](canvas.md): Tools for drawing custom shapes and patterns onto a Section.
* [Colors](colors.md): Tools for defining custom colors and generating color palettes.
	* ColorPresets: Provides several pre-defined common colors.
* [Cue](cue.md): Provides methods serializing PixelMaestro commands.
* [Point](point.md): Defines the size of Pixel grids as well as individual coordinates.
* [Show](show.md): Utility for scheduling Cues to run at certain points in the program's lifecycle.
* [Utility](utility.md): Common methods (prevents having to pull in stdlib).

# Example
This smaple Arduino sketch shows how to create a new Pixel grid 50 Pixels wide and 10 Pixels tall, draw text, and make it flash.

```c++
#include "canvas/canvas.h"
#include "canvas/fonts/font5x8.h"
#include "colorpresets.h"
#include "core/Maestro.h"

using namespace PixelMaestro;

// Define a Maestro with a single Section 50 Pixels wide and 10 Pixels high.
Maestro maestro(50, 10);

void setup() {
	// Set global brightness to 50%
	maestro.set_brightness(128);

	// Create a new blinking animation using the ColorWheel preset, then sets the animation speed to 500ms
	Animation* animation = maestro.get_section(0)->set_animation(AnimationType::Blink, ColorPresets::COLORWHEEL, 12);
	animation->set_speed(500);

	// Create a new Canvas and write "Hello world" using a 5x8 font
	Canvas* canvas = maestro.get_section(0)->add_canvas(CanvasType::AnimationCanvas);
	canvas->draw_text(0, 0, new Font5x8(), "Hello world!", 12);
}

void loop() {
	maestro.update(millis());

	for (unsigned short y = 0; y < maestro.get_section(0)->get_dimensions()->y; y++) {
		for (unsigned short x = 0; x < maestro.get_section(0)->get_dimensions()->x; x++) {
			// Retrieve the Pixel's color using `maestro.get_pixel_color(0, x, y);`
		}
	}
}
```
