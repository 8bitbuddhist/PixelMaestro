# Structure
PixelMaestro is split into three main components:
* [Pixel](pixel.md): A single RGB output.
* [Animation](animation.md): An animation to render in a Section.
* [Section](section.md): A collection of multiple Pixels. Provides the core functionality for animating Pixels.
* [Maestro](maestro.md): A collection of Sections. Handles the synchronization and updating of one or more Sections.

PixelMaestro also includes the following support classes:
* [Canvas](canvas.md): Provides methods for drawing custom shapes and patterns onto a Section.
* [Colors](colors.md): Provides core utilities for managing colors including several pre-defined colors, color schemes, and methods for generating new colors.
* [Show](show.md): Provides a way to schedule animation changes and other actions via a Maestro. These changes are triggered over the course of the program's runtime.
* [Utility](utility.md): Shared (mostly mathematic) methods.

# Basic Usage
The following code manages a 10x10 grid of Pixels cycling through a set of 12 various colors.
```c++
Point layout = (10, 10);

Section sections[] = {
	new Section(&layout)
}
maestro.get_section(0)->set_animation(new BlinkAnimation(maestro.get_section(0), Colors::COLORWHEEL, 12));

Maestro maestro(sections, num_sections);

// Define a timer or loop method that also tracks the program's runtime in milliseconds
maestro.update(runtime);
```
