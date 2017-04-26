# Maestro
Maestros are responsible for coordinating multiple Sections. A Maestro isn't necessarily required, but it helps if you're controlling two or more Sections. Note that a Maestro has no idea about the physical layout of its Sections, just as a Section has no idea about the physical layout of its Pixels.

## Declaration
Declare a Maestro by passing in the Sections that it will be controlling.
```c++
int numSections = 2;
Section sections[numSections];
Maestro maestro = new Maestro(sections, numSections);
```
You can also use the `setSections` method to update the Maestro's Sections.

## Getting the Refresh Rate
The `getRefreshRate` method takes the refresh rate of all the Sections in the Maestro and returns the lowest one. The purpose of this is to ensure that even the fastest Section is being updated properly. Note that this doesn't guarantee that all Sections will be updated at their intended rate (for example, if Section 1 refreshes every 50ms and Section 2 every 75ms, Section 2 won't refresh until 100ms).

## Interacting with Sections
You can call a Section using the `getSection` method and passing in the index of the Section.

## Toggling the Running State
You can pause the Maestro using the `toggleRunning` method. When the Maestro is paused, it won't refresh any of its Sections.

## Updating the Maestro
To update the Maestro, call the `update` method while passing in the program's current runtime in milliseconds. The Maestro will call each Section's `update` method while forwarding the runtime to each Section.
```c++
maestro.update(runtime);
```
[Home](Readme.md)
