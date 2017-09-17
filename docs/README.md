## Contents
1. [Structure](#structure)
2. [Quick Start](#quick-start)

# Structure
PixelMaestro has four main components:
* [Maestro](maestro.md): Main class. Handles synchronizing one or more Sections.
* [Section](section.md): Provides the core functionality for managing and animating groups of Pixels.
* [Animation](animation.md): An animation to render in a Section.
* [Show](show.md): Provides a way to schedule animation changes and other actions via a Maestro. These changes are triggered over the course of the program's runtime.

PixelMaestro also includes the following support classes:
* [Canvas](canvas.md): Provides methods for drawing custom shapes and patterns onto a Section.
* [Colors](colors.md): Provides core utilities for managing colors including several pre-defined colors, color schemes, and methods for generating new colors.
* [Point](point.md): Class for managing coordinates on the Pixel grid.
* [Pixel](pixel.md): A single RGB output.
* [Utility](utility.md): Shared (mostly mathematic) methods.

# Quick Start
This Arduino-style example shows how to create a new Pixel grid 50 Pixels wide and 10 Pixels tall, draw text, and make it flash.

```c++
Section sections[] = {
	// Create a new 50x10 Pixel grid
	Section(new Point(50, 10)
};
// Add the Section to the Maestro
Maestro maestro(sections, 1);

void setup() {
	// Create a new blinking animation using an assortment of colors
	sections[0].set_animation(new BlinkAnimation(Colors::COLORWHEEL, 12));

	// Create a new Canvas and write "Hello world" using a 5x8 font
	Canvas* canvas = sections[0].add_canvas();
	canvas.draw_text(0, 0, new Font5x8(), "Hello world!");
}

void loop() {
	maestro.update(millis());

	Colors::RGB color;
	for (unsigned int pixel = 0; pixel < sections[0]->get_dimesions()->size(); pixel++) {
		color = sections[0].get_pixel_color(pixel);
		// Add methods to use `color` below
	}
}
```
