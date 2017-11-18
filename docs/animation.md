# Animation
Animations are dynamic color patterns displayed on a Section. Animations use a set of colors (called a `Palette`) to apply colors to individual Pixels. On each update, the Animation draws a new frame by calculating the color of each and every Pixel in the Section.

Animations consist of multiple stages called _cycles_. After a certain number of cycles (typically the same as the number of colors in the Palette), the Animation loops and starts over. Different animations have different cycle counts depending on their behavior: for example, `Solid` has one cycle (on), `Blink` has two cycles (on and off), and `Cycle` has a cycle count equal to the number of colors in the palette (one cycle per color).

## Contents
1. [Animation Types](#animation-types)
2. [Creating an Animation](#creating-an-animation)
	1. [Setting the Color Palette](#setting-the-color-palette)
	2. [Additional Options](#additional-options)
3. [Setting the Orientation](#setting-the-orientation)
4. [Changing the Animation Speed](#changing-the-animation-speed)
5. [Toggling Fading](#toggling-fading)

## Animation Types
The following animation types are available:
* Solid: Displays each color in the Palette.
* Blink: Switches between the Solid animation and off.
* Cycle: Cycles all Pixels through each of the colors stored in the Palette simultaneously.
* Wave: Similar to the Solid animation, only the Palette moves across the grid.
* Merge: Converges the Palette into the center of the Section.
* Random: Changes each Pixel to a random color in the Palette.
* Sparkle: Activates random Pixels and turns the rest off.
* Radial: Radiates the Palette from the center of the grid in a series of circles.
* Mandelbrot: Displays a [Mandelbrot set](https://en.wikipedia.org/wiki/Mandelbrot_set) with each color radiating from the center.
* Plasma: Displays a plasma effect.
* Lightning: Displays lightning bolts arcing from one end of the grid to the other.

## Creating an Animation
To create an animation, use `Section::set_animation()`, specifying the animation type and a color Palette.

```c++
#include "colorpresets.h"
#include "core/section.h"

Section section(10, 10);
Animation* animation = section.set_animation(AnimationType::Blink, ColorPresets::COLORWHEEL, 12);
``` 

Some animations (such as Sparkle) support the use of additional parameters. You can set these parameters by calling a method specific to that animation (e.g. `SparkleAnimation::set_threshold()`).

```c++
Section section(10, 10);
SparkleAnimation* animation = static_cast<SparkleAnimation*>(section.set_animation(AnimationType::Sparkle, ColorPresets::COLORWHEEL, 12));
animation->set_threshold(50);
``` 

### Setting the Color Palette
All animations require a color palette. The palette provides the set of colors that the animation uses for each of its cycles. You can set the palette when setting the animation or by using `Animation::set_colors()`.

The following example sets a palette of three colors: red, green, and blue. Depending on the animation, one of these colors (or a mix) will be displayed in each Pixel.
```c++
Colors::RGB colors[] = {Colors::RED, Colors::GREEN, Colors::BLUE};
animation->set_colors(colors, 3);
```

**Tip:** You can find pre-defined palettes in the `ColorPresets` class.

## Setting the Orientation
The orientation determines the direction (vertical or horizontal) that the Animation moves in. You can change the orientation using `Animation::set_orientation()`. Some Animations (such as Cycle) don't support orientations. Animations are horizontal by default.

```c++
Animation* animation = new WaveAnimation();
animation->set_orientation(Animation::Orientations::VERTICAL);
```

## Changing the Animation Speed
You can set the animation's speed via the `set_timing()` method. Speed is the amount of time (in milliseconds) between animation cycles. For example, an animation with 5 cycles and a speed of 100 will take 500ms (5 * 100) to finish, while the same animation with a speed of 500 will take 2500ms (5 * 500) to finish.

You can also set a pause interval. Pause is the amount of time (in milliseconds) that the cycle is delayed. For example, consider an Animation with a speed of 500ms and fading enabled. Normally the Animation would gradually fade over the course of the entire 500ms. But if you set a pause interval of 300ms, the Animation won't start fading until 300ms have passed. This results in the Animation "rushing" over the last 200ms. Pause only works while fading is enabled.

### Toggling Fading
By default, Pixels fade between color changes. Disabling fading causes color changes to occur instantly.
```c++
animation->set_fade(false);
```

[Home](README.md)
