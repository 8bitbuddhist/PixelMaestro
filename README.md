# PixelMaestro

![latest tag](https://img.shields.io/github/tag/8bitbuddhist/pixelmaestro.svg) ![license](https://img.shields.io/github/license/8bitbuddhist/pixelmaestro.svg)

PixelMaestro is a graphics library for LED displays. It lets you create dynamic, colorful 2D animations and patterns on any size display. Originally designed for Arduinos, PixelMaestro can be used to drive any kind of display on any kind of device.

## Contents
<!-- TOC START min:2 max:5 link:true update:false -->
- [Getting Started](#getting-started)
  - [Installation](#installation)
  - [Example](#example)
- [Running Tests](#running-tests)
- [Companion App](#companion-app)
- [Donate](#donate)
<!-- TOC END -->

## Getting Started

These instructions will walk you through downloading PixelMaestro, adding it to your project, and including it in your code.

To use PixelMaestro with an Arduino or other embedded device, download and install [PlatformIO](https://platformio.org/). You can find detailed instructions on setting up PixelMaestro in PlatformIO in the [examples folder](examples/arduino).

### Installation

Clone this repository to your local machine and copy or link to the `src` folder from your project.

For use with an Arduino, see the [Arduino Readme](examples/arduino/README.md).

### Tutorial

[Click here](#Tutorial) for a brief introductory walkthrough of using PixelMaestro.

## Running Tests

PixelMaestro uses the [Catch](https://github.com/catchorg/Catch2) framework to run tests. Compiling the test suite requires CMake 3.6.2 or higher.

1. Navigate to the `tests` folder.
2. Run `cmake .`
3. Navigate to the `bin` folder and run `PixelMaestro_Test`.

## Companion App

PixelMaestro has a companion desktop application called PixelMaestro Studio. PixelMaestro Studio lets you mix animations in real-time, save and share configurations, control devices over USB, and more. [Click here](https://github.com/8bitbuddhist/PixelMaestro-Studio) to learn more about PixelMaestro Studio.

## Donate

If you find this project useful, cool, or just plain interesting, consider [making a donation](https://www.patreon.com/bePatron?c=1348704).
