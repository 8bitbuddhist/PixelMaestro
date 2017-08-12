# Structure
PixelMaestro is split into three main components:
* [Pixel](pixel.md): A single RGB output.
* [Section](section.md): A collection of multiple Pixels. Provides the core functionality for animating Pixels.
* [Maestro](maestro.md): A collection of Sections. Handles the synchronization and updating of one or more Sections.

PixelMaestro also the following utility classes:
* [Colors](colors.md): Provides core utilities for managing colors including an RGB struct, several pre-defined colors and color schemes, and methods for generating new colors and color arrays.
* [Show](show.md): Allows you to schedule animation changes and other actions to be performed by a Maestro. These changes are triggered over the course of the program's runtime.

# Basic Usage
The following code creates a 10x10 grid of Pixels flashing a variety of colors:
```c++
int rows = 10;
int columns = 10;
int numPixels = rows * columns;
Pixel pixels[numPixels];

int numSections = 1;
Section sections[numSections];
sections[0].setPixels(pixels, numPixels);
sections[0].setColors(Colors::COLORWHEEL, 12);
sections[0].setColorAnimation(ColorAnimations::BLINK, false, AnimationOrientations::HORIZONTAL);

Maestro maestro;
maestro.setSections(sections, numSections);
```
