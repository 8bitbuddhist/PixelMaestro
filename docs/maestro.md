# Maestro
Maestros are responsible for coordinating multiple Sections. A Maestro isn't necessarily required, but it helps with abstracting away some of the management of multiple sections.

## Contents
1. [Creating a Maestro](#creating-a-maestro)
2. [Updating the Maestro](#updating-the-maestro)
3. [Changing the Refresh Rate](#changing-the-refresh-rate)
4. [Interacting with Sections](#interacting-with-sections)
5. [Setting a Global Brightness Level](#setting-a-global-brightness-level)
6. [Toggling the Running State](#toggling-the-running-state)
7. [Setting a Show](#setting-a-show)

## Creating a Maestro
Declare a Maestro by passing in the Sections that it will be controlling. The following code creates two Sections, one with a 10x20 grid of Pixels and another with a 20x30 grid.
```c++
int num_sections = 2;
Section sections[num_sections] = {
	Section(new Point(10, 20)),
	Section(new Point(20, 30))
};
Maestro maestro(sections, num_sections);
```
You can also use `set_sections()` to set the Maestro's Sections.

## Updating the Maestro
The `Maestro::update()` method triggers an update of all Sections, Pixels, Canvases, and Animations (and a Show, if configured) that the Maestro manages. The time between refreshes is determined by the `refresh_interval`, which defaults to 20 milliseconds. This means that every 20ms (or 50 times a second), every Section managed by the Maestro will draw a single frame. Calling `update()` multiple times repeatedly is what gives the appearance of a single fluid animation.

When you call the `update()` method, pass in the program's current runtime (or any incrementing value) in milliseconds. The Maestro will pass the runtime down to the Show's update method (if one is set) and each Section's `update()` method, as well as any Overlays or Canvases.
```c++
maestro.update(runtime);
```

## Changing the Refresh Rate
The refresh rate is the amount of time (in milliseconds) between redraws. On each refresh interval, each Section's `update()` method is called, which triggers a refresh of the Section's Pixels. This also cascades down to any Overlays and Canvases you configured for each Section. You can get the refresh rate using `get_refresh_interval()` and set the refresh rate using `set_refresh_interval()`.

## Interacting with Sections
You can call a Section using the `get_section()` method and passing in the index of the Section.

## Setting a Global Brightness Level
Use the `set_brightness()` method to set a global brightness level for all Sections and Pixels. Global brightness is applied when retrieving a Pixel color via `get_pixel_color(section, index)`.

## Toggling the Running State
You can pause the Maestro using the `set_running(bool)` method. When the Maestro is paused, it won't update any of its Sections.

## Setting a Show
[Shows](show.md) let you configure actions that will execute at a pre-determined time later during the program's runtime. For more information, see the [Show documentation](show.md).

[Home](README.md)
