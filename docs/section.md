# Section
Sections manage a set of Pixels and the various PixelMaestro components that interact with Pixels. They manage and update Animations, Canvases, and Layers, while acting as a bridge between the Maestro and Pixels. Sections themsevles are managed by a [Maestro](maestro.md).

## Contents
1. [Creating a Section](#creating-a-section)
2. [Animating a Section](#animating-a-section)
3. [Displaying Custom Shapes and Patterns](#displaying-custom-shapes-and-patterns)
4. [Using Layers](#using-layers)
5. [Retrieving Pixels and Colors](#retrieving-pixels-and-colors)
6. [Updating a Section](#updating-a-section)
7. [Other Methods](#other-methods)

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
An Layer is a second Section layered on top of an existing Section. Both Sections run independently of each other, but when you retrieve a Pixel's color from the base Section, the base Section merges the color from the corresponding Layer pixel. This lets you create complex layered effects.

**Tip:** You can learn more about color merging in the [Colors](colors.md) document.

Create an Layer by calling `Section::set_layer()`. You will need to specify the `MixMode` used to combine colors from the Layer, and optionally an `alpha` value that determines how much the Layer is blended with the base Section. This returns a new Layer instance, which contains the Layer's parameters and the Section used to control the Layer. You can access the overlaid Section using `Section::get_layer()->section`.

Since any Section can have an Layer, you can theoretically stack an unlimited number of Layers by calling each Layer's `set_layer()` method. For example, to add three Layer levels, call `Section::get_layer()->section->set_layer()->section->set_layer()`.

```c++
Section base = Section(10, 10);
...
// Creates a new Layer and sets its animation.
// The final Pixel color will be 50% of the base color and 50% of the overlaid color.
Layer* layer = base.set_layer(Colors::MixMode::ALPHA, 127);
layer->section->set_animation(AnimationType::RadialAnimation, ColorPresets::COLORWHEEL, 12);
```

## Retrieving Pixels and Colors
At any given time, you can pull a Pixel's color value using the `get_pixel_color(x, y)` method. This takes the Pixel's raw color (set by an Animation), applies the Canvas and Layer (if set), and returns an RGB value which you can forward to your output device.

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
