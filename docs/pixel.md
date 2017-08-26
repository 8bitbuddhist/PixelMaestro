# Pixel
A Pixel represents a single RGB output. It stores a single RGB color value, a pointer to a target RGB value, and instructions on how to reach that target color when it's animating. Pixels are normally not used by themselves without being included in a Section.

## Contents
1. [Creating a Pixel](#creating-a-pixel)
2. [Updating a Pixel](#updating-a-pixel)
3. [Common Methods](#common-methods)

## Creating a Pixel
The following snippet creates a grid 10 Pixels long and assigns it to a Section:
```c++
int rows = 1;
int columns = 10;
Pixel pixels[rows * columns];
Section section;
section.set_pixels(pixels, rows, columns);
```

## Updating a Pixel
To update the Pixel, simply call the Pixel's `update()` method. This triggers a single refresh of the Pixel. A refresh tells the Pixel to increment one step from its current color towards its target color. If fading is not enabled, this causes the Pixel to immediately jump to the color set in `set_next_color()`.

## Common methods
* `Pixel::get_color()`: Retrieves the Pixel's current RGB color value.
* `Pixel::set_next_color(Colors::RGB\* next_color, bool fade, unsigned char cycle_speed, unsigned char refresh_rate)`: Sets the next color for the Pixel. On update, the Pixel will switch from its current color to the target color. `fade` specifies whether the transition is instantaneous or smoothed out over time. `cycle_speed` is the total amount of time it will take the Pixel to go to the next color, while `refresh_rate` is the number of refreshes that the Pixel will undergo before reaching the next cycle. All of these are used during fading to calculate the Pixel's target color on each update.
* `Pixel::update()`: Calculates and applies the Pixel's next color. If fading is enabled, the Pixel will be set to some intermediate color based on the interval specified in `set_next_color()`.

[Home](README.md)
