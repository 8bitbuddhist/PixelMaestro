# Section
Sections manage a set of Pixels and the various PixelMaestro components that interact with Pixels. They manage and update Animations, Canvases, and Layers, while acting as a bridge between the Maestro and Pixels. Sections themselves are managed by a [Maestro](maestro.md).

## Contents
1. [Creating a Section](#creating-a-section)
2. [Animating a Section](#animating-a-section)
3. [Displaying Custom Shapes and Patterns](#displaying-custom-shapes-and-patterns)
4. [Using Layers](#using-layers)
5. [Scrolling](#scrolling)
	1. [Offsetting](#offsetting)
6. [Retrieving Pixels and Colors](#retrieving-pixels-and-colors)
7. [Updating a Section](#updating-a-section)
8. [Other Methods](#other-methods)

## Creating a Section
When creating a Section, pass the layout of its Pixel grid in the constructor:

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

## Using Layers
A Layer is a second Section placed on top of an existing Section. Both Sections run independently of each other, but when you retrieve a Pixel's color from the base Section, the base Section merges the color from the layered Pixel at the same coordinates. This lets you create complex layered effects.

**Tip:** You can learn more about color merging in the [Colors](colors.md) document.

Create a Layer by calling `Section::set_layer()`. You will need to specify the `MixMode` used to combine colors from the Layer, and optionally an `alpha` value which determines how much the Layer's colors are blended with the base's colors. This returns a new Layer instance, which contains the Layer's parameters and the new Section managed in the Layer. You can access the overlaid Section using `Section::get_layer()->section`.

Since any Section can have a Layer, you can theoretically stack an unlimited number of Layers by calling the Layer's `set_layer()` method. For example, to add three Layer levels, use `Section::set_layer()->section->set_layer()->section->set_layer()`.

```c++
Section base = Section(10, 10);
...
// Creates a new Layer and sets its animation.
// The final Pixel color will be 50% of the base color and 50% of the overlaid color.
Layer* layer = base.set_layer(Colors::MixMode::ALPHA, 127);
layer->section->set_animation(AnimationType::RadialAnimation, ColorPresets::COLORWHEEL, 12);
```

## Scrolling
Scrolling shifts the contents of the Section along the Pixel grid. Unlike other timing methods, scroll time is measured in terms of refresh cycles, e.g. a value of `2` means the Section will refresh twice before scrolling 1 pixel. Use `set_scroll()` to define the scroll rate along the x and y axes. When this value is positive, the Section scrolls to the left on the x-axis and up on the y-axis, otherwise it scrolls right on x and down on y.

Call `update_scroll()` to trigger a scroll. A scroll is also triggered automatically on each `update()` of the Section (i.e. on each Maestro update). Setting either axis to 0 disables scrolling on that axis. You can also stop scrolling by calling `remove_scroll()`, which completely disables all scrolling behavior.

**Note:** Disabling scrolling will stop the grid in its current location. If you want to move the grid back to the center, set its [offset](#offsetting) to 0.

The following code scrolls 1 Pixel to the left on every refresh cycle and 1 Pixel down every other refresh cycle.

```c++
section->set_scroll(1, -2);
```

### Offsetting
Scrolling works by modifying the Section's offset values. You can manually modify these values in order to shift the Section without having to automatically scroll it.

```c++
section->set_offset(5, 1);
```

**Note:** Offset will be disabled if scrolling is enabled, since scrolling uses the offset values.

## Retrieving Pixels and Colors
At any given time, you can pull a Pixel's color value using the `get_pixel_color(x, y)` method. This takes the Pixel's raw color, processes the Canvas and Layer (if set), and returns an RGB value which you can forward to your output device.

You can also retrieve a Pixel's color using the `Maestro::get_pixel_color(section, x, y)` method. You should use this method instead if you used `Maestro::set_brightness()` to set a global brightness level.

## Updating a Section
To update a Section, call the `Section::update(runtime)` method. This updates the Section along with any objects managed by the Section including the active Animation, the Canvas, all Layers, and each Pixel assigned to that Section. Calling `Maestro::update()` automatically calls this method for you.

```c++
section.update(runtime);
```

## Other Methods
* `Section::set_all(Colors::RGB\* color)`: Sets all Pixels to the specified color.
* `Section::set_one(unsigned int index, Colors::RGB\* color)`: Sets the Pixel at the specified array index to the specified color.

[Home](README.md)
