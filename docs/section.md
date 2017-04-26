# Section
Sections are the primary interface for PixelMaestro. They manage a collection of Pixels as a logical 2D grid.

## Declaration
Sections can be declared using a default or implicit constructor.

### Default Constructor
When using the default constructor, make sure you assign Pixels to the Section before using it.
```c++
Section section;
section.setPixels(pixels, rows, columns);
```

### Implicit Constructor
Alternatively, you can assign Pixels to the Section as part of the constructor.
```c++
Section section(pixels, rows, columns);
```

## Animations
Sections perform animations primarily by sending color values to individual Pixels. You can configure the type of animation performed, the colors used in the animation, and the speed of the animation from the Section.

### Setting the Color Palette
Sections require a pre-defined set of colors for use in animating Pixels. Colors are stored as a pointer to a `Colors::RGB` array. To set the color palette, use the `Section::setColors` method:
```c++
Colors::RGB colors = {Colors::WHITE, Colors::BLACK};
section.setColors(colors, 2);
```

### Choosing an Animation
The animations available to you are stored in the `Section::ColorAnimations` enum.
* NONE: Nothing is displayed.
* SOLID: Displays a solid color.
* BLINK: Cycles all Pixels between on and off.
* CYCLE: All Pixels cycle through the colors stored in the color array.
* WAVE: Displays colors as a wave moving across the Section.
* PONG: Moves a wave of colors back and forth across the Section.
* MERGE: Converges colors into the center of the Section.
* RANDOMINDEX: Changes each Pixel to a random color stored in the array.
* SPARKLE: Quickly flashes a random Pixel on.
* PATTERN: Displays a user-defined pattern.

Select an animation using the `Section::setColorAnimation` method:
```c++
bool reverse = false;
Section::AnimationOrientations orientation = AnimationOrientations::HORIZONTAL;
section.setColorAnimation(ColorAnimations::WAVE, reverse, orientation);
```
Changing `reverse` to `true` reverses the direction of the animation. Additionally, changing `orientation` moves the orientation of the animation by 90 degrees.
You can call this method without passing any parameters to simply switch to the next animation in the list. If you've reached the end of the list, the Section will jump back to the first animation.

### Changing the Animation's Speed
The speed of an animation is determined by two different counters: the refresh rate and the cycle rate. The refresh rate is the rate at which each Pixel redraws (this is really only used when fading is enabled). The cycle rate is the rate at which each Pixel switches colors, e.g. when the animation increments by one step. Both the refresh rate and cycle rate are measured in milliseconds. The following code refreshes the Section every 1/10th of a second and cycles the animation every 1/2 second:
```c++
section.setRefreshRate(100);
section.setCycleSpeed(500);
```

### Displaying Patterns
A Pattern is an array of boolean values that maps to the Pixel array. Each boolean toggles whether or not its corresponding Pixel is turned on or off. For example, if index 10 of the Pattern = false, then the Pixel at index 10 of the Pixel array will not be activated. Patterns can store multiple frames, and the Section will switch to the next frame on the next animation cycle.
This code snippet sets a 1-frame Pattern for a Pixel grid with dimensions 3x2.
```c++
unsigned char pattern[6] = {0, 1, 0, 0, 1, 0};
section.setPattern(pattern, 3, 2, 1);
```

### Toggling Fading
You can have Pixels fade during color changes by enabling fading. Otherwise, when the next animation cycle begins, Pixels will immediately jump to the next color.
```c++
if (!section.getFade()) section.toggleFade();
```

## Interacting with Pixels
You can interact with any Pixels assigned to a Section. In fact, this is the primary way of retrieving a Pixel's color for output. Sections provide multiple ways of interacting with Pixels, and thus mulitple ways of getting a Pixel's color.

### Accessing the Pixel by Index
If you know the array index of the Pixel, you can use the `getPixel(index)` method to retrieve the Pixel directly:
```c++
Pixel *pixel = section.getPixel(100);
```

### Accessing the Pixel by Coordinate
If you don't know the Pixel's array index, but you know where it lies in the hypothetical 2D grid, you can access it by its row and column. The Section will translate these coordinates into the array index.
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
To update the Section, call the `update()` method. You will need to pass in the program's current runtime in milliseconds. More than likely, you will update a Section by calling its Maestro's `update()` method, which automatically updates all Sections (including Overlays) assigned to the Maestro.
```c++
section.update(runtime);
```

## Other Methods
* Section::getPixelIndex(unsigned short row, unsigned short column): Returns the actual index of a Pixel given a row and column number.
* Section::setAll(Colors::RGB \*color): Sets all Pixels to the specified color.
* Section::setOne(unsigned short row, unsigned short column, Colors::RGB *color): Sets the Pixel at the specified row and column number to the specified color.

[Home](README.md)
