# Show
Shows schedule the execution of [Cues](cue.md) at certain points during the program's lifetime. To start a Show, use the `Maestro::set_show()` method. This method also requires you to pass in a set of [`Events`](#adding-events), which are explained below.

For an example of how to configure a Show, see [ShowDemo](../gui/demo/showdemo.cpp) in PixelMaestro Studio.

## Contents
1. [Creating a Show](#creating-a-show)
2. [Adding Events](#adding-events)
3. [Timing Methods](#timing-methods)
4. [Looping](#looping)
5. [Other Methods](#other-methods)
6. [Event List](#event-list)

## Creating a Show
To create a Show, call `Maestro::set_show()` and pass in the Events you want to run. This example creates two events using Cues: one that adds a new Canvas, and one that draws a circle onto the newly created Canvas.

**Tip:** `set_show()` automatically calls `set_cue_controller()` in case you haven't already initialized a CueController.

```c++
#include "cue/canvascuehandler.h"
#include "cue/event.h"
#include "cue/sectioncuehandler.h"

...
// Configure Maestro and CueController
...

int num_events = 2;
Event events[num_events] = {
	Event(5000, section_handler->set_canvas(0, 0, CanvasType::ColorCanvas)),
	Event(5000, canvas_handler->draw_circle(0, 0, Colors::GREEN, 5, 5, 2, true))
}
maestro.set_show(events, num_events);
```

## Adding Events
A `Event` contains a set of instructions for running a Cue. Events consist of:
* A `time` when the Event will execute in relation to the program's current runtime, and
* A [`Cue`](cue.md) that will run when the Event executes.

An Event is executed when its `time` is matched or exceeded by the program's runtime. When an Event runs, its `Cue` is loaded and executed. Each Show contains at least one Event. As each Event executes, the Show tracks the index of the next queued Event so that each Event runs sequentially.

To change or reset the Event list, use `Show::set_events()`.

## Timing Methods
A Show can use one of two timing methods: relative or absolute. Relative time measures the amount of time that has passed since the last Event. For example, if Event 1 has a time of 1000 and Event 2 has a time of 2000 ms, Event 1 executes 1000 ms after the program starts, and Event 2 executes 2000 ms after Event 1.

Absolute time measures the amount of time that has passed since the program started. Using the same example above, Event 1 executes 1000 ms after the program starts, and Event 2 executes 2000 ms after the program starts (or1000 ms after Event 1 starts).

## Looping
After a Show completes its last Event, it won't do anything except update the Maestro. However, with looping enabled, the Show will repeat its Events indefinitely. To enable looping, call `Show::set_looping(boolean)`. To determine whether a Show is looping, call `Show::get_looping()`. Looping only works when using relative time.

[Home](README.md)
