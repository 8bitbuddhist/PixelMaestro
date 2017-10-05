# Section
Sections are the core of PixelMaestro. Their main function is to delegate colors to Pixels. They are responsible for managing Animations, Canvases, Overlays, and other objects that impact the Pixel grid.

## Contents
1. [Creating a Section](#creating-a-section)
2. [Animating a Section](#animating-a-section)
3. [Displaying Custom Shapes and Patterns](#displaying-custom-shapes-and-patterns)
4. [Retrieving Pixels and Colors](#retrieving-pixels-and-colors)
	1. [Accessing Pixels by Index](#accessing-pixels-by-index)
	2. [Accessing Pixels by Coordinate](#accessing-pixels-by-coordinate)
5. [Using Overlays](#using-overlays)
6. [Updating a Section](#updating-a-section)
7. [Other Methods](#other-methods)

## Creating a Section
When creating a Section, pass the logical layout of the array (e.g. rows and columns) as part of the constructor.

```c++
Section section = Section(10, 10);
```
Alternatively:
```c++
Point dimensions(10, 10);
Section section = Section(dimensions);
```

## Animating a Section
Sections are primarily responsible for managing Animations. Their main purpose is to pass calculated color values from Animations to individual Pixels.

For more information, see the [Animation](animation.md) document.

## Displaying Custom Shapes and Patterns
You can draw custom shapes and patterns onto a Section using a Canvas. Different types of Canvases are available that interact with Sections in different ways.

For more information, see the [Canvas](canvas.md) document.

## Retrieving Pixels and Colors
At some point, you'll need to retrieve the color of a Pixel for output. You can do this using the `get_pixel_color(index)` method, where `index` is the index of the Pixel in the array (demonstrated below in [Accessing the Pixel by Index](#accessing-the-pixel-by-index)). This takes the Pixel's raw color, applies the Canvas and Overlay (if set), and returns a post-processed RGB value which you can send to your output.

**Note:** If you'd rather access the Pixel by specifying its coordinate in the grid, see [Accessing the Pixel by Coordinate](#accessing-the-pixel-by-coordinate).

You can also retrieve a Pixel's color by using the `Maestro::get_pixel_color(section, index)` method. You should use this method instead if you want to set a global brightness level using `Maestro::set_brightness()`.

### Accessing Pixels by Index
If you know the array index of the Pixel, you can use the `get_pixel(index)` method to retrieve the Pixel directly:
```c++
Pixel *pixel = section.get_pixel(100);
```

### Accessing Pixels by Coordinate
If you don't know the Pixel's array index, but you know where it lies on the 2D grid, you can access it by its row and column. The Section will translate these coordinates into the appropriate array index.
```c++
Pixel *pixel = section.get_pixel(50, 2);
```

## Using Overlays
You can layer animations by adding an Overlay to a Section. An Overlay is a second Section layered on top of an existing Section, with both Sections running independently of each other. When you retrieve a Pixel's color from the base Section using `get_pixel_color()`, the color from the base Section is merged with the color of the corresponding Pixel in the overlaid Section. You can learn more about color merging in the [Colors](colors.md) document.

Create an Overlay by calling `Section::set_overlay()`. This returns a new Overlay object, which contains the Section used to render the Overlay as well as methods for rendering the Section over its parent Section. You can access the overlaid Section by calling `Section::get_overlay()->section`.

Since any Section can have an Overlay, you could theoretically stack an unlimited number of Overlays. For example, to add a second-level Overlay, call `Section::get_overlay()->section->set_overlay()`.

```c++
Section base = Section(10, 10);
...
// Creates a new Overlay and sets its animation.
// The final Pixel color will be 50% of the base color and 50% of the overlaid color.
Overlay* overlay = base.set_overlay(overlay, Colors::MixMode::ALPHA, 127);
overlay->section->set_animation(new RadialAnimation(Colors::RAINBOW, 7));
```

## Updating a Section
To update a Section, call the `Section::update(runtime)` method. This updates the Section along with any objects managed by the Section including the active Animation, the Canvas, all Overlays, and every Pixel assigned to that Section. You don't need to call this method directly since calling `Maestro::update()` automatically calls this method for you.

```c++
section.update(runtime);
```

## Other Methods
* `Section::get_pixel_index(unsigned short x, unsigned short y)`: Translates a Pixel's x and y coordinates into its index in the Pixel array. This method also accepts a Point.
* `Section::set_all(Colors::RGB\* color)`: Sets all Pixels to the specified color.
* `Section::set_one(unsigned int index, Colors::RGB\* color)`: Sets the Pixel at the specified array index to the specified color.

[Home](README.md)
