# Colors
The Colors class provides methods for creating and managing colors. Colors are based on the RGB color model and are stored as 24-bit objects with 8 bits dedicated to each color channel. Colors are defined by the `Colors::RGB` struct.

## Contents
1. [Creating Colors](#creating-colors)
2. [Manipulating Colors](#manipulating-colors)
3. [Generating Colors](#generating-colors)
4. [Mixing Colors](#mixing-colors)
5. [Sample Colors](#sample-colors)

## Creating Colors
The following example creates a solid blue color by setting the blue channel to full (255) and the red and green channels to 0.
```c++
Colors::RGB blue = {0, 0, 255};
```

## Manipulating Colors
You can directly set, add, subtract, multiply, and divide Colors:
```c++
Colors::RGB red = {255, 0, 0};
Colors::RGB blue = {0, 0, 255};
Colors::RGB fuchsia = red + blue;	// {255, 0, 255}
```

## Generating Colors
The `generate_random_color_array()` and `generate_scaling_color_array()` methods can quickly create new color palettes. Pass in a starting color, the array that you want to populate, and the number of colors you wish to generate. You can also provide additional parameters to tweak the output of the palette.

## Mixing Colors
`mix_colors()` blends two colors together and returns the result. This is primarily used for Section Overlays, but it can also be used on its own. You can use a variety of different color mixing options provided by the `MixMode` enum:
* ALPHA_BLENDING: Blends the second color with the first color by the specified percentage (e.g. 0.5 = 50%).
* MULTIPLY: Multiplies the first color by the second.
* NORMAL: Same as `ALPHA_BLENDING`, but with a set blending level of 50%.

## Sample Colors
PixelMaestro comes with several predefined colors. These include primary colors (red, green, blue) as well as secondary and tertiary colors.
There are also two sample color arrays:
* `COLORWHEEL` contains a total of 12 primary, secondary, and tertiary colors.
* `RAINBOW` contains 7 varying colors.

[Home](README.md)
