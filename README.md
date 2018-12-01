# PixelMaestro

![latest tag](https://img.shields.io/github/tag/8bitbuddhist/pixelmaestro.svg) ![license](https://img.shields.io/github/license/8bitbuddhist/pixelmaestro.svg)

PixelMaestro is a graphics library for LED displays. It lets you create dynamic, colorful 2D animations and patterns on any size display. Originally designed for Arduinos, PixelMaestro can be used to drive any kind of LED on any device.

## Features

- True (24-bit) color depth
- Support for up to 256 independent, multi-layered drawing surfaces
- Over 10 uniquely customizable animations with support for various orientations, speeds, and color schemes
- Powerful raster image editing tools with support for still or animated images
- Lightweight and flexible communications protocol for controlling devices over USB, Bluetooth, or other serial channel
- Runs in under 2KB of RAM and uses under 32KB of storage

## Getting Started

[Click here](https://github.com/8bitbuddhist/PixelMaestro/wiki/Tutorial) for a tutorial on using PixelMaestro, or read the [documentation](https://github.com/8bitbuddhist/PixelMaestro/wiki).

If you want to run PixelMaestro on an Arduino, you can do so via the [Arduino IDE](https://www.arduino.cc/en/Main/Software) or [PlatformIO](https://platformio.org/). For detailed instructions, see the [examples folder](examples/arduino).

## Companion App

PixelMaestro has a companion desktop application called PixelMaestro Studio. PixelMaestro Studio lets you design custom animations, save and share configurations, control devices over USB, and more. [Click here](https://github.com/8bitbuddhist/PixelMaestro-Studio) to learn more about PixelMaestro Studio.

## Running Tests

PixelMaestro uses the [Catch](https://github.com/catchorg/Catch2) framework to run tests. Compiling the test suite requires CMake 3.6.2 or higher.

1. Navigate to the `tests` folder.
2. Run `cmake .`
3. Navigate to the `bin` folder and run `PixelMaestro_Test`.
