# Maestro
As the name implies, Maestros are responsible for coordinating all other PixelMaestro components. In addition to managing Sections directly, Maestros set global parameters such as the Pixel refresh rate, brightness level, [Cue controller](cue.md), and [Show handler](show.md).

## Contents
1. [Creating a Maestro](#creating-a-maestro)
2. [Updating the Maestro](#updating-the-maestro)
3. [Changing the Refresh Rate](#changing-the-refresh-rate)
4. [Interacting with Sections](#interacting-with-sections)
5. [Setting a Global Brightness Level](#setting-a-global-brightness-level)
6. [Toggling the Running State](#toggling-the-running-state)
7. [Creating a Show](#creating-a-show)

## Creating a Maestro
When creating a Maestro, you need to pass in the Sections it will be controlling. The following snippet creates two Sections, one with a 10x20 Pixel grid and another with a 20x30 grid.
```c++
int num_sections = 2;
Section sections[] = {
	Section(10, 20),
	Section(20, 30)
};
Maestro maestro(sections, num_sections);
```

If you only want to use a single Section, just pass the grid dimensions into the Maestro's constructor. The Maestro dynamically allocates the new Section:
```c++
Maestro maestro(10, 20);
```

You can also use `Maestro::set_sections()` to set the Maestro's Sections.

## Updating the Maestro
The `Maestro::update()` method triggers an update of every component managed by the Maestro. The time between refreshes is determined by the `refresh_interval`, which defaults to 50 milliseconds (or 20 frames per second). This means that every 50ms, every component will run through its update routine, such as drawing an animation or canvas frame.

**Note:** `Maestro::update()` is non-blocking, meaning it will not prevent other processes or tasks from executing even on a single-threaded device.

When you call `Maestro::update()`, pass in the program's current runtime in milliseconds. The Maestro uses the runtime to determine whether it should update (by comparing the runtime to the last time the update was executed). The Maestro then calls `Section::update()` on each of its Sections, which in turn update all of their managed components.
```c++
maestro.update(runtime);
```
If necessary, you can bypass the runtime check and force the Maestro to update using `maestro.update(runtime, true)`. This immediately updates every Section regardless of the Maestro's last update time.

## Changing the Refresh Rate
The refresh rate is the amount of time (in milliseconds) before the Maestro updates its Sections. This defaults to 50ms (or 20fps). You can get the refresh rate using `get_refresh_interval()` and set the refresh rate using `set_refresh_interval()`.

## Interacting with Sections
You can retrieve a Section using `get_section()`. Pass in the index of the desired Section. For more information, see the [Section documentation](section.md).

## Setting a Global Brightness Level
Use `set_brightness()` to set a global brightness level for all Pixels. Global brightness is applied when retrieving a Pixel color via `get_pixel_color(section, index)`. Brightness ranges from 0 (off) to 255 (full).

## Toggling the Running State
You can pause the Maestro using `set_running(bool)`. When you resume, it will pick up exactly where it left off (unless you are running a Show, in which case it will execute each Event that should have ran while the Maestro was paused).

## Creating a Show
Shows let you plan out actions that will execute at a later point in the Mastro's runtime. For more information, see the [Show documentation](show.md).

[Home](README.md)
