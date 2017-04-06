# PixelMaestro
PixelMaestro is a set of classes for creating and rendering 2D animations and patterns. While originally designed for LEDs, it can be used to generate RGB values for any device or output.

## Structure
PixelMaestro is split into modular classes which can be used independently or combined to simplify management. There are four primary classes in order from lowest-level to highest-level:
* Pixel: A single RGB output. Provides limited functionality for changing colors.
* Section: Collection of multiple Pixels. Provides core functionality for animating Pixels.
* Maestro: Collection of Sections. Handles synchronized updating of multiple Sections.

There are also the following classes:
* Colors: Provides core utilities for managing colors including an RGB struct, several pre-defined colors and color schemes, and methods for generating new colors and color arrays.
* Show: Allows you to schedule animation changes and other actions to be performed by a Section. These changes are triggered at points that you determine over the course of the program's runtime.

## Setup and Use
### Pixel
Simply declare a new Pixel() variable to begin using it. Pixels are normally not  used by themselves without being included in a Section. 

#### Common methods:
* Pixel::getColor(): Retrieves the Pixel's current raw RGB color value.
* Pixel::setNextColor(Colors::RGB \*nextColor, bool fade, unsigned char interval): Sets the next color for the Pixel. On update, the Pixel will switch from its current color to the target color. Fade specifies whether the transition is instantaneous or smoothed out over time, while interval specifies how long the transition will take.
* Pixel::update(bool fade): Calculates and applies the Pixel's next color. If fade is true, this value will be some intermediate color based on your specified transition time.

### Section
Sections are the primary interface for PixelMaestro. They manage a collection of Pixels as a logical 2D grid.
Constructor:
Section::Section(Pixel \*pixels, unsigned short rows, unsigned short columns)

* pixels: An array of Pixels.
* rows: The number of logical rows of Pixels.
* columns: The number of logical columns of Pixels.

#### Common methods:
* Section::getPixel(unsigned short row, unsigned short column): Returns the Pixel at the specified row and column. There is also an overloaded method that accepts the index of the desired Pixel.
* Section::setColorAnimation(ColorAnimations animation, bool reverseAnimation): Specifies the color animation to use and whether the animation should run in reverse (only for certain animations).
* Section::setColors(Colors::RGB \*colors, unsigned int numColors): Stores a set of colors. These colors are used by the animations to create different visual effects.
* Section::setOverlay(Overlay overlay): Allows you to add another Section to the current Section as a layer. You can tweak the transparency of the layer to combine and create new visual effects.
* Section::setSpeed(unsigned char speed): Sets the interval between color changes.
* Section::toggleFade(): Toggles whether to fade Pixels during color transitions.
* Section::update(unsigned long currentTime): Updates the Section and all of its Pixels. You will need to pass the current time in milliseconds.

#### Other Methods
* Section::setAll(Colors::RGB color): Immediately sets all Pixels to the specified color.
* Section::setOne(unsigned int row, unsigned int column, Colors::RGB color): Immediately changes the Pixel at the specified index to the specified color. There is also an overloaded method that accepts the index of the desired Pixel.
* Section::setPattern(unsigned char \*pattern, unsigned char patternLength): Stores an 8-bit pattern. Each pattern is a unsigned char value where each bit determines the on/off status of an individual Pixel.

#### Color Animations
Section provides several pre-defined animations as specified in Section::ColorAnimations. Certain animations can also be displayed in reverse.
* NONE: Nothing is displayed.
* SOLID: Displays a solid color.
* BLINK: Cycles all Pixels between on and off.
* CYCLE (reversible): All Pixels cycle through the colors stored in the color array.
* WAVE (reversible): Displays colors as a wave moving across the Section.
* PONG (reversible): Moves a wave of colors back and forth across the Section.
* MERGE (reversible): Converges colors into the center of the Section.
* RANDOMINDEX: Changes each Pixel to a random color stored in the array.
* SPARKLE: Quickly flashes a random Pixel on.
* PATTERN: Uses a unsigned char value to turn on/off specific Pixels.

### Colors
Contains pre-defined colors, color arrays, and color generation methods. Declare a new Color by using the Colors::RGB struct, e.g.
	Colors::RGB green = {0, 255, 0};
You can directly add, subtract, and compare RGBs using the overloaded operators.

#### Common methods:
* Colors::generateScalingColorArray(Colors::RGB targetArray[], Colors::RGB baseColor, unsigned char threshold, unsigned char numColors): Generates a scaling array of colors based on the color specified in baseColor. Threshold is used to generate a target color and is the difference in RGB values from baseColor.
* Colors::HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val): Converts an HSV value into a Colors::RGB object.
* Colors::mixColors(RGB \*colorOne, RGB \*colorTwo, MixMode mode, float alpha = 0): Blends two colors together using the specified blending mode. Alpha specifies the transparency level of colorTwo.
