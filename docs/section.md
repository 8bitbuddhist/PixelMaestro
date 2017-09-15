# Section
Sections are the primary interface for PixelMaestro. Their main function is to bridge Pixels and Animations. More specifically, they send colors to and from Pixels based on the current running animation.

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
Section *section = new Section(new Point(rows, columns));
```

## Animating a Section
The main purpose of a Section is to render Animations. It does this by taking calculated color values from the Animation and passing them to individual Pixels. The Section is responsible for managing the speed at which Animations update, but is otherwise unaware of the underlying Animation logic.

For more information, see the [Animation](animation.md) document.

## Displaying Custom Shapes and Patterns
Sections can also display Canvases. A Canvas lets you "draw" shapes, which are then rendered on top of the Section's Animation.

For more information, see the [Canvas](canvas.md) document.

## Retrieving Pixels and Colors
At some point, you'll need to retrieve the color of a Pixel for output. You can do this using the `get_pixel_color(index)` method, where `index` is the index of the Pixel in the array (demonstrated below in [Accessing the Pixel by Index](#accessing-the-pixel-by-index)). If you'd rather access the Pixel by specifying its coordinate in the grid, see [Accessing the Pixel by Coordinate](#accessing-the-pixel-by-coordinate).

You can also retrieve a Pixel's color by using the `Maestro::get_pixel_color(section, index)` method. You should use this method instead if you have set a global brightness level in the Maestro.

### Accessing Pixels by Index
If you know the array index of the Pixel, you can use the `get_pixel(index)` method to retrieve the Pixel directly:
```c++
Pixel *pixel = section.get_pixel(100);
```

### Accessing Pixels by Coordinate
If you don't know the Pixel's array index, but you know where it lies in the logical 2D grid, you can access it by its row and column. The Section will translate these coordinates into the appropriate array index.
```c++
Pixel *pixel = section.get_pixel(50, 2);
```

## Using Overlays
You can add a second layer to your animations by merging the output of one Section with the current Section. This requires two sections, two Color arrays (one for each section), and two Pixel arrays (one for each Section). The layering is performed by merging the color of a Pixel in the base Section with its corresponding Pixel in the target Section.

You can stack multiple Overlays by calling `base.get_overlay()->section->add_overlay()`.

You can learn more about merging colors in the [Colors](colors.md) document.

```c++
// Initialize Sections base and overlay
base.add_overlay(overlay, Colors::MixMode::NORMAL);
```

## Updating a Section
To update a Section, call the `update()` method. You will need to pass in the program's current runtime in milliseconds. More than likely, you will update a Section by calling its Maestro's `update()` method, which automatically the Section and all other Sections.

```c++
section.update(runtime);
```

## Other Methods
* `Section::get_pixel_index(unsigned short x, unsigned short y)`: Translates a Pixel's x and y coordinates into its index in the Pixel array. This method also accepts a Point.
* `Section::set_all(Colors::RGB\* color)`: Sets all Pixels to the specified color.
* `Section::set_one(unsigned int index, Colors::RGB\* color)`: Sets the Pixel at the specified array index to the specified color.

[Home](README.md)
