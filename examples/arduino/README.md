# PixelMaestro Arduino Sketches
This folder contains sample Arduino sketches. These sketches were created using [PlatformIO](http://platformio.org/).

## Configuring PlatformIO
1. Open this folder in PlatformIO.
2. Download any necessary libraries using the PlatformIO package manager.
3. Copy the sketch you want to upload to the `src/` folder.
4. Check that the `src/PixelMaestro` folder links to the PixelMaestro `src/` folder. If not, create a link or copy the PixelMaestro `src/` folder into this folder.
5. Build and upload the project to your board.

## Arduino IDE installation
1. Download the latest version of PixelMaestro from https://github.com/8bitbuddhist/PixelMaestro/releases by clicking the **Source Code (zip)** link.
2. (In the Arduino IDE) Sketch > Include Library > Add .ZIP Library... > select the downloaded file > Open

You will now find example sketches demonstrating the use of PixelMaestro in the **File > Examples > PixelMaestro** menu.
### Installing library dependencies
Adafruit Neopixel (required for the **File > Examples > PixelMaestro > NeoPixel** examples):
1. (In the Arduino IDE) Sketch > Include Library > Manage Libraries...
2. Wait for the download to finish.
3. In the "Filter your search..." box, type "adafruit neopixel single-wire".
4. Click on "Adafruit NeoPixel".
5. Click "Install".
6. Wait for installation to finish.
7. Click "Close".

light_WS2812 (required for the **File > Examples > PixelMaestro > WS2812** examples):
1. Download https://github.com/8bitbuddhist/light_ws2812/raw/pixelmaestro/light_ws2812_Arduino/light_WS2812.zip
2. (In the Arduino IDE) Sketch > Include Library > Add .ZIP Library... > Select the downloaded file > Open
