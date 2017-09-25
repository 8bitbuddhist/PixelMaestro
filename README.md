# PixelMaestro
PixelMaestro is a library for creating and rendering 2D animations and patterns. While originally designed for LEDs, it can be used to render RGB values to any device or output.

PixelMaestro does not interact directly with underlying hardware. Instead, it acts as a buffer where color values are stored. You will have to use another library or wrapper to actually write the buffer to the underlying hardware. Examples of this can be found in the [Arduino folder](arduino).

**Note:** PixelMaestro is pre-alpha software. New releases can (and likely will) introduce incompatible changes.

## Getting Started
To get started, please read the [documentation](docs/README.md). You can also test PixelMaestro by running the [Qt-based frontend](gui/README.md) or [Arduino sketches](arduino).
