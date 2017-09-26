## Contents
1. [Structure](#structure)
2. [Quick Start](#quick-start)

# Structure
PixelMaestro has five main components:
* [Maestro](maestro.md): Main class. Handles synchronizing one or more Sections.
* [Section](section.md): Provides the core functionality for managing and animating groups of Pixels.
* [Pixel](pixel.md): A single RGB output.
* [Animation](animation.md): An animation to render in a Section.
* [Show](show.md): Provides a way of scheduling animation changes and other actions via a Maestro. These changes are triggered automatically over the course of the program's runtime.

PixelMaestro also includes the following support classes:
* [Canvas](canvas.md): Provides methods for drawing custom shapes and patterns onto a Section.
* [Colors](colors.md): Provides core utilities for managing colors including several pre-defined colors, color schemes, and methods for generating new colors.
* [Point](point.md): Class for managing coordinates on the Pixel grid.
* [Serial](serial.md): Provides methods for sending PixelMaestro commands to other devices via serial communication.
* [Utility](utility.md): Shared (mostly mathematic) methods.

# Quick Start
This Arduino-style example shows how to create a new Pixel grid 50 Pixels wide and 10 Pixels tall, draw text, and make it flash.

```c++
#include "canvas/canvas.h"
#include "canvas/fonts/font5x8.h"
#include "core/Maestro.h"

using namespace PixelMaestro;

Section sections[] = {
	// Create a new grid 50 pixels wide and 10 pixels high
	Section(50, 10)
};
// Add the Section to the Maestro
Maestro maestro(sections, 1);

void setup() {
	// Set global brightness to 50%
	maestro.set_brightness(128);

	// Create a new blinking animation using an assortment of 12 colors, then sets the animation speed to 500ms
	sections[0].set_animation(new BlinkAnimation(Colors::COLORWHEEL, 12, 500));

	// Create a new Canvas and write "Hello world" using a 5x8 font
	Canvas* canvas = sections[0].add_canvas();
	canvas.draw_text(0, 0, new Font5x8(), "Hello world!");
}

void loop() {
	maestro.update(millis());

	Colors::RGB *color;
	for (unsigned int pixel = 0; pixel < sections[0]->get_dimesions()->size(); pixel++) {
		color = maestro.get_pixel_color(0, pixel);
		// Use `color` below, e.g. to send RGB values to a LED strip
	}
}
```
