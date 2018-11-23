# PixelMaestro

![latest tag](https://img.shields.io/github/tag/8bitbuddhist/pixelmaestro.svg) ![license](https://img.shields.io/github/license/8bitbuddhist/pixelmaestro.svg)

PixelMaestro is a graphics library for LED displays. It lets you create dynamic, colorful 2D animations and patterns on any size display. Originally designed for Arduinos, PixelMaestro can be used to drive any kind of LEDs on any device.

## Contents
<!-- TOC START min:2 max:5 link:true update:false -->
- [Getting Started](#getting-started)
  - [Installation](#installation)
  - [Using PixelMaestro](#using-pixelmaestro)
- [Companion App](#companion-app)
- [Running Tests](#running-tests)
- [Donate](#donate)
<!-- TOC END -->

## Getting Started

[Click here](https://github.com/8bitbuddhist/PixelMaestro/wiki/Tutorial) for a tutorial on using PixelMaestro, or read the [documentation](https://github.com/8bitbuddhist/PixelMaestro/wiki).

If you want to run PixelMaestro on an Arduino, you can do so via the [Arduino IDE](https://www.arduino.cc/en/Main/Software) or [PlatformIO](https://platformio.org/). For detailed instructions, see the [examples folder](examples/arduino).

## Companion App

PixelMaestro has a companion desktop application called PixelMaestro Studio. PixelMaestro Studio lets you create custom animations, save and share configurations, control devices over USB, and more. [Click here](https://github.com/8bitbuddhist/PixelMaestro-Studio) to learn more about PixelMaestro Studio.

## Running Tests

PixelMaestro uses the [Catch](https://github.com/catchorg/Catch2) framework to run tests. Compiling the test suite requires CMake 3.6.2 or higher.

1. Navigate to the `tests` folder.
2. Run `cmake .`
3. Navigate to the `bin` folder and run `PixelMaestro_Test`.
