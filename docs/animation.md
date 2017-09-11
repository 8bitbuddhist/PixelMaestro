# Animation
Animations are moving patterns displayed on a Section. At its core, an animation is a set of colors that change over time. Each time an animation is updated, it calculates new color values for each Pixel in a Section, then applies the color to its respective Pixel.

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
* SOLID: Displays the color palette without changing.
* BLINK: Displays the color palette and cycles it on and off.
* CYCLE: Cycles the grid through each of the colors stored in the palette.
* WAVE: Displays color palette as a wave moving across the Section.
* MERGE: Converges palette colors into the center of the Section.
* RANDOM: Changes each Pixel to a random color in the palette.
* SPARKLE: Randomly activates different Pixels.
* RADIAL: Displays palette colors radiating from the center of the grid.
* MANDELBROT: Displays a mandelbrot set.
* PLASMA: Displays a plasma effect.

## Creating an Animation
All animations are derived from the [Animations](src/animation/animation.h) class. To create an animation, import the desired animation class.

```c++
#include "animation/blinkanimation.h"

Section *section = new Section(new Point(10, 10));
Animation* blink_animation = new BlinkAnimation(section, Colors::COLORWHEEL, 12);
section->set_animation(blink_animation);
``` 

Some animations (such as SPARKLE) support the use of additional parameters. You can set these parameters in the animation's constructor.


### Setting the Color Palette
All animations require you to set a color palette. The palette provides a reference to all of the colors used during the animation. You can pass an array of colors during the animation constructor, or by using `Animation::set_colors()`.

The following example sets a palette of three colors: red, green, and blue. Depending on the animation, one of these colors (or a mix) will be displayed in each Pixel.
```c++
Colors::RGB *colors = {Colors::RED, Colors::GREEN, Colors::BLUE};
section.set_colors(colors, 3);
```

## Setting the Orientation
The orientation determines the direction (vertical or horizontal) that the animation travels in. Animations are horizontal by default, but some animations support a vertical orientation. You can change the orientation using `Animation::set_orientation()`.

```c++
// Declare new WaveAnimation
animation->set_orientation(Animation::Orientations::VERTICAL);
```

## Changing the Animation Speed
The speed of an animation is determined by the Section rather than the animation itself. There are two different counters: the refresh interval and the cycle interval. The refresh interval is the amount of time between Pixel redraws and only applies when fading is enabled. The cycle interval is the amount of time between animation updates. Both the refresh and cycle intervals are measured in milliseconds.

The following code refreshes the Section every 1/10th of a second and cycles the animation every 1/2 second. If fading is disabled, then only the cycle speed will factor into the animation.
```c++
section.set_refresh_interval(100);
section.set_cycle_interval(500);
```

### Toggling Fading
By default, Pixels fade between color changes. Disabling fading causes color changes to occur instantly.
```c++
animation->set_fade(false);
```

[Home](README.md)
