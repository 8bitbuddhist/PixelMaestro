# Show
Shows are used to modify Maestros at pre-defined moments. This can be anything from changing the animation displayed by a Section to adding an Overlay to stopping the Maestro from running.
Shows sit one layer above a Maestro. To initialize a Show, use the `Show::setMaestro()` method, passing in a reference to the Maestro that you wish to control. Now, when you want to update the Maestro, you'll call `Show::update()` instead of `Maestro::update()`.

For an example of how to configure a Show, see [ShowDemo](../gui/demos/ShowDemo.cpp).

## Transition
A `Transition` is a set of instructions for changing the properties of a Section. Transitions are defined by:
* A `time` when the Transition will execute, based on the program's current runtime
* An [action](#specifying_an_action) that will be performed when the Transition executes

Transitions can be found in the [`src/show`](../src/show) folder. The name should be pretty self-explanatory, and the argument list essentially matches the argument list of the corresponding function.

The action is dependent on the type of Transition being performed, and is executed when the Transition's `time` is matched or exceeded by the program's runtime. Each Show references an array of Transitions. As each Transition executes, the Show tracks the current index of the array and the time the last Transition ran.

To set the Transitions in a Show, use the `Show::setTransitions()` method.

### Specifying an Action
Actions are pre-defined calls to other methods in the PixelMaestro suite. These calls are primarily to Maestros or Sections. For example, an Action can disable a Maestro, change a Section's Pixel layout, or generate a new color scheme. The action performed is based on the type of Transition, and each Transition performs a different action than the others.

For example, changing a Section's color animation is handled by the `SectionSetColorAnimationTransition` Transition. When you declare the Transition, you specify the animation options as part of the constructor. Then, you store that Transition in an array with whatever other Transitions you want to pass to the Show. When the Show runs, it executes the Transition's `run()` method, which calls the Section's `setColorAnimation()` method with the parameters you specified in the constructor.

```c++
int numTransitions = 1;
Transition* transitions[] = {
	new SectionSetColorAnimationTransition(section, 5000, Section::ColorAnimations::NEXT, false, Section::AnimationOrientations::HORIZONTAL)
}

show.addShow(transitions, numTransitions, TimingModes::RELATIVE, true);
```

## Timing Methods
A Show can use one of two timing methods: relative or absolute. Relative time measures the amount of time that has passed since the last Transition. For example, if Transition 1 has a time of 1000 and Transition 2 has a time of 2000 ms, Transition 1 will execute 1000 ms after the program starts, and Transition 2 will execute 2000 ms after Transition 1.

Absolute time measures the amount of time that has passed since the program started. Using the same example above, Transition 1 executes 1000 ms after the program starts, and Transition 2 executes 2000 ms after the program starts (or 1000 ms after Transition 1 starts).

## Looping
When a Show completes its last Transition, it does nothing except update the Maestro. However, with looping enabled, the Show will repeat its Transitions indefinitely. To enable looping, call `Show::toggleLooping()`. To determine whether a Show is looping, call `Show::getLooping()`. Looping works best when using relative time.

## Other Methods
* unsigned short getCurrentIndex(): Returns the index of the next queued Transition.
* Transition \*getCurrentTransition: Returns the next queued Transition.

[Home](README.md)
