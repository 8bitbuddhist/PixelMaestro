# PixelMaestro
This is a set of Arduino classes for creating and rendering 2D patterns on RGB LEDs.

# Use
PixelMaestro provides a set of methods for generating RGB values primarily to display patterns on an LED. The library is split into four classes:
* LED: manages an individual LED.
* Line: manages several LEDs as an LED strip or array.
* Matrix: manages several Lines as a grid or matrix.
* Colors: provides utilities for managing colors. Includes an RGB struct, several pre-defined colors and color schemes, and methods for generating collections of new colors.
Each class can be used independently. Higher-level classes (e.g. Matrix) automatically include all lower-level classes (e.g. Line). All classes include Colors by default.

## Setup
### LED
Typically LEDs are not used without being declared as part of a Line or Matrix. However, you can simply declare a new LED variable and use the setNextColor(), update(), and getColor() methods to manage the LED yourself.

### Line
Line::Line(LED \*leds, unsigned char numLEDs, Colors::RGB \*colors, unsigned char numColors)

* leds: An array of LEDs with length specified by numLEDS.
* numLEDs: The number of LEDs in the strip.
* colors: Optional. The initial array of colors to use as animations.
* numColors: Optional. The number of colors in the colors array.

### Matrix
Matrix::Matrix(Line \*lines, unsigned char numLines)

* lines: An array of Lines with length specified by numLines.

# Common Functions
## LED
* LED::getColor(): Retrieves the LED's current RGB color value. This is the value that you write to the LED controller.

## Line
* Line::getLED(unsigned char index): Returns the LED at the index provided. Commonly used with LED::getColor() to return the LED's current color for writing to the actual LED.
* Line::setColorAnimation(ColorAnimations animation, bool reverseAnimation): Changes the color animation and whether to reverse the animation.
* Line::setColors(Colors::RGB colors[], unsigned char numColors): Stores a set of colors in the strip for animations.
* Line::setSpeed(unsigned char speed): Changes the interval between color changes.
* Line::toggleFade(): Toggles whether to fade the LEDs during color transitions.
* Line::update(unsigned long currentTime): Updates the array. You will need to pass the current time in milliseconds.

## Matrix
* Matrix::getLine(unsigned char row): Returns the Line at the specified row number. This is typically used with Line::getLED()->getColor() to return color values stored by individual LEDs.
* Matrix::update(unsigned long currentTime): Updates the matrix. You will need to pass the current time in milliseconds.

## Colors
* Colors::generateScalingColorArray(Colors::RGB targetArray[], Colors::RGB baseColor, unsigned char threshold, unsigned char numColors): Generates a scaling array of colors based on the color specified in baseColor and the scale specified by threshold.
* Colors::HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val): Converts an HSV value into a Colors::RGB object. Useful for creating an RGB color from a potentiometer value.

## Other Functions
* Line::setAll(Colors::RGB color): Immediately sets all LEDs to the provided color.
* Line::setColor(unsigned char colorIndex, Colors::RGB color) Changes a color stored in the colors array.
* Line::setOne(unsigned char led, Colors::RGB color): Immediately changes the LED at the specified index to the specified color.
* Line::setPattern(unsigned char \*pattern, unsigned char patternLength): Stores an 8-bit pattern. Each pattern is a unsigned char value where each bit determines the on/off status of an individual LED.

# Color Animations
Line provides several pre-defined animations as specified in Line::ColorAnimations. Certain animations can also be displayed in reverse.
* NONE: Nothing is displayed.
* SOLID: Displays a solid color.
* BLINK: Cycles all LEDs between on and off.
* CYCLE, CYCLE_REVERSE: All LEDs cycle through the colors stored in the color array.
* WAVE, WAVE_REVERSE: Displays colors as a wave moving through the LEDs.
* PONG: Cycles the color array back and forth across the LEDs.
* MERGE, MERGE_REVERSE: Converges colors into the center of the LEDs (opposite effect for MERGE_REVERSE).
* RANDOMINDEX: Changes each LED to a random color stored in the array.
* SPARKLE: Quickly flashes a random LED on.
* PATTERN: Uses a unsigned char value to turn on/off specific LEDs.
