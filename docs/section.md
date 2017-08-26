# Section
Sections are the primary interface for PixelMaestro. Their purpose is to coordinate the behavior of Pixels. More specifically, they're used to send colors to Pixels based on the current running animation.

## Contents
1. [Creating a Section](#creating-a-section)
2. [Animating a Section](#animating-a-section)
	1. [Setting the Color Palette](#setting-the-color-palette)
	2. [Choosing an Animation](#choosing-an-animation)
	3. [Changing the Animation Speed](#changing-the-animation-speed)
	4. [Providing Additional Options](#providing-additional-options)
	5. [Toggling Fading](#toggling-fading)
3. [Displaying Custom Shapes and Patterns](#displaying-custom-shapes-and-patterns)
4. [Retrieving Pixels and Colors](#retrieving-pixels-and-colors)
	1. [Accessing Pixels by Index](#accessing-pixels-by-index)
	2. [Accessing Pixels by Coordinate](#accessing-pixels-by-coordinate)
5. [Using Overlays](#using-overlays)
6. [Updating a Section](#updating-a-section)
7. [Other Methods](#other-methods)

## Creating a Section
When creating a Section, you must assign a Pixel array to the Section as well as the logical layout of the array (e.g. rows and columns).
```c++
Section *section = new Section(pixels, new Point(rows, columns));
```

## Animating a Section
The main focus of a Section is to render an animation. They do this by calculating color values which are stored in individual Pixels. The Section manages the type of animation, the colors used in the animation, the speed of the animation, and more.

Creating an animation requires two steps:
1. Set a color palette, and
2. Set the animation.

You can perform additional steps such as changing the animation's speed, toggling fading, or specifying additional animation-specific options.

### Setting the Color Palette
Sections require you to specify a palatte of colors for use in animations. You should provide one or more Colors as pointers in a `Colors::RGB` array. To set the color palette, use the `Section::set_colors` method.

The following example sets a palette of three colors: red, green, and blue. Depending on the animation, one of these colors (or a mix) will be displayed in each Pixel.
```c++
Colors::RGB *colors = {Colors::RED, Colors::GREEN, Colors::BLUE};
section.set_colors(colors, 3);
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
* SPARKLE: Quickly flashes a random Pixel on. The activated Pixel is randomly generated on each cycle update using a threshold that you can specify in the [AnimationOpts](#providing-additional-options) parameter.
* NEXT: Shortcut for skipping to the next animation.

Select an animation using the `Section::set_color_animation` method. The following code displays a vertical wave moving from the top of the grid to the bottom:
```c++
Section::ColorAnimations anmation = ColorAnimations::WAVE;
bool reverse = false;
Section::AnimationOrientations orientation = AnimationOrientations::VERTICAL;
section.set_color_animation(animation, reverse, orientation);
```
Changing `reverse` to `true` reverses the direction of the animation. Additionally, changing `orientation` rotates the orientation of the animation by 90 degrees.

### Changing the Animation Speed
The speed of an animation is determined by two different counters: the refresh interval and the cycle interval. The refresh interval is the amount of time between Pixel redraws, and only applies when fading is enabled. The cycle interval is the amount of time between animation updates. Both the refresh and cycle intervals are measured in milliseconds.

The following code refreshes the Section every 1/10th of a second and cycles the animation every 1/2 second. If fading is disabled, then only the cycle speed will factor into the animation.
```c++
section.set_refresh_interval(100);
section.set_cycle_interval(500);
```

### Providing Additional Options
Some animations use additional parameters for further customization. These parameters are stored in the `Section::animation_opts_` union. You can only set one option at a time, and the option applied depends on the current active animation.

The following code sets the threshold for the SPARKLE animation to 50%. SPARKLE determines whether to enable a Pixel by checking to see if a randomly generated number exceeds the threshold.
```c++
section.set_color_animation(Section::ColorAnimations::SPARKLE);
section.get_animation_opts()->sparkle_threshold = 50;
```

### Toggling Fading
You can have Pixels fade during color changes by enabling fading. Otherwise, when the animation cycle changes, Pixels will immediately jump to the next color.
```c++
if (!section.get_fade()) section.toggle_fade();
```

## Displaying Custom Shapes and Patterns
You can display custom shapes using the [Canvas](canvas.md) class.

## Retrieving Pixels and Colors
At some point, you'll need to retrieve the color of a Pixel for output. You can do this using the `get_pixel_color(index)` method, where `index` is the index of the Pixel in the array (demonstrated below in [Accessing the Pixel by Index](#accessing-the-pixel-by-index)). If you'd rather access the Pixel by specifying its coordinate in the grid, see [Accessing the Pixel by Coordinate](#accessing-the-pixel-by-coordinate).

### Accessing Pixels by Index
If you know the array index of the Pixel, you can use the `get_pixel(index)` method to retrieve the Pixel directly:
```c++
Pixel *pixel = section.get_pixel(100);
```

### Accessing Pixels by Coordinate
If you don't know the Pixel's array index, but you know where it lies in the logical 2D grid, you can access it by its row and column. The Section will translate these coordinates into the appropriate array index.
```c++
Pixel *pixel = section.get_pixel(50, 2);
```

## Using Overlays
You can add a second layer to your animations by merging the output of one Section with the current Section. This requires two sections, two Color arrays (one for each section), and two Pixel arrays (one for each Section). The layering is performed by merging the color of a Pixel in the base Section with its corresponding Pixel in the target Section.
You can learn more about merging colors in the [Colors](colors.md) document.
```c++
// Initialize Sections base and overlay
base.set_overlay(overlay, Colors::MixMode::NORMAL);
```

## Updating a Section
To update a Section, call the `update()` method. You will need to pass in the program's current runtime in milliseconds. More than likely, you will update a Section by calling its Maestro's `update()` method, which automatically the Section and all other Sections.
```c++
section.update(runtime);
```

## Other Methods
* `Section::get_pixel_index(unsigned short row, unsigned short column)`: Translates a Pixel's x and y coordinates into its index in the Pixel array. This method also accepts a Point.
* `Section::set_all(Colors::RGB\* color)`: Sets all Pixels to the specified color.
* `Section::set_one(unsigned int index, Colors::RGB\* color)`: Sets the Pixel at the specified array index to the specified color.

[Home](README.md)
