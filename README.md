# PixelMaestro
PixelMaestro is a library for creating and rendering 2D animations and patterns. While originally designed for LEDs, it can be used to display animations on any device or output.

PixelMaestro does not interact directly with hardware. Instead, it acts as a buffer where color values are stored. You will have to use another library or wrapper to actually write from the buffer to the final output. Examples of this can be found in the [Arduino folder](arduino).

**Note:** PixelMaestro is alpha software. New releases may introduce incompatible changes.

## Getting Started
You can start using PixelMaestro by using the [Qt-based frontend](gui/README.md) or [Arduino sketches](arduino). To learn more, please read the [documentation](docs/README.md).
