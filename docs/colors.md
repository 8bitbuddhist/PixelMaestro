# Colors
The Colors class provides methods for creating and interacting with colors. Colors are based on the RGB color model and are therefore stored as 24-bit variables with 8 bits dedicated to each color channel. Colors are defined by the `Colors::RGB` struct.
```c++
Colors::RGB blue = {0, 0, 255};
```

## Manipulating Colors
The `Colors::RGB` enum contains overridden operators for setting, adding, subtracting, and comparing colors.

## Generating Colors
The `generateRandomColorArray` and `generateScalingColorArray` methods are designed for quickly creating new colors. Pass in a seed color, a destination color array, and the number of colors you wish to generate. The methods will automatically populate the array with the number of new colors requested.

## Mixing Colors
The `mixColors` method allows you to blend two colors together and returns the result. This is primarily used for overlaying one Section on top of another.
The MixMode determines the type of blending performed:
* NORMAL: Simply calculates the average of both colors.
* ALPHA_BLENDING: Allows you to specify how much of the second color is applied to the first. This essentially lets you set the transparency of the second color.
* OVERLAY: Uses the second color to essentially calculate the transparency of the first color.

## Sample Colors
PixelMaestro provides several pre-defined colors out of the box. These include primary colors (red, green, blue), as well as some secondary and tertiary colors.
There are also two sample color arrays: COLORWHEEL and RAINBOW.

[Home](Readme.md)
