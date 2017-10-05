# Maestro
Maestros are at the top of the PixelMaestro hierarchy. In addition to managing multiple Sections, they set global parameters such as the refresh rate, brightness level, and Show Events.

## Contents
1. [Creating a Maestro](#creating-a-maestro)
2. [Updating the Maestro](#updating-the-maestro)
3. [Changing the Refresh Rate](#changing-the-refresh-rate)
4. [Interacting with Sections](#interacting-with-sections)
5. [Setting a Global Brightness Level](#setting-a-global-brightness-level)
6. [Toggling the Running State](#toggling-the-running-state)
7. [Creating a Show](#creating-a-show)

## Creating a Maestro
Create a Maestro by passing in the Sections that it will be controlling. The following code creates two Sections, one with a 10x20 grid of Pixels and another with a 20x30 grid.
```c++
int num_sections = 2;
Section sections[] = {
	Section(10, 20),
	Section(20, 30)
};
Maestro maestro(sections, num_sections);
```
You can also use `set_sections()` to set the Maestro's Sections.

## Updating the Maestro
The `Maestro::update()` method triggers an update of all Sections, Pixels, Canvases, and Animations (and a Show, if added) that the Maestro manages. The time between refreshes is determined by the `refresh_interval`, which defaults to 40 milliseconds. This means that every 40ms (or 25 times a second), each Pixel will draw a single frame. Drawing new frames multiple times per second is what gives the appearance of a single fluid animation.

When you call `Maestro::update()`, pass in the program's current runtime in milliseconds. The Maestro will subsequently call the `update()` method of each of its Sections, which update all of their Animations, Canvases, Overlays, and Pixels.
```c++
maestro.update(runtime);
```

## Changing the Refresh Rate
The refresh rate is the amount of time (in milliseconds) between redraws. On each refresh, each Section's `update()` method is called, which triggers a redraw of the Section's Pixels. You can get the refresh rate using `get_refresh_interval()` and set the refresh rate using `set_refresh_interval()`.

## Interacting with Sections
You can retrieve a Section using the `get_section()` method. Pass in the index of the desired Section.

## Setting a Global Brightness Level
Use the `set_brightness()` method to set a global brightness level for all Sections and Pixels. Global brightness is applied when retrieving a Pixel color via `get_pixel_color(section, index)`. Brightness levels range from 0 (off) to 255 (fully lit).

## Toggling the Running State
You can pause the Maestro using the `set_running(bool)` method. When you resume, it will pick up exactly where it left off (unless you are running a Show, in which case it will execute each Event that should have ran).

## Creating a Show
Shows let you set in advance actions that will execute at a later point in the Mastro's runtime. For more information, see the [Show documentation](show.md).

[Home](README.md)
