# Section
Sections are the primary interface for PixelMaestro. Their purpose is to coordinate the behavior of Pixels. More specifically, they're used to send colors to Pixels based on the current running animation.

When creating a Section, you must assign a Pixel array to the Section as well as the logical layout of the array (e.g. rows and columns).
```c++
Section *section = new Section(pixels, new Section::Layout(rows, columns));
```

## Animations
The main focus of a Section is to render an animation. They do this by calculating color values which are stored in individual Pixels. The Section manages the type of animation, the colors used in the animation, the speed of the animation, and more.

### Setting the Color Palette
Sections require you to specify a palatte of colors for use in animations. You should provide one or more Colors as pointers in a `Colors::RGB` array. To set the color palette, use the `Section::setColors` method.

The following example sets a palette of three colors: red, green, and blue. Depending on the animation, one of these colors (or a mix) will be displayed in each Pixel.
```c++
Colors::RGB *colors = {Colors::RED, Colors::GREEN, Colors::BLUE};
section.setColors(colors, 3);
```

### Choosing an Animation
The animations available to you are listed in the `Section::ColorAnimations` enum.
* NONE: Nothing is displayed.
* SOLID: Displays a solid color.
* BLINK: Cycles all Pixels between on and off.
* CYCLE: All Pixels cycle through the colors stored in the color array.
* WAVE: Displays colors as a wave moving across the Section.
* PONG: Moves a wave of colors back and forth across the Section.
* MERGE: Converges colors into the center of the Section.
* RANDOMINDEX: Changes each Pixel to a random color stored in the array.
* SPARKLE: Quickly flashes a random Pixel on. The activated Pixel is randomly generated on each cycle update using a threshold that you can specify in the [AnimationOpts](#providing_additional_options) parameter.
* PATTERN: Displays a pre-defined pattern. See [Displaying Patterns](#displaying_patterns).
* NEXT: Shortcut for skipping to the next pattern.

Select an animation using the `Section::setColorAnimation` method. The following code displays a vertical wave moving from the top of the grid to the bottom:
```c++
Section::ColorAnimations anmation = ColorAnimations::WAVE;
bool reverse = false;
Section::AnimationOrientations orientation = AnimationOrientations::VERTICAL;
section.setColorAnimation(animation, reverse, orientation);
```
Changing `reverse` to `true` reverses the direction of the animation. Additionally, changing `orientation` rotates the orientation of the animation by 90 degrees.

### Changing the Animation's Speed
The speed of an animation is determined by two different counters: the refresh interval and the cycle interval. The refresh interval is the amount of time between Pixel redraws, and only applies when fading is enabled. The cycle interval is the amount of time between animation updates. Both the refresh and cycle intervals are measured in milliseconds.

The following code refreshes the Section every 1/10th of a second and cycles the animation every 1/2 second. If fading is disabled, then only the cycle speed will factor into the animation.
```c++
section.setRefreshInterval(100);
section.setCycleInterval(500);
```

### Providing Additional Options
Some animations use additional parameters for further customization. These parameters are stored in the `Section::animation_opts_` union. You can only set one option at a time, and the option applied depends on the current active animation.

The following code sets the threshold for the SPARKLE animation to 50%. SPARKLE determines whether to enable a Pixel by checking to see if a randomly generated number exceeds the threshold.
```c++
section.setColorAnimation(Section::ColorAnimations::SPARKLE);
section.getAnimationOpts()->sparkle_threshold = 50;
```

## Displaying Patterns
A Pattern is a 2D array of boolean values containing a representation of an animation. The array contains a collection of boolean arrays (called `frames`), each of which contains a set of boolean values that map directly to the Pixel grid. Each boolean value toggles whether or not its corresponding Pixel is turned on or off. For example, if frame 1, index 10 of the Pattern = false, then the Pixel at index 10 of the Pixel array will not be activated. However, if frame 2, index 10 = true, then on the next cycle the Pixel will be activated (e.g. display its normal color instead of black).

Tip: See the [PatternDemo class](../gui/demo/patterndemo.cpp) in the PixelMaestro QT application for an example.

This code snippet creates a single-frame Pattern for a Pixel grid with 10 rows and 10 columns. It displays a border around the grid, indicated by `1`. Note that when initializing a new Section::Pattern object, you must specify a custom Layout for the Pattern and the number of frames to display. The Pattern layout can be different than the Section Layout, and the number of frames can be less than the number of frames in the boolean array.
```c++
bool** pattern_array_ = new bool*[5] {
	// Frame 1: Border
	new bool[100] {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	}
}

section->setColorAnimation(Section::ColorAnimations::PATTERN);
section->setPattern(new Section::Pattern(this->pattern_array_, new Section::Layout(10, 10), 1));
```

#### Offsetting a Pattern
Offsetting shifts the Pattern's starting point to another place on the Pixel grid. By default the offset is set to 0, meaning the starting point is the same as the Pixel grid's starting point. Changing `offset->x` changes the starting row, and changing `offset->y` changes the starting column. These values can be negative.

The following code moves the Pattern 5 Pixels to the right and 1 Pixel down.
```c++
pattern->offset->x = 5;
pattern->offset->y = 1;
section->setPattern(pattern);
```

If the Pattern extends beyond the Pixel grid, the rest of the Pattern will be hidden from view. However, setting `Pattern::repeat` to true will wrap the hidden parts of the Pattern to the opposite end of the Pixel grid.

#### Animating a Pattern
You can set a Pattern to scroll horizontally, vertically, or both using the `Pattern::scrollRate` property. `scrollRate` defines the direction and number of Pixels that the Pattern should scroll per cycle. `scrollRate->x` scrolls along the horizontal axis, and `scrollRate->y` scrolls along the vertical axis. These values can be negative, which scrolls left instead of right for `scrollRate->x` and up instead of down for `scrollRate->y`.

The following code scrolls 1 Pixel to the right and 2 Pixels up.
```c++
pattern->scrollRate = new Section::Offset(1, -2);
```

### Toggling Fading
You can have Pixels fade during color changes by enabling fading. Otherwise, when the animation cycle changes, Pixels will immediately jump to the next color.
```c++
if (!section.getFade()) section.toggleFade();
```

## Getting a Pixel's Color
At some point, you'll need to retrieve the color of a Pixel for output. You can do this using the `getPixelColor(index)` method, where `index` is the index of the Pixel in the array (demonstrated below in [Accessing the Pixel by Index](#accessing-the-pixel-by-index)). If you'd rather access the Pixel by specifying its coordinate in the grid, see [Accessing the Pixel by Coordinate](#accessing-the-pixel-by-coordinate).

### Accessing the Pixel by Index
If you know the array index of the Pixel, you can use the `getPixel(index)` method to retrieve the Pixel directly:
```c++
Pixel *pixel = section.getPixel(100);
```

### Accessing the Pixel by Coordinate
If you don't know the Pixel's array index, but you know where it lies in the logical 2D grid, you can access it by its row and column. The Section will translate these coordinates into the appropriate array index.
```c++
Pixel *pixel = section.getPixel(50, 2);
```

## Using Overlays
You can add a second layer to your animations by merging the output of one Section with the current Section. This requires two sections, two Color arrays (one for each section), and two Pixel arrays (one for each Section). The layering is performed by merging the color of a Pixel in the base Section with its corresponding Pixel in the target Section.
You can learn more about merging colors in the [Colors](colors.md) document.
```c++
// Initialize Sections base and overlay
base.setOverlay(overlay, Colors::MixMode::NORMAL);
```

## Updating the Section
To update the Section, call the `update()` method. You will need to pass in the program's current runtime in milliseconds. More than likely, you will update a Section by calling its Maestro's `update()` method, which automatically the Section and all other Sections.
```c++
section.update(runtime);
```

## Other Methods
* Section::getPixelIndex(unsigned short row, unsigned short column): Translates a Pixel's coordinate into its index in the Pixel array.
* Section::setAll(Colors::RGB \*color): Sets all Pixels to the specified color.
* Section::setOne(unsigned short row, unsigned short column, Colors::RGB *color): Sets the Pixel at the specified row and column number to the specified color.

[Home](README.md)
