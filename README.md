# PixelMaestro
PixelMaestro is a library for creating and rendering 2D animations and patterns. While originally designed for LEDs, it can be used to display animations on any device.

PixelMaestro comes with two components: the [core library](docs/README.md), and a desktop application called [PixelMaestro Studio](gui/README.md).

PixelMaestro does not interact directly with hardware. Instead, it acts as a buffer where color values are stored. You will have to use another library or wrapper to actually write from the buffer to the output device. You can find examples using Arduino in the [Arduino folder](arduino).

**Note:** PixelMaestro is alpha software. New releases may introduce incompatible changes.
