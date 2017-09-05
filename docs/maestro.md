# Maestro
Maestros are responsible for coordinating multiple Sections. A Maestro isn't necessarily required, but it helps if you're controlling two or more Sections. Note that a Maestro has no idea about the physical layout of its Sections, just as a Section has no idea about the physical layout of its Pixels.

## Contents
1. [Creating a Maestro](#creating-a-maestro)
2. [Getting the Refresh Rate](#getting-the-refresh-rate)
3. [nteracting with Sections](#interacting-with-sections)
4. [Toggling the Running State](#toggling-the-running-state)
5. [Updating the Maestro](#updating-the-maestro)

## Creating a Maestro
Declare a Maestro by passing in the Sections that it will be controlling.
```c++
int num_sections = 2;
Section sections[num_sections];
Maestro* maestro = new Maestro(sections, num_sections);
```
You can also use the `set_sections()` method to update the Maestro's Sections.

## Getting the Refresh Rate
The `get_refresh_rate()` method takes the refresh rate of all the Sections in the Maestro and returns the lowest one. The purpose of this is for creating timers that call `Maestro::update()` at pre-determined intervals, while ensuring that even the fastest Section is being updated properly. Note that this doesn't guarantee that all Sections will be updated at their intended rate (for example, if Section 1 refreshes every 50ms and Section 2 every 75ms, Section 2 won't refresh until 100ms).

## Interacting with Sections
You can call a Section using the `get_section()` method and passing in the index of the Section.

## Toggling the Running State
You can pause the Maestro using the `toggle_running()` method. When the Maestro is paused, it won't update any of its Sections.

## Updating the Maestro
To update the Maestro, call the `update()` method while passing in the program's current runtime in milliseconds. The Maestro will pass the runtime down to each Section's `update()` method.
```c++
maestro.update(runtime);
```

[Home](README.md)
