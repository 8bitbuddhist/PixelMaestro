
Colors
======

The Colors class provides methods for creating and managing colors. Colors are stored as 24-bit objects, with 8 bits dedicated to each color channel (red, green, and blue). Colors are defined in the ``Colors::RGB`` struct and follow the `RGB color model <https://en.wikipedia.org/wiki/RGB_color_model>`_.

.. _colors-creating:
Creating Colors
---------------

To create a color, set each of the three color channels to a value between 0 (off) and 255 (full). The following example creates a solid blue color by setting the blue channel to full (255) and the red and green channels to 0.

.. code-block:: c++

   Colors::RGB blue = {0, 0, 255};

To create a random color, use ``Colors::generate_random_color()``.

Creating Color Palettes
------------------------

A :doc:`Palette <Palettes>` is a collection of one or more colors. Read the Palette documentation for details on how to create new Palettes.

The ``Colors`` class provides methods for populating color palettes. The ``generate_scaling_color_array()`` method generates a gradient of colors that scales from one color to another. Provide your initial color, target color, the ``Colors::RGB`` array you want to populate, and the number of colors to create, The ``generate_random_color_array()`` creates a completely random set of colors.

.. _colors-mixing:
Combining/Mixing Colors
-----------------------

You can blend two colors together using the ``mix_colors()`` method. There are a number of different color mixing options (as provided in the ``MixMode`` enum):

* Alpha: Blends the second color with the first color by the specified amount (0 - 255, where 0 is none and 255 is full).
* Multiply: Multiplies the first color by the second.
* Overlay: Returns the first color if the second color is black (black equals transparent).

You can also  set, add, subtract, multiply, and divide Colors directly:

.. code-block:: c++

   Colors::RGB red = {255, 0, 0};
   Colors::RGB blue = {0, 0, 255};
   Colors::RGB fuchsia = red + blue;   // {255, 0, 255}

.. _colors-sample:
Sample Colors
-------------

PixelMaestro comes with several predefined colors. These include the primary colors (red, green, blue), as well as secondary and tertiary colors. These are available in the ``ColorPresets`` class.

There are also two sample color palettes:


* ``Colorwheel`` contains a total of 12 primary, secondary, and tertiary colors.
* ``Rainbow`` contains 7 colors following the `ROYGBIV <https://en.wikipedia.org/wiki/ROYGBIV>`_ sequence.
