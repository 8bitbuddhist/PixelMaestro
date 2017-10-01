# Animation
Animations are moving patterns displayed on a Section. Animations dictate the color output of each Pixel based on the type of Animation and how long the Animation has been running. Each time an Animation is updated, it recalculates each Pixel's position in the Animation and assigns it the appropriate color from a palette.

Animations are broken down into stages called _cycles_. After a certain number of cycles (typically the same as the number of colors in the color palette), the Animation loops and starts over. Different animations have different cycle counts depending on their behavior: for example, `Solid` has one cycle (on), `Blink` has two cycles (on and off), and `Merge` has a cycle count equal to the number of colors in the palette (one cycle per color).

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
* Solid: Displays the color palette.
* Blink: Switches between showing the color palette and showing nothing.
* Cycle: Cycles the grid through each of the colors stored in the palette.
* Wave: Displays the color palette as a wave moving across the Section.
* Merge: Converges the palette into the center of the Section.
* Random: Changes each Pixel to a random color in the palette.
* Sparkle: Randomly activates different Pixels.
* Radial: Displays palette colors radiating from the center of the grid.
* Mandelbrot: Displays a mandelbrot set.
* Plasma: Displays a plasma effect.
* Lightning: Displays lightning bolts branching from one end of the grid to the other.

## Creating an Animation
All animations derive from the [base Animation class](src/animation/animation.h). To create an animation, import the relevant animation class and initialize the animation along with a color palette and optionally a speed. An animation _must_ have a color palette or it will not run.

```c++
#include "animation/blinkanimation.h"

Section section Section(10, 10);
Animation* blink_animation = new BlinkAnimation(Colors::COLORWHEEL, 12);
section->set_animation(blink_animation);
``` 

Some animations (such as Sparkle) support the use of additional parameters. You can set these parameters in the Animation's constructor, or by calling a method specific to that animation (e.g. `SparkleAnimation::set_threshold()`).


### Setting the Color Palette
All animations require you to set a color palette. The palette provides a set of colors that the animation uses for each of its cycles. You can set the palette in the constructor or by using `Animation::set_colors()`.

**Note:** The Animation copies the palette into a new buffer, so the source does not need to be persistent.

The following example sets a palette of three colors: red, green, and blue. Depending on the animation, one of these colors (or a mix) will be displayed in each Pixel.
```c++
Colors::RGB colors[] = {Colors::RED, Colors::GREEN, Colors::BLUE};
animation->set_colors(colors, 3);
```

## Setting the Orientation
The orientation determines the direction (vertical or horizontal) that animations move in. You can change the orientation using `Animation::set_orientation()`. Animations are horizontal by default. Some Animations (such as Cycle) don't support orientations.

```c++
Animation* animation = new WaveAnimation();
animation->set_orientation(Animation::Orientations::VERTICAL);
```

## Changing the Animation Speed
You can set the animation's speed in the constructor or via the `set_speed()` method. Speed is the amount of time between animation updates and is measured in milliseconds. "Speed" is a bit of a misnomer, since it actually measures the amount of time between the start of the animation and its completion. For example, an animation with 5 cycles and a speed of 100 will take 500ms (5 * 100) to finish, while the same animation with a speed of 500 will take 2500ms (5 * 500) to finish.

### Toggling Fading
By default, Pixels fade between color changes. Disabling fading causes color changes to occur instantly.
```c++
animation->set_fade(false);
```

[Home](README.md)
