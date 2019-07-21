
Palettes
========

``Palettes`` store colors used to draw Animations and Canvases.

Creating a Palette
------------------

To create a Palette, pass in an array of colors (\ ``Colors::RGB`` objects) and the number of colors in the array.

.. Tip:: Palettes can store up to 255 colors. The last color (index 255) is reserved for transparency.

For example, let's create a Palette with three colors: red, green, and blue:

.. code-block:: c++

   const int num_colors = 3;
   Colors::RGB colors[num_colors] = {
     {255, 0, 0},  // red
     {0, 255, 0},  // green
     {0, 0, 255}   // blue
   };
   Palette* palette = new Palette(colors, num_colors);

Using a Palette
---------------

Palettes are used in ``Animations`` and ``Canvases``. You can assign a Palette by calling each component's ``set_palette()`` method. Since components don't modify Palettes, you can reuse the same Palette with multiple components.

.. code-block:: c++

   Palette my_palette = ColorPresets::Colorwheel_Palette;
   animation.set_palette(my_palette);
   canvas.set_palette(my_palette)

Changing Colors
---------------

Use ``set_colors()`` to swap a Palette's color array for a new one.

Retrieving Colors
-----------------

Palettes provide multiple methods for getting colors. To retrieve a specific color from the Palette, use ``get_color_at_index(int index)`` and provide the index of the desired color. To get every color, use ``get_colors()`` and ``get_num_colors()``.
