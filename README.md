# PixelMaestro
PixelMaestro is a set of classes for creating and rendering 2D animations and patterns. While originally designed for LEDs, it can be used to generate RGB values for any device or output.

## Structure
PixelMaestro is split into modular classes which can be used independently or combined to simplify management. There are four primary classes in order from lowest-level to highest-level:
* Pixel: A single RGB output. Provides limited functionality for changing colors.
* Line: Collection of multiple Pixels. Provides core functionality for animations.
* Grid: Collection of multiple Lines. Provides additional animations.
* Maestro: Collection of Lines and Grids.

There are also the following classes:
* Colors: Provides core utilities for managing colors including an RGB struct, several pre-defined colors and color schemes, and methods for generating new color collections.
* Show: Provides functionality for scheduling animation changes and other actions.

## Setup and Use
### Pixel
Simply declare a new Pixel() variable to begin using it. Pixels are normally not  used by themselves without being included in a Line or Grid. 

Common methods:
* Pixel::getColor(): Retrieves the Pixel's current RGB color value. This is the value that you would write to an LED controller.
* Pixel::setNextColor(Colors::RGB \*nextColor, bool fade, unsigned char interval): Sets the next color for the Pixel. On update, the Pixel will change from its current color to the target color. Fade specifies whether the transition is instantaneous or smoothed, while interval specifies how long the transition will take.

### Line
Constructor:
Line::Line(Pixel \*pixels, unsigned char numPixels, Colors::RGB \*colors, unsigned char numColors)

* pixels: An array of Pixels.
* numPixels: The number of Pixels in the array.
* colors: Optional. The initial array of colors to use as animations.
* numColors: Optional. The number of colors in the colors array.

Common methods:
* Line::getPixel(unsigned char index): Returns the Pixel at the index provided. Commonly used with Pixel::getColor() to return the Pixel's current color as output.
* Line::setColorAnimation(ColorAnimations animation, bool reverseAnimation): Changes the color animation and whether to reverse the animation.
* Line::setColors(Colors::RGB colors[], unsigned char numColors): Stores a set of colors in the strip for animations.
* Line::setSpeed(unsigned char speed): Changes the interval between color changes.
* Line::toggleFade(): Toggles whether to fade the Pixels during color transitions.
* Line::update(unsigned long currentTime): Updates the array. You will need to pass the current time in milliseconds.

### Grid
Constructor:
Matrix::Matrix(Line \*lines, unsigned char numLines)

* lines: An array of Lines with length specified by numLines.

Common methods:
* Grid::getLine(unsigned char row): Returns the Line at the specified row number. This is typically used with Line::getPixel()->getColor() to return color values stored by individual Pixels.

### Colors
Declare a new Color by using the RGB struct, e.g.
	Colors::RGB green = {0, 255, 0};

Common methods:
* Colors::generateScalingColorArray(Colors::RGB targetArray[], Colors::RGB baseColor, unsigned char threshold, unsigned char numColors): Generates a scaling array of colors based on the color specified in baseColor and the scale specified by threshold.
* Colors::HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val): Converts an HSV value into a Colors::RGB object. Useful for creating an RGB color from a potentiometer value.

### Other Functions
* Line::setAll(Colors::RGB color): Immediately sets all Pixels to the specified color.
* Line::setColor(unsigned char colorIndex, Colors::RGB color) Changes a color stored in the colors array.
* Line::setOne(unsigned char pixel, Colors::RGB color): Immediately changes the Pixel at the specified index to the specified color.
* Line::setPattern(unsigned char \*pattern, unsigned char patternLength): Stores an 8-bit pattern. Each pattern is a unsigned char value where each bit determines the on/off status of an individual Pixel.

## Color Animations
Line provides several pre-defined animations as specified in Line::ColorAnimations. Certain animations can also be displayed in reverse.
* NONE: Nothing is displayed.
* SOLID: Displays a solid color.
* BLINK: Cycles all Pixels between on and off.
* CYCLE, CYCLE_REVERSE: All Pixels cycle through the colors stored in the color array.
* WAVE, WAVE_REVERSE: Displays colors as a wave moving through the Pixels.
* PONG: Cycles the color array back and forth across the Pixels.
* MERGE, MERGE_REVERSE: Converges colors into the center of the Pixels (opposite effect for MERGE_REVERSE).
* RANDOMINDEX: Changes each Pixel to a random color stored in the array.
* SPARKLE: Quickly flashes a random Pixel on.
* PATTERN: Uses a unsigned char value to turn on/off specific Pixels.
