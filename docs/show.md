# Show
Shows are used to schedule animation changes for Sections in a Maestro. To initialize a Show, use the `Show::setMaestro()` method, passing in a reference to the Maestro that you wish to control.

For an example of how to configure a Show, see [ShowDemo](../gui/demos/ShowDemo.cpp) in the PixelMaestro_GUI application.

## Transition
A `Transition` is a set of instructions for changing the properties of a Section. Transitions are defined by:
* A `time` when the Transition will execute, based on the program's current runtime
* An `action` that will be performed when the Transition executes

An `action` is a function that gets executed when the Transition's `time` is matched or exceeded by the program's runtime.

The Show stores an array of Transitions. As each Transition executes, the Show tracks the current index of the array and the time the last Transition ran.

To set the Transitions in a Show, use the `Show::setTransitions()` method.

### Specifying an Action
Actions are partial function applications created using [std::bind](http://en.cppreference.com/w/cpp/utility/functional/bind). When the Transition executes, it runs this function, then moves on to the next Transition. An Action can be anything from toggling the Maestro to changing a Section's layout to generating a new color scheme.

## Timing Methods
A Show can use one of two timing methods: relative or absolute. Relative time measures the amount of time that has passed since the last Transition. For example, if Transition 1 has a time of 1000 and Transition 2 has a time of 2000 ms, Transition 1 will execute 1000 ms after the program starts, and Transition 2 will execute 2000 ms after Transition 1.

Absolute time measures the amount of time that has passed since the program started. Using the same example above, Transition 1 executes 1000 ms after the program starts, and Transition 2 executes 2000 ms after the program starts (or 1000 ms after Transition 1 starts).

## Looping
When a Show completes its last Transition, it does nothing except update the Maestro. However, with looping enabled, the Show will repeat its Transitions indefinitely. To enable looping, call `Show::toggleLooping()`. To determine whether a Show is looping, call `Show::getLooping()`. Looping works best when using relative time.

## Other Methods
* unsigned short getCurrentIndex(): Returns the index of the next queued Transition.
* Transition \*getCurrentTransition: Returns the next queued Transition.

[Home](README.md)
