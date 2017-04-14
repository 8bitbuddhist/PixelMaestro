# PixelMaestro
PixelMaestro is a library for creating and rendering 2D animations and patterns. PixelMaestro works by manipulating the color values of Pixels, or individual color points, using customizable animations. While originally designed for LEDs, it can be used to generate RGB values for any device or output.

## Structure
PixelMaestro is split into five components:
* Pixel: A single RGB output.
* Section: A collection of multiple Pixels. Provides the core functionality for animating Pixels.
* Maestro: A collection of Sections. Handles the synchronization and updating of one or more Sections.

PixelMaestro includes the following utility classes:
* Colors: Provides core utilities for managing colors including an RGB struct, several pre-defined colors and color schemes, and methods for generating new colors and color arrays.
* Show: Allows you to schedule animation changes and other actions to be performed by a Maestro. These changes are triggered over the course of the program's runtime.

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
* Section::setCycleSpeed(unsigned short speed, unsigned short pause): Sets the interval between animation changes. Pause creates a delay between when the subsequent change begins.
* Section::setOverlay(Section \*section, Colors::MixMode mixMode, float alpha): Adds another Section on top of the current Section as a visual layer. Specify a blend mode and alpha level to create new visual effects.
* Section::setRefreshRate(unsigned short refreshRate): Specifies how often the Section is redrawn in milliseconds.
* Section::toggleFade(): Toggles whether to fade Pixels during color transitions.
* Section::update(unsigned long currentTime): Updates the Section and all of its Pixels.

#### Other Methods
* Section::getPixelIndex(unsigned short row, unsigned short column): Returns the actual index of the Pixel given a row and column number.
* Section::setAll(Colors::RGB \*color): Sets all Pixels to the specified color.
* Section::setOne(unsigned short row, unsigned short column, Colors::RGB *color): Sets the Pixel at the specified row and column number to the specified color.
* Section::setPattern(unsigned long \*pattern, unsigned short patternRows, unsigned short patternFrames): Stores a bitmasked pattern. A pattern is a series of integers, each corresponding to a row, with a bitmask for each column. You can store multiple Patterns (called frames) in a single array which the Section will cycle through.

#### Color Animations
Section provides several pre-defined animations as specified in Section::ColorAnimations. You can reverse any animation by passing true as a second argument to Section::setColorAnimation().
* NONE: Nothing is displayed.
* SOLID: Displays a solid color.
* BLINK: Cycles all Pixels between on and off.
* CYCLE: All Pixels cycle through the colors stored in the color array.
* WAVE: Displays colors as a wave moving across the Section.
* PONG: Moves a wave of colors back and forth across the Section.
* MERGE: Converges colors into the center of the Section.
* RANDOMINDEX: Changes each Pixel to a random color stored in the array.
* SPARKLE: Quickly flashes a random Pixel on.
* PATTERN: Displays a user-defined pattern.

### Colors
Contains pre-defined colors, color arrays, and color generation methods. Declare a new Color by using the Colors::RGB struct, e.g.
	Colors::RGB green = {0, 255, 0};

#### Common methods:
* Colors::generateScalingColorArray(RGB newArray[], RGB baseColor, unsigned int numColors, unsigned char threshold): Generates a scaling array of colors based on the color specified in baseColor. Threshold is used to generate a target color and is the difference in RGB values from baseColor.
* Colors::HSVtoRGB(unsigned int hue, unsigned int sat, unsigned int val): Converts an HSV value into an RGB.
* Colors::mixColors(RGB \*colorOne, RGB \*colorTwo, MixMode mode, float alpha = 0): Blends two colors together using the blending mode specified by mode.
