# Pixel
A Pixel represents a single RGB output. It stores an RGB color value, a pointer to a target RGB value, and instructions on how to reach that target color during an animation. Pixels are normally not used by themselves without being included in a Section.

## Contents
1. [Creating Pixels](#creating-pixels)
2. [Animating Pixels](#animating-pixels)
3. [Updating Pixels](#updating-pixels)
4. [Common Methods](#common-methods)

## Creating Pixels
The following code creates a 1x10 line of Pixels and assigns it to a Section:
```c++
Point* grid_size = new Point(1, 10);
Pixel pixels[grid_size->x * grid_size->y];
Section section = new Section(&pixels[0], grid_size);
```

## Animating Pixels
Each Pixel stores three key bits of information: its `current_color_`, its `next_color_`, and its `step_` amount.

The `current_color_` is the color that the Pixel is displaying right now. This is the value that gets rendered to your output device and can be accessed using the `get_color()` method. This is also the value that gets updated when the Pixel's `update()` method is called.

The `next_color_` is the color that the Pixel will switch to on the next animation cycle. At the end of a cycle, the value of `current_color_` equals the value of `next_color_`.

When fading is enabled, `step_` is used to calculate the degree of change between the Pixel's `current_color_` and its `next_color_` at the start of each animation cycle. On each refresh, the `step_` amount is applied to the `current_color_`, which blends the Pixel in the direction of `next_color_`. The number of steps is tracked in `step_count_` and is equal to the animation cycle interval divided by the refresh rate.

## Updating Pixels
To update a Pixel, simply call the Pixel's `update()` method. This triggers a single refresh of the Pixel. A refresh tells the Pixel to move one step from its current color towards its target color. If fading is enabled, this adds blending to the Pixel's current color bringing it closer to its target color. If fading is not enabled, this causes the Pixel to immediately jump to its next color.

## Common methods
* `Pixel::get_color()`: Retrieves the Pixel's current RGB color value.
* `Pixel::set_next_color(Colors::RGB\* next_color, bool fade, unsigned short cycle_speed, unsigned short refresh_rate)`: Sets the next color for the Pixel. On update, the Pixel will switch from its current color to the target color. `fade` specifies whether the transition is instantaneous or smoothed out over time. `cycle_speed` is the amount of time until the Pixel moves from its `current_color_` to its `next_color_` (e.g. the amount of time to complete one animation cycle). `refresh_rate` is the number of times the Pixel will update before reaching its `next_color_` (only applies when fading is enabled).
* `Pixel::update()`: Calculates and applies the Pixel's current color. If fading is enabled, the Pixel will be set to some intermediate color based on the interval specified in `set_next_color()`. If fading is not enabled, the Pixel jumps immediately to `next_color_`.

[Home](README.md)
