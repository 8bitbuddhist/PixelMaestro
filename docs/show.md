# Show
Shows are used to perform actions at pre-determined moments. This can be anything from changing the animation, to adding an Overlay, to drawing text on a Canvas. It lets you plan out changes that the Maestro automatically performs over its runtime.

Shows are controlled by a Maestro. To initialize a Show, use the `Maestro::add_show()` method. This method also requires you to pass in a set of `Events`, which are explained below.

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
Create a Show by calling `Maestro::add_show()` and passing in the Events you want to run:

```c++
int num_events = 2;
Event* events[] = {
	new SectionSetCycleIntervalEvent(section, 5000, 1000),
	new SectionSetAnimationEvent(section, 5000, new CycleAnimation(Colors::COLORHWEEL, 12))
}
maestro.add_show(&events[0], num_events);
```

## Adding Events
A `Event` is a set of instructions such as generating a color scheme or changing the speed of an animation. Events consist of:
* A `time` when the Event will execute based on the program's current runtime
* An [action](#event-actions) that will be performed when the Event executes

All Events can be found in the [src/show](../src/show) folder. A list of Events can be found in the [Event List](#event-list) section below.

The `Action` is dependent on the type of Event being performed, and is executed when the Event's `time` is matched or exceeded by the program's runtime. Each Show contains one or more Events. As each Event executes, the Show tracks the index of the next queued Event so that each Event runs sequentially.

To reset or change the Event list, use `Show::set_events()`.

### Event Parameters
The first parameter of an Event is typically a pointer to the object being manipulated by this Event (e.g. a Maestro, Section, Canvas, or Animation) The second parameter is the time that the Event is scheduled to occur. Any other parameters will vary depending on the type of Event.

### Event Actions
Actions are pre-defined calls to other methods in the PixelMaestro suite. These calls are primarily to Maestros or Sections. For example, an Action can disable a Maestro, change a Section's Pixel layout, or generate a new color scheme. The action performed is based on the type of Event, and each Event performs a different action than the others.

For example, changing a Section's Animation is handled by the `SectionSetAnimationEvent` Event. When you declare the Event, you pass the target Animation in the constructor. Then, you store that Event in an array with whatever other Events you want to pass to the Show. When the Show runs, it executes the Event's `run()` method, which calls the Section's `set_color_animation()` method with the parameters you specified in the constructor. The sample Show created below will change the Animation and cycle interval after 5 seconds.

## Timing Methods
A Show can use one of two timing methods: relative or absolute. Relative time measures the amount of time that has passed since the last Event. For example, if Event 1 has a time of 1000 and Event 2 has a time of 2000 ms, Event 1 will execute 1000 ms after the program starts, and Event 2 will execute 2000 ms after Event 1.

Absolute time measures the amount of time that has passed since the program started. Using the same example above, Event 1 executes 1000 ms after the program starts, and Event 2 executes 2000 ms after the program starts (or 1000 ms after Event 1 starts).

## Looping
After a Show completes its last Event, it won't do anything except update the Maestro. However, with looping enabled, the Show will repeat its Events indefinitely. To enable looping, call `Show::set_looping(boolean)`. To determine whether a Show is looping, call `Show::get_looping()`. Looping only works when using relative time.

## Event List
* AnimationSetFadeEvent: Toggles fading on an animation.
* CanvasClearEvent: Clears everything displayed on a Canvas.
* CanvasDrawCircleEvent: Draws a circle onto a Canvas.
* CanvasDrawLineEvent: Draws a line onto a Canvas.
* CanvasDrawPointEvent: Draws a single point on a Canvas.
* CanvasDrawRectEvent: Draws a box onto a Canvas.
* CanvasDrawTextEvent: Draws a string of characters onto a Canvas.
* CanvasDrawTriangleEvent: Draws a triangle onto a Canvas.
* ColorsGenerateRandomColorArrayEvent: Generates a set of random colors and stores it in the specified array.
* ColorsGenerateRandomColorEvent: Generates a single random color and stores it in the specified variable.
* ColorsGenerateScalingColorArrayEvent: Generates a color color gradient and stores it in the specified array.
* MaestroSetRunningEvent: Sets a Maestro's running state.
* OverlaySetOptionsEvent: Sets an Overlay's options.
* RunFunctionEvent: Uses std::functional to run a function (not available on Arduino).
* SectionAddOverlayEvent: Adds an Overlay to a Section.
* SectionRemoveOverlayEvent: Removes a Section's Overlay.
* SectionSetAnimationEvent: Changes a Section's current animation.
* SectionSetCycleIntervalEvent: Changes the interval between animation cycles for a Section.

[Home](README.md)
