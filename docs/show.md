# Show
Shows are used to schedule animation changes for Sections in a Maestro.

## Transition
A `Transition` is a set of instructions for changing the properties of a Section. A Transition consists of the following properties:
* A `time` when the Transition will execute, based on the program's current runtime
* An `action` that will be performed when the Transition executes
* Any `opts`, or options, passed to the Section
* Whether the Transition has already `ran`.

When a Transition's `time` is matched or exceeded by the program's runtime, the `action` is performed with any extra parameters specified in `opts`. After the `action` has finished executing, `ran` is switched to `true`.
The Show stores an array of Transitions. As each Transition executes, the Show tracks the current index of the array. Since a Show could contain a lot of Transitions, it may be more resource-friendly to overwrite already-executed Transitions than to create a large array of Transitions that only run once.

### Specifying an Action
Actions are specified by the Show::Actions enum. Actions are performed against a Section. Transitions support the following actions:
* SET_COLOR_ANIMATION: Changes the active color animationto the one specified by `opts.val1`.
* SET_PATTERN: Changes the pattern to the one specified by `opts.pattern`.
* SET_UPDATE_SPEED: Changes the refresh rate to the one specified by `opts.val`.
* TOGGLE_FADE: Toggles fading of the Section.

How to specify which Section to update is described in detail under the heading *Setting Options*.

### Setting Options
The `Opts` struct lets you define various parameters as part of the Transition. These parameters include:
* `animation`: Specifies the Section::ColorAnimation to switch to when using the `SET_COLOR_ANIMATION` Action.
* `pattern`: Specifies the pattern that will be used for the `PATTERN` color animation.
* `sectionNum`: Specifies the index of the Section that the Action applies to.
* `val`: A multi-purpose variable for passing integer values.

## Other Methods
* unsigned short getCurrentIndex(): Returns the index of the next queued Transition.
* Transition \*getCurrentTransition: Returns the next queued Transition.

[Home](README.md)
