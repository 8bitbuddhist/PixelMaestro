# Pixel
A Pixel represents a single RGB output. It stores a single RGB color value, a pointer to a target RGB value, and instructions on how to reach that target color when it's animating. Pixels are normally not used by themselves without being included in a Section.

## Declaration
The following snippet creates a grid 10 Pixels long and assigns it to a Section:
```c++
int rows = 1;
int columns = 10;
Pixel pixels[rows * columns];
Section section;
section.setPixels(pixels, rows, columns);
```

## Updating the Pixel
To update the Pixel, simply call the Pixel's `update()` method. This triggers a single refresh of the Pixel.

## Common methods
* Pixel::getColor(): Retrieves the Pixel's current RGB color value.
* Pixel::setNextColor(Colors::RGB \*nextColor, bool fade, unsigned char interval): Sets the next color for the Pixel. On update, the Pixel will switch from its current color to the target color. Fade specifies whether the transition is instantaneous or smoothed out over time, while interval specifies how long the transition will take.
* Pixel::update(bool fade): Calculates and applies the Pixel's next color. If fade is true, this value will be some intermediate color based on your specified transition time.

[Home](Readme.md)
