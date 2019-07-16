# PixelMaestro Arduino Sketches

This folder contains sample sketches for running PixelMaestro on an Arduino.

## Contents
- [Arduino IDE Installation](#arduino-ide-installation)
	- [Installing Library Dependencies](#installing-library-dependencies)
- [PlatformIO Installation](#platformio-installation)

## Arduino IDE Installation

1. In the Arduino IDE, click **Sketch > Include Library > Manage Libraries...**
2. Once the download is finished, click the **Filter your search...** box and enter **pixelmaestro**.
3. Select **PixelMaestro** and click **Install**.
4. After the installation is finished, click **Close**.

You can find example sketches demonstrating the use of PixelMaestro in the **File > Examples > PixelMaestro** menu.

### Installing Library Dependencies

These examples use the [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) library. Repeat steps 1-4 above, but search for **adafruit neopixel single-wire** instead.

## PlatformIO Installation

1. In PlatformIO, click **File > Open Folder...** and select this folder.
2. Copy the sketch that you want to upload to the **src/** folder.
3. Build and upload the project to your board. PlatformIO will automatically download dependencies during the build.
