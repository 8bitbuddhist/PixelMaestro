# Pixel
A Pixel represents a single RGB output. It stores a color value, a pointer to a target color, and instructions on how to reach that target color. Pixels are normally not used by themselves without being included in a Section.

## Contents
1. [Creating Pixels](#creating-pixels)
2. [Animating Pixels](#animating-pixels)
3. [Updating Pixels](#updating-pixels)
4. [Common Methods](#common-methods)

## Creating Pixels
Pixels don't take any parameters.
```c++
Pixel pixel;
```

## Animating Pixels
Each Pixel stores three key bits of information: its `current_color_`, its `next_color_`, and its `step_` amount.

`current_color_` is the color that the Pixel is displaying right now. This can be accessed using `Section::get_pixel_color(x, y)` or `Maestro::get_pixel_color(section, x, y)`. This value also gets changed when the Pixel's `update()` method gets called.

`next_color_` points to the color that the Pixel will switch to on the next animation cycle. During an animation cycle, if fading is enabled, `current_color_` will gradually approach `next_color_` until the cycle is complete, at which point the RGB values of `current_color_` are set to those of `next_color_`. If fading is not enabled, `current_color_` will immediately jump to `next_color_` when starting the next cycle.

When fading, `step_` is used to calculate the amount of change between the Pixel's `current_color_` and its `next_color_` at the start of each animation cycle. On each refresh, the `step_` amount is applied to the `current_color_`, which blends the Pixel in the direction of `next_color_`. The number of steps is tracked in `step_count_` and is equal to the animation cycle interval divided by the refresh rate. This is not used when fading is disabled.

## Updating Pixels
Calling a Pixel's `update()` method triggers a single refresh of the Pixel. A refresh tells the Pixel to move one step from its current color towards its target color.

## Common methods
* `Pixel::get_color()`: Retrieves the Pixel's current RGB color value.
* `Pixel::set_next_color(Colors::RGB\* next_color, uint8_t step_count)`: Sets the next color for the Pixel. On update, the Pixel will switch from its current color to the target color. 
* `Pixel::update()`: Calculates and applies the Pixel's current color. If fading is enabled, the Pixel will be set to some intermediate color based on the interval specified in `set_next_color()`. If fading is not enabled, the Pixel jumps immediately to `next_color_`.

[Home](README.md)
