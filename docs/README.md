## Contents
1. [Structure](#structure)
2. [Quick Start](#quick-start)

# Structure
PixelMaestro has four main components:
* [Pixel](pixel.md): A single RGB output.
* [Animation](animation.md): An animation to render in a Section.
* [Section](section.md): A collection of multiple Pixels. Provides the core functionality for animating Pixels.
* [Maestro](maestro.md): A collection of Sections. Handles refreshing and synchronizing Sections.

PixelMaestro also includes the following support classes:
* [Canvas](canvas.md): Provides methods for drawing custom shapes and patterns onto a Section.
* [Colors](colors.md): Provides core utilities for managing colors including several pre-defined colors, color schemes, and methods for generating new colors.
* [Point](point.md): Class for managing coordinates on the Pixel grid.
* [Show](show.md): Provides a way to schedule animation changes and other actions via a Maestro. These changes are triggered over the course of the program's runtime.
* [Utility](utility.md): Shared (mostly mathematic) methods.

# Quick Start
This example shows how to create a new Pixel grid 50 Pixels wide and 10 Pixels tall, set a new animation, writes text, and animate the Maestro.

```c++
Section sections[] = { Section(new Point(10, 10) };
sections[0].set_animation(new BlinkAnimation(Colors::COLORWHEEL, 12));

Canvas* canvas = sections[0].add_canvas();
Point origin = {0, 0};
canvas.draw_text(&origin, new Font5x8(), "Hello world!");

Maestro maestro(sections, 1);

// Define a timer or loop method that also tracks the program's runtime in milliseconds
maestro.update(runtime);
```
