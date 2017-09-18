# Animation
Animations are moving patterns displayed on a Section. At its core, an animation is a set of colors that change over time. Each time an animation is updated, it calculates and applies new color values for each Pixel in the Section. A single update is called a _cycle_. Different animations have different cycle counts depending on their behavior: for example, SOLID has one cycle (on), BLINK has two cycles (on and off), and CYCLE has a cycle count equal to the number of colors (one cycle per color).

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
* LIGHTNING: Displays lightning bolts branching from one end of the grid to the other.

## Creating an Animation
All animations derive from the [Animations](src/animation/animation.h) class. To create an animation, import the relevant animation class and initialize the animation along with a color palette and optionally a speed. An animation _must_ have a color palette or it will not run.

```c++
#include "animation/blinkanimation.h"

Section section Section(10, 10);
Animation* blink_animation = new BlinkAnimation(Colors::COLORWHEEL, 12);
section->set_animation(blink_animation);
``` 

Some animations (such as SparkleAnimation) support the use of additional parameters. You can set these parameters in the Animation's constructor, or by calling a method (e.g. `SparkleAnimation::set_threshold()`).


### Setting the Color Palette
All animations require you to set a color palette. The palette provides a list of the colors that the animation can use during its cycle. You can set the palette in the constructor, or by using `Animation::set_colors()`.

The following example sets a palette of three colors: red, green, and blue. Depending on the animation, one of these colors (or a mix) will be displayed in each Pixel.
```c++
Colors::RGB *colors = {Colors::RED, Colors::GREEN, Colors::BLUE};
animation->set_colors(colors, 3);
```

## Setting the Orientation
The orientation determines the direction (vertical or horizontal) that some animations move in. Animations are horizontal by default. You can change the orientation using `Animation::set_orientation()`.

```c++
Animation* animation = new WaveAnimation();
animation->set_orientation(Animation::Orientations::VERTICAL);
```

## Changing the Animation Speed
You can set the animation's speed in the constructor or via the `set_speed()` method. Speed is the amount of time between animation updates measured in milliseconds. It's a bit of a misnomer, since it's actually the amount of time for the animation to finish. So for example, an animation with 5 cycles and a speed of 100 would take 500ms to finish, while the same animation with a speed of 500 would take 2500ms to finish.

### Toggling Fading
By default, Pixels fade between color changes. Disabling fading causes color changes to occur instantly.
```c++
animation->set_fade(false);
```

[Home](README.md)
