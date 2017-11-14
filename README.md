# PixelMaestro
PixelMaestro is a library for creating and rendering 2D animations and patterns. While originally designed for LEDs, it can be used to display animations on any device. To learn more about PixelMaestro, see the [included documentation](docs/README.md).

PixelMaestro comes with a companion GUI application called PixelMaestro Studio. PixelMaestro Studio lets you preview animations, customize and share configurations, control devices running PixelMaestro over USB, and more.

PixelMaestro does not interact directly with hardware. Instead, it acts as a buffer that you can copy color values from. You will need to use another library or write your own code to link the buffer to your output device. You can find examples using Arduino and popular LEDs in the [Arduino folder](arduino).

**Note:** PixelMaestro is alpha software. New releases may introduce incompatible changes.
