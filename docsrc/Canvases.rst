
Canvases
========

Canvases let you draw custom shapes and images onto a Section similar to an image editor.

Overview
--------

A ``Canvas`` is a drawing surface where you can create shapes, write text, free draw, and add other objects to your Section.


.. image:: images/palette-canvas.png
   :target: images/palette-canvas.png
   :alt: Canvas


*A ``Canvas`` with its associated palette.*

Canvases are rendered after Animations, meaning you can draw a Canvas on top of an Animation. Like `Animations <Animations.html>`_\ , Canvases rely on ``Palettes``. Canvases are transparent by default.

.. Tip:: The same ``Palettes`` can be used for both ``Animations`` and ``Canvases``.

Creating a Canvas
-----------------

Create a new Canvas using ``Section::set_canvas(uint16_t num_frames)``. ``num_frames`` is an optional parameter for creating `animated canvases <#animating-a-canvas>`_. By default, Canvases have a single frame. Frames are described in more detail in the section `Animating a Canvas <#animating-a-canvas>`_.

.. code-block:: c++

   // Declare a new Canvas with a single frame
   Canvas& canvas = section.set_canvas();

To create an animated ``Canvas``\ , set the number of frames to 2 or more.

.. code-block:: c++

   int num_frames = 10;
   // Declare a new Canvas with 10 frames
   Canvas& canvas = section.set_canvas(num_frames);

Setting the Palette
^^^^^^^^^^^^^^^^^^^

Canvases require you to set a `Palette <Palettes.html>`_. Use ``Canvas::set_palette(Palette& palette)`` to set the palette.

.. code-block:: c++

   Canvas& canvas = section.set_canvas();
   canvas.set_palette(ColorPresets::Colorwheel_Palette);

Animating a Canvas
------------------

Canvases can also display animations. Unlike `Section Animations <Animations.html>`_\ , which use dynamically generated patterns, animated Canvases allow for a much higher degree of customization.


Frames
^^^^^^

The area that you draw on a Canvas is called a ``frame``. A frame is a drawing surface that shares the dimensions of its parent Section. When a Canvas has more than one frame, it renders each frame on a set interval, essentially turning it into a video player.

You can specify the number of frames when initializing the Canvas using ``Section::set_canvas()``. You can also change the number of frames in an existing Canvas using ``Canvas::set_num_frames()``. Note that this will **\ *delete*\ ** the current frame set. You can change the amount of time (in milliseconds) between frames using ``Canvas::set_frame_timer(milliseconds)``.

Switching Frames
^^^^^^^^^^^^^^^^

The Canvas keeps track of the frame that's currently displayed. This is known as the *active frame.* Any `drawing <#drawing-shapes>`_ actions performed on the Canvas are done on the active frame.

To draw on a different frame, first switch to the frame using ``set_current_frame_index(index)``. You can also use ``next_frame()`` to change to the next available frame (or to the first frame if you're currently on the last frame). To get the index of the current frame, use ``get_current_frame_index()``.

Drawing Shapes
--------------

You can draw on a Canvas using one of the following ``draw`` methods. Each method requires a starting point (as x and y coordinates), an ending point (or size), and extra parameters specific to the shape or pattern.

Canvases use the same Cartesian coordinate system as Sections to track Pixels. The origin (0, 0) is at the top-left corner of the grid, with positive values moving to the right and down. For example, (5, 10) means 5 pixels to the right and 10 pixels down.

Selecting a Color
^^^^^^^^^^^^^^^^^

When drawing, you must specify the color that you want to draw in according to its index in the ``Palette``. Each ``draw`` method requires this index as a parameter to determine how to draw the shape.

.. code-block:: c++

   // Draws a single point 10 Pixels to the right and 10 Pixels down using the 6th color in the Palette index
   canvas.draw_point(6, 10, 10);

Lines
^^^^^

The ``draw_line()`` method draws a line from one point to another. Enter the coordinate where the line starts and the coordinate where the line ends.

.. code-block:: c++

   // Draw a 10 Pixel long diagonal line
   canvas.draw_line(0, 0, 0, 10, 10);

Points
^^^^^^

The ``draw_point()`` method draws a single point. You can erase the point using ``erase_point()``.

.. code-block:: c++

   // Draw a single point 5 pixels under the origin, then erase it.
   canvas.draw_point(0, 0, 5);
   canvas.erase_point(0, 5);

Rectangles
^^^^^^^^^^

The ``draw_rect()`` method draws a basic non-rotated rectangle with the specified origin, size, and whether to ``fill`` the rectangle or just draw the outline.

.. code-block:: c++

   // Draw the outline of a 10 x 10 rectangle
   bool fill = false;
   canvas.draw_rect(0, 0, 0, 10, 10, fill);

Text
^^^^

Drawing text requires ``Fonts``\ , which take up a relatively significant amount of RAM and program space. Because of this, they are disabled by default. To enable them, add the ``CANVAS_ENABLE_FONTS`` preprocessor directive to your project. In the Arduino IDE, add ``#define CANVAS_ENABLE_FONTS`` to the top of your .ino file. In PlatformIO, add the following to your platformio.ini file:

.. code-block:: ini

   [common]
   build_flags = -D CANVAS_ENABLE_FONTS

The ``draw_text()`` method draws a string of characters. Specify the origin, a ``Font``\ , and the ``text`` to display. As of this writing, the only font available is the included `5x8 font <../blob/master/src/canvas/fonts/font5x8.h>`_.

.. code-block:: c++

   // Draws "PixelMaestro" at the Canvas' origin in a 5x8 font
   Font *font = new Font5x8();
   canvas.draw_text(0, 0, 0, *font, "PixelMaestro");

Triangles
^^^^^^^^^

The ``draw_triangle()`` method draws a triangle with the three specified coordinates. You can also ``fill`` the triangle, or just draw an outline.

.. code-block:: c++

   // Draws a filled in right-angle triangle 10 pixels high and 10 pixels wide
   canvas.draw_triangle(0, 0, 0, 10, 0, 0, 10, true);

Clearing the Canvas
^^^^^^^^^^^^^^^^^^^

Use ``clear()`` to erase the entire Canvas (including all frames). You can clear a single Pixel using the ``erase_point()`` method. Note that once you clear a Canvas, there's no way to recover its contents.
