# Maestro
Maestros are responsible for coordinating multiple Sections. A Maestro isn't necessarily required, but it helps with abstracting away some of the management of multiple sections.

## Contents
1. [Creating a Maestro](#creating-a-maestro)
2. [Changing the Refresh Rate](#changing-the-refresh-rate)
3. [Interacting with Sections](#interacting-with-sections)
4. [Setting a Global Brightness Level](#setting-a-global-brightness-level)
5. [Toggling the Running State](#toggling-the-running-state)
6. [Updating the Maestro](#updating-the-maestro)

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

## Changing the Refresh Rate
The refresh rate is the amount of time (in milliseconds) between Pixel redraws. On each refresh interval, each Section's `update()` method is called, which triggers a refresh of every Section's Pixels. You can get the refresh rate using `get_refresh_interval()` and set the refresh rate using `set_refresh_interval()`.

## Interacting with Sections
You can call a Section using the `get_section()` method and passing in the index of the Section.

## Setting a Global Brightness Level
Use the `set_brightness()` method to set a global brightness level for all Sections and Pixels. Global brightness is applied when retrieving a Pixel color via `get_pixel_color(section, index)`.

## Toggling the Running State
You can pause the Maestro using the `set_running(bool)` method. When the Maestro is paused, it won't update any of its Sections.

## Updating the Maestro
To update the Maestro, call the `update()` method while passing in the program's current runtime in milliseconds. The Maestro will pass the runtime down to each Section's `update()` method.
```c++
maestro.update(runtime);
```

[Home](README.md)
