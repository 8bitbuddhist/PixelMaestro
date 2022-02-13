# PixelMaestro

![latest tag](https://img.shields.io/github/tag/8bitbuddhist/pixelmaestro.svg) ![license](https://img.shields.io/github/license/8bitbuddhist/pixelmaestro.svg)

PixelMaestro is a fully featured graphics library for creating dynamic 2D animations and patterns on low-power devices. It was originally designed for controlling LEDs using microcontrollers and SoC devices like Raspberry Pi, but can be used on almost any device for any size or type of display. PixelMaestro makes it easy to control LED colors, create animations, draw custom shapes or text, and even create fully automated shows.

PixelMaestro does not directly control LEDs like [NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) or [FastLED](https://github.com/FastLED/FastLED), but is meant to be used in combination with them. You use PixelMaestro to generate colors, then pass these colors to your LED library to send to your LEDs.

## Features

- True (24-bit) color depth
- Support for up to 256 independent and multi-layered LED matrices
- Support for layered animations (up to 256 layers per matrix)
- Over 10 unique, customizable animations with support for different orientations, speeds, and color schemes
- A raster graphics editing tool that supports still and animated bitmap images.
- A fully-featured scheduling system for creating LED shows
- Lightweight communications protocol for controlling remote devices over USB, Ethernet, Bluetooth, or other connection
- Microcontroller friendly: Use with Arduino, Raspberry Pi, ESP32, and other devices

## Getting Started

[Click here](https://8bitbuddhist.github.io/PixelMaestro/Tutorial.html) for a tutorial, or read the [documentation](https://8bitbuddhist.github.io/PixelMaestro/) for the full getting started guide.

For examples, see the [examples folder](examples/). For Arduino-specific examples, see the [Arduino examples](examples/arduino). You can use PixelMaestro with the [Arduino IDE](https://www.arduino.cc/en/Main/Software) or [PlatformIO](https://platformio.org/).

## Desktop App

[PixelMaestro Studio](https://github.com/8bitbuddhist/PixelMaestro-Studio) is the desktop companion application to PixelMaestro. It lets you visually manage animations, edit canvases, schedule shows, control devices over USB or network, and more. Binaries are available for Windows and Linux. [Click here](https://github.com/8bitbuddhist/PixelMaestro-Studio) to learn more.

## Running Tests

PixelMaestro uses the [Catch](https://github.com/catchorg/Catch2) framework to run tests. Compiling the test suite requires CMake 3.6.2 or higher.

1. Navigate to the `tests` folder.
2. Run `cmake .`
3. Navigate to the `bin` folder and run `PixelMaestro_Test`.

## Building Docs

Docs are built using Doxygen and Sphinx. To build docs:

1. Install doxygen
2. Run `pip install -r docsrc/requirements.txt`
3. Run `sphinx-build -b html docsrc/ docs/`