# Show
Shows are used to perform actions at pre-determined moments. This can be anything from changing an Animation to adding an Overlay to drawing on a Canvas. It lets you plan out actions in advance that the Maestro will automatically perform over the course of its runtime. Combined with [Cues](cue.md), Shows let you run practically any PixelMaestro action at any time.

Shows are managed by a Maestro. To initialize a Show, use the `Maestro::add_show()` method. This method also requires you to pass in a set of [`Events`](#adding-events), which are explained below.

For an example of how to configure a Show, see [ShowDemo](../gui/demo/showdemo.cpp).

## Contents
1. [Creating a Show](#creating-a-show)
2. [Adding Events](#adding-events)
	1. [Event Parameters](#event-parameters)
	2. [Event Actions](#event-actions)
3. [Timing Methods](#timing-methods)
4. [Looping](#looping)
5. [Other Methods](#other-methods)
6. [Event List](#event-list)

## Creating a Show
Create a Show by calling `Maestro::add_show()` and passing in the Events you want to run. This example creates two events using Cues: one that adds a new Canvas, and one that draws a circle onto the Canvas.

```c++
#include "cue/canvascue.h"
#include "cue/sectioncue.h"
unsigned char canvas_buffer[100];
unsigned char drawing_buffer[100];

SectionCue::add_canvas(canvas_buffer, 0, CanvasType::ColorCanvas);
CanvasCue::draw_circle(drawing_buffer, 0, Colors::GREEN, 5, 5, 2, true);

int num_events = 2;
Event* events[] = {
	new RunCueEvent(5000, maestro, canvas_buffer),
	new RunCueEvent(5000, maestro, drawing_buffer),
}

maestro.add_show(&events[0], num_events);
```

## Adding Events
A `Event` is an object containing a set of instructions. Events consist of:
* A `time` when the Event will execute based on the program's current runtime, and
* An [`action`](#event-actions) that will be performed when the Event executes.

All Events can be found in the [src/show](../src/show) folder. A list of Events can be found in the [Event List](#event-list) section below.

An Event is executed when its `time` is matched or exceeded by the program's runtime. When an Event runs, its `action` is called, which is typically a method call to another PixelMaestro component. Each Show contains at least one Event. As each Event executes, the Show tracks the index of the next queued Event so that each Event runs sequentially.

To reset or change the Event list, use `Show::set_events()`.

### Event Parameters
The first parameter is the time that the Event is scheduled to occur in milliseconds. The second parameter is typically a pointer to the object being manipulated (e.g. a Maestro, Section, Canvas, or Animation). Any other parameters will vary depending on the type of Event.

### Event Actions
Actions are pre-defined calls to other methods in the PixelMaestro suite. These calls are primarily to Maestros or Sections. For example, an action can stop a Maestro, change a Section's size, or generate a new color scheme. The action performed is based on the type of Event, and each Event performs a different action.

For example, changing a Section's Animation is handled by the `SectionSetAnimationEvent` Event. When you declare the Event, you pass a pointer to the desired Animation in the constructor. Then, you store that Event in an array with whatever other Events you want to pass to the Show. When the Show runs, it executes the Event's `run()` method, which calls the Section's `set_animation()` method with the parameters you specified in the constructor.

## Timing Methods
A Show can use one of two timing methods: relative or absolute. Relative time measures the amount of time that has passed since the last Event. For example, if Event 1 has a time of 1000 and Event 2 has a time of 2000 ms, Event 1 will execute 1000 ms after the program starts, and Event 2 will execute 2000 ms after Event 1.

Absolute time measures the amount of time that has passed since the program started. Using the same example above, Event 1 executes 1000 ms after the program starts, and Event 2 executes 2000 ms after the program starts (1000 ms after Event 1 starts).

## Looping
After a Show completes its last Event, it won't do anything except update the Maestro. However, with looping enabled, the Show will repeat its Events indefinitely. To enable looping, call `Show::set_looping(boolean)`. To determine whether a Show is looping, call `Show::get_looping()`. Looping only works when using relative time.

## Event List
* RunCueEvent: Runs a [Cue](#cue.md).
* RunFunctionEvent: Uses std::functional to run a function (not available on Arduino).

[Home](README.md)
