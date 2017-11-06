# Section
Sections are the bridges between the various PixelMaestro components. Their main function is to delegate colors to Pixels, but they also manage Animations, Canvases, and Overlays. A Section is essentially a set of Pixels controlled via a single interface.

Sections are managed by a [Maestro](maestro.md).

## Contents
1. [Creating a Section](#creating-a-section)
2. [Animating a Section](#animating-a-section)
3. [Displaying Custom Shapes and Patterns](#displaying-custom-shapes-and-patterns)
4. [Using Overlays](#using-overlays)
5. [Retrieving Pixels and Colors](#retrieving-pixels-and-colors)
	1. [Accessing Pixels by Index](#accessing-pixels-by-index)
	2. [Accessing Pixels by Coordinate](#accessing-pixels-by-coordinate)
6. [Updating a Section](#updating-a-section)
7. [Other Methods](#other-methods)

## Creating a Section
When creating a Section, pass the 2D layout of the Pixel grid (columns and rows) in the constructor.

```c++
Section section = Section(10, 10);
```
Alternatively:
```c++
Point dimensions(10, 10);
Section section = Section(dimensions);
```

You will need to assign the Section to a Maestro using `Maestro::set_sections(sections, num_sections)`. If you're only using one Section, you can fast-track this process by creating the Maestro using `Maestro(columns, rows)`.

## Animating a Section
You can display complex color animations on a Section. For more information, see the [Animation](animation.md) document.

## Displaying Custom Shapes and Patterns
You can draw custom shapes and patterns onto a Section using a Canvas. For more information, see the [Canvas](canvas.md) document.

## Using Overlays
You can combine different effects by adding an Overlay. An Overlay is a second Section layered on top of an existing Section. Both Sections run independently of each other, but when you retrieve a Pixel's color from the base Section, the base Section merges the color from the corresponding Overlay pixel.

**Tip:** You can learn more about color merging in the [Colors](colors.md) document.

Create an Overlay by calling `Section::set_overlay()`. You will need to specify the `MixMode` used to combine colors from the Overlay, and optionally an `alpha` value that determines how much the Overlay is blended with the base Section. This returns a new Overlay instance, which contains the Overlay's parameters and the Section used to control the Overlay. You can access the overlaid Section using `Section::get_overlay()->section`.

Since any Section can have an Overlay, you could theoretically stack an unlimited number of Overlays. For example, to add a second-level Overlay, call `Section::get_overlay()->section->set_overlay(mix_mode, alpha)`.

```c++
Section base = Section(10, 10);
...
// Creates a new Overlay and sets its animation.
// The final Pixel color will be 50% of the base color and 50% of the overlaid color.
Overlay* overlay = base.set_overlay(Colors::MixMode::ALPHA, 127);
overlay->section->set_animation(AnimationType::RadialAnimation, ColorPresets::COLORWHEEL, 12);
```

## Retrieving Pixels and Colors
At any given time, you can pull a Pixel's color value using the `get_pixel_color(index)` method, where `index` is the index of the Pixel in the array (demonstrated below in [Accessing the Pixel by Index](#accessing-the-pixel-by-index)). This takes the Pixel's raw color (set by an Animation), applies the Canvas and Overlay (if set), and returns an RGB value which you can send to your output device.

**Note:** If you'd rather access the Pixel by specifying its coordinate in the grid, see [Accessing the Pixel by Coordinate](#accessing-the-pixel-by-coordinate).

You can also retrieve a Pixel's color using the `Maestro::get_pixel_color(section, index)` method. You should use this method instead if you used `Maestro::set_brightness()` to set a global brightness level.

### Accessing Pixels by Coordinate
You can access a Pixel by its location on the 2D grid:
```c++
Pixel *pixel = section.get_pixel(50, 2);
```

## Updating a Section
To update a Section, call the `Section::update(runtime)` method. This updates the Section along with any objects managed by the Section including the active Animation, the Canvas, all Overlays, and each Pixel assigned to that Section. Calling `Maestro::update()` automatically calls this method for you.

```c++
section.update(runtime);
```

## Other Methods
* `Section::set_all(Colors::RGB\* color)`: Sets all Pixels to the specified color.
* `Section::set_one(unsigned int index, Colors::RGB\* color)`: Sets the Pixel at the specified array index to the specified color.

[Home](README.md)
