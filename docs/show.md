# Show
Shows are used to modify Maestros at pre-defined moments. This can be anything from changing the animation displayed by a Section to adding an Overlay to stopping the Maestro from running.
Shows sit one layer above a Maestro. To initialize a Show, use the `Show::set_maestro()` method, passing in a reference to the Maestro that you wish to control. Now, in your program's loop, you'll call `Show::update()` instead of `Maestro::update()`.

For an example of how to configure a Show, see [ShowDemo](../gui/demo/showdemo.cpp).

## Contents
1. [Adding Events](#adding-events)
	1. [Event Parameters](#event-parameters)
	2. [Event Actions](#event-actions)
2. [Specifying Timing Methods](#specifying-timing-methods)
3. [Looping](#looping)
4. [Other Methods](#other-methods)
5. [Event List](#event-list)

## Adding Events
A `Event` is a set of instructions for changing the properties of a Section. Events are defined by:
* A `time` when the Event will execute, based on the program's current runtime
* An [action](#event-actions) that will be performed when the Event executes

Events can be found in the [src/show](../src/show) folder. A list of Events can be found in the [Event List](#event-list) section below.

The action is dependent on the type of Event being performed, and is executed when the Event's `time` is matched or exceeded by the program's runtime. Each Show references an array of Events. As each Event executes, the Show tracks the current index of the array and the time the last Event ran.

To set the Events in a Show, use the `Show::set_events()` method.

### Event Parameters
The first parameter is typically a pointer to the object being manipulated by this Event (e.g. a Maestro, Section, Canvas, etc.) The second parameter is the time that the Event is scheduled to occur. Any other parameters will depend on the action being performed.

```c++
int event_time = 5000;		// Trigger the Event after 5 seconds (5000ms).
int cycle_interval = 1000;	// Set the Section's cycle interval to 1 second (1000ms).
Event* event = new SectionSetCycleIntervalEvent(section, event_time, cycle_interval);
```

### Event Actions
Actions are pre-defined calls to other methods in the PixelMaestro suite. These calls are primarily to Maestros or Sections. For example, an Action can disable a Maestro, change a Section's Pixel layout, or generate a new color scheme. The action performed is based on the type of Event, and each Event performs a different action than the others.

For example, changing a Section's color animation is handled by the `SectionSetColorAnimationEvent` Event. When you declare the Event, you specify the animation options as part of the constructor. Then, you store that Event in an array with whatever other Events you want to pass to the Show. When the Show runs, it executes the Event's `run()` method, which calls the Section's `set_color_animation()` method with the parameters you specified in the constructor.

```c++
int num_events = 2;
Event* events[] = {
	new SectionSetCycleIntervalEvent(section, 5000, 1000),
	new SectionSetColorAnimationEvent(section, 5000, Section::ColorAnimations::NEXT, false, Section::AnimationOrientations::HORIZONTAL)
}
show.set_events(events, num_events);
```

## Specifying Timing Methods
A Show can use one of two timing methods: relative or absolute. Relative time measures the amount of time that has passed since the last Event. For example, if Event 1 has a time of 1000 and Event 2 has a time of 2000 ms, Event 1 will execute 1000 ms after the program starts, and Event 2 will execute 2000 ms after Event 1.

Absolute time measures the amount of time that has passed since the program started. Using the same example above, Event 1 executes 1000 ms after the program starts, and Event 2 executes 2000 ms after the program starts (or 1000 ms after Event 1 starts).

## Looping
After a Show completes its last Event, it won't do anything except update the Maestro. However, with looping enabled, the Show will repeat its Events indefinitely. To enable looping, call `Show::toggle_looping()`. To determine whether a Show is looping, call `Show::get_looping()`. Looping only works when using relative time.

## Event List
The parameters required by each Event should be pretty self-explanatory.
* CanvasClearEvent: Clears everything displayed on a Canvas.
* CanvasDrawCharEvent: Draws a single text character onto a Canvas.
* CanvasDrawCircleEvent: Draws a circle onto a Canvas.
* CanvasDrawLineEvent: Draws a line onto a Canvas.
* CanvasDrawPointEvent: Draws a single point on a Canvas.
* CanvasDrawRectEvent: Draws a box onto a Canvas.
* CanvasDrawTextEvent: Draws a string of characters onto a Canvas.
* CanvasDrawTriangleEvent: Draws a triangle onto a Canvas.
* ColorsGenerateRandomColorArrayEvent: Generates a set of random colors and stores it in the specified array.
* ColorsGenerateRandomColorEvent: Generates a single random color and stores it in the specified variable.
* ColorsGenerateScalingColorArrayEvent: Generates a color color gradient and stores it in the specified array.
* MaestroToggleRunEvent: Toggles a Maestro's running state.
* RunFunctionEvent: Uses std::functional to run a function (not available on Arduino).
* SectionSetCanvasEvent: Sets a Canvas to a Section.
* SectionSetColorAnimationEvent: Changes a Section's current color animation.
* SectionSetCycleIntervalEvent: Changes the interval between animation cycles for a Section.
* SectionSetOverlayEvent: Sets an Overlay to a Section.
* SectionToggleFadeEvent: Toggles fading on a Section's color animation.
* SectionUnsetOverlayEvent: Removes an Overlay from a Section.

[Home](README.md)
