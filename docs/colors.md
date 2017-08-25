# Colors
The Colors class provides methods for creating and interacting with colors. Colors are based on the RGB color model and are stored as 24-bit variables with 8 bits dedicated to each color channel. Colors are defined by the `Colors::RGB` struct.

## Contents
1. [Creating Colors](#creating-colors)
2. [Manipulating Colors](#manipulating-colors)
3. [Generating Colors](#generating-colors)
4. [Mixing Colors](#mixing-colors)
5. [Sample Colors](#sample-colors)

## Creating Colors
The following example creates a new color called `blue`. The red and green channels are set to 0, but the blue channel is set to 255 (full).
```c++
Colors::RGB blue = {0, 0, 255};
```

## Manipulating Colors
The `Colors::RGB` struct contains overridden operators for setting, adding, subtracting, and comparing colors.
```c++
Colors::RGB red = {255, 0, 0};
Colors::RGB blue = {0, 0, 255};
Colors::RGB fuchsia = red + blue;	// {255, 0, 255}
```

## Generating Colors
The `generateRandomColorArray` and `generateScalingColorArray` methods are used to quickly create new color palettes. Pass in a starting color, a destination color array, and the number of colors you wish to generate. These methods automatically generate a new palette and populate the array based on your parameters.

## Mixing Colors
`mixColors` blends two colors together and returns the result. This is primarily used for Section Overlays, but it can also be used independently.
The `MixMode` determines the type of blending performed:
* ALPHA_BLENDING: Similar to Normal, but allows you to specify the percentage at which the first color is blended with the second.
* MULTIPLY: Multiplies the first color by the second.
* NORMAL: Same as `ALPHA_BLENDING`, but with a set blending level of 50%.

## Sample Colors
PixelMaestro comes with several predefined colors. These include primary colors (red, green, blue) as well as secondary and tertiary colors.
There are also two sample color arrays:
* `COLORWHEEL` contains a total of 12 primary, secondary, and tertiary colors.
* `RAINBOW` contains 7 varying colors.

[Home](README.md)
