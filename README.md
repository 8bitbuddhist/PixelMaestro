# PixelMaestro
PixelMaestro is a library for creating and rendering 2D animations and patterns. PixelMaestro works by manipulating the color values of Pixels, or individual color points, using customizable animations. While originally designed for LEDs, it can be used to generate RGB values for any device or output.

## Structure
PixelMaestro is split into five components:
* [Pixel](docs/pixel.md): A single RGB output.
* [Section](docs/section.md): A collection of multiple Pixels. Provides the core functionality for animating Pixels.
* [Maestro](docs/maestro.md): A collection of Sections. Handles the synchronization and updating of one or more Sections.

PixelMaestro includes the following utility classes:
* [Colors](docs/colors.md): Provides core utilities for managing colors including an RGB struct, several pre-defined colors and color schemes, and methods for generating new colors and color arrays.
* [Show](docs/show.md): Allows you to schedule animation changes and other actions to be performed by a Maestro. These changes are triggered over the course of the program's runtime.
