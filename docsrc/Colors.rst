
Colors
======

The Colors class provides methods for creating and managing colors. Colors are based on the RGB color model and are stored as 24-bit objects (8 bits dedicated to each color channel). Colors are defined by the ``Colors::RGB`` struct.

Creating Colors
---------------

To create a color, set each of the three color channels to a value between 0 (off) and 255 (full). The following example creates a solid blue color by setting the blue channel to full (255) and the red and green channels to 0.

.. code-block:: c++

   Colors::RGB blue = {0, 0, 255};

You can also create a completely random color by calling ``Colors::generate_random_color()``.

For color palettes, you can use the ``generate_scaling_color_array()`` method. Pass the initial color, the target color, the array that you want to populate, and the number of colors, and it will automatically create a gradient of colors from the starting color to the target color. You can also use ``generate_random_color_array()`` to create a completely random color set.

Mixing Colors
-------------

``mix_colors()`` blends two colors together and returns the result. This is primarily used for Section Layers, but it can also be used on its own. You can use a variety of different color mixing options (as provided in the ``MixMode`` enum):


* Alpha: Blends the second color with the first color by the specified amount (0 - 255, where 0 is none and 255 is full).
* Multiply: Multiplies the first color by the second.
* Overlay: Returns the first color if the second color is black (black equals transparent).

You can also  set, add, subtract, multiply, and divide Colors directly:

.. code-block:: c++

   Colors::RGB red = {255, 0, 0};
   Colors::RGB blue = {0, 0, 255};
   Colors::RGB fuchsia = red + blue;   // {255, 0, 255}

Sample Colors
-------------

PixelMaestro comes with several predefined colors. These include the primary colors (red, green, blue), as well as secondary and tertiary colors. These are available in the ``ColorPresets`` class.

There are also two sample color palettes:


* ``Colorwheel`` contains a total of 12 primary, secondary, and tertiary colors.
* ``Rainbow`` contains 7 colors following the `ROYGBIV <https://en.wikipedia.org/wiki/ROYGBIV>`_ sequence.
