# PixelMaestro Arduino Sketches

This folder contains sample sketches for running PixelMaestro on an Arduino.

## Contents
- [Arduino IDE Installation](#arduino-ide-installation)
	- [Installing Library Dependencies](#installing-library-dependencies)
- [PlatformIO Installation](#platformio-installation)

## Arduino IDE Installation

1. Download the latest version of PixelMaestro from https://github.com/8bitbuddhist/PixelMaestro/releases by clicking the **Source Code (zip)** link.
2. In the Arduino IDE, click **Sketch > Include Library > Add .ZIP Library...** and select the downloaded ZIP file
3. Click **OK**.

You will now find example sketches demonstrating the use of PixelMaestro in the **File > Examples > PixelMaestro** menu.

### Installing Library Dependencies

The examples in the **NeoPixel** folder require the [Adafruit NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) library.

1. In the Arduino IDE, click **Sketch > Include Library > Manage Libraries...**
2. Once the download is finished, click the **Filter your search...** box and enter **adafruit neopixel single-wire**.
3. Select **Adafruit NeoPixel** and click **Install**.
4. After the installation is finished, click **Close**.

The examples in the **WS2812** folder require the [light_ws2812](https://github.com/cpldcpu/light_ws2812) library.

1. Download the library ZIP file from [GitHub](https://github.com/8bitbuddhist/light_ws2812/raw/pixelmaestro/light_ws2812_Arduino/light_WS2812.zip).
2. In the Arduino IDE, click **Sketch > Include Library > Add .ZIP Library...** and select the downloaded ZIP file.
3. Click **OK**.

## PlatformIO Installation

1. In PlatformIO, click **File > Open Folder...** and select this folder.
2. Copy the sketch that you want to upload to the **src/** folder.
3. Build and upload the project to your board.
