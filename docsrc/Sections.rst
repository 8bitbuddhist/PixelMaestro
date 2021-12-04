
Sections
========

A `Section` is a virtual collection of :doc:`Pixels <Pixels>` laid out in a 2D grid. Sections are the PixelMaestro equivalent of a `framebuffer <https://en.wikipedia.org/wiki/Framebuffer>`_, containing a complete bitmap that can be sent to a set of LEDs for display. In addition to storing the framebuffer, Sections also manage any components that directly modify the framebuffer, particularly :doc:`Animations <Animations>` and :doc:`Canvases <Canvases>`.

Sections are managed by :doc:`Maestros <Maestros>`. A Section can only be assigned to one Maestro at a time.

.. _sections-creating:
Creating a Section
------------------

You can create and initialize a new Section in one of two ways: implicitly (or dynamically), or explicitly.

With implicit initialization, you can automatically create one or more Sections when you create the Maestro. To do this, declare a ``Maestro`` object, pass in the Section's dimensions, then pass in the number of Sections you want to create. For example, this allocates a single Section 128 pixels high and 256 pixels across.

.. code-block:: c++

   Maestro maestro(256, 128, 1);

.. Note:: A single Maestro can manage up to 256 Sections.

With explicit initialization, you create and manage the Sections yourself. This is useful if you want to manage them outside of a Maestro, but it adds an extra step. First, declare your Sections as an array, then assign them to the Maestro using ``Maestro::set_sections(Section* sections, uint8_t num_sections)``. Here, we create two Sections with two different dimensions (64 x 16 and 32 x 8) and assign them to the Maestro:

.. code-block:: c++

   Section sections[2] = {
       Section(64, 16),
       Section(32, 8);
   }
   Maestro maestro(sections, 2);

.. _sections-interacting:
Interacting With the Framebuffer
--------------------------------

The framebuffer (or pixel grid) is an in-memory representation containing each and every pixel in the Section. When you initialize a Section, PixelMaestro automatically creates a `two-dimensional array <https://www.cplusplus.com/doc/tutorial/arrays/#multidimensional>`_ made up of :doc:`Pixel <Pixels>` objects. This array uses a `Cartesian plane <https://en.wikipedia.org/wiki/Cartesian_coordinate_system>`_, with the origin (0, 0) starting in the top-left corner and increasing as you move to the right and down. For example, the coordinates (3, 5) represent a pixel 4 spaces to the right and 6 spaces down (remember that array indices start at 0).

.. _sections-retrieving-pixel-color:
Retrieving a Pixel's Color
^^^^^^^^^^^^^^^^^^^^^^^^^^

To get the color of any pixel, use ``Section::get_pixel_color(uint16_t x, uint16_t y)``, where ``x`` and ``y`` are the pixel's coordinates. This is the "final" color of the pixel, after post-processing effects have been applied (Canvases, Layers, brightness, etc.)

You can also get a pixel's "raw" color (the color before any effects have been applied) by using ``Section::get_pixel(x, y).get_color()``. This is better for low-power devices where CPU is at a premium, but it makes many PixelMaestro features unusable. It essentially limits you to using Animations and setting colors directly.

.. _sections-setting-pixel-color:
Setting a Pixel's Color
^^^^^^^^^^^^^^^^^^^^^^^

To change the color of a pixel directly, use ``Section::set_pixel_color(uint8_t x, uint8_t y, Colors::RGB& color)``. ``x`` and ``y`` are the pixel's coordinates, and ``color`` is an RGB representation of the color you want to set it to. For example, this sets the pixel 5 across and 10 down to the color blue:

.. code-block:: c++

   Colors::RGB blue = {0, 0, 255};
   section.set_pixel_color(4, 9, blue);

Note that your changes may be overwritten if you're using an Animation. To avoid this, disable the Animation or run ``set_pixel_color()`` after ``Maestro::update()``.

.. _sections-animating:
Displaying Animations
-------------------

Animations let you display dynamic visual effects. To learn more, see :doc:`Animations <Animations>`.

.. _sections-canvases:
Displaying Custom Shapes and Patterns
-------------------------------------

Canvases let you draw custom shapes and patterns. To learn more, see :doc:`Canvases <Canvases>`.

.. _sections-brightness:
Setting the Brightness Level
--------------------------

You can change the Section's overall brightness using ``Section::set_brightness(uint8_t brightness)``, which changes the luminosity of the framebuffer. You can set the brightness on a scale between 0-255, with 0 being unlit and 255 being fully lit.

.. _sections-layers:
Layering Sections
-----------------

A Layer is a second Section rendered on top of an existing Section. The color output of the second Section is merged with the base Section in real-time, creating a composite image. You can learn more about color merging in the :doc:`Colors <Colors>` document.

.. Warning:: Adding a Layer creates a new framebuffer, doubling the amount of RAM required. Be careful when using Layers on low-memory devices

.. image:: images/layer-example.png
   :target: _images/layer-example.png
   :alt: Layers

*Layering Section 2 (center) on top of Section 1 (left) using the alpha MixMode results in Section 3 (right).*

To create a Layer, use ``Section::set_layer(Colors::MixMode mix_mode, uint8_t alpha)``. ``MixMode`` is the method used to combine the Layer's colors with those of the base Section. If you're using the Alpha MixMode, ``alpha`` sets the amount that the Layer's colors are blended with the base's colors. Otherwise, it's not necessary.

This method returns a new ``Layer``, object, which contains a newly initialized ``Section`` that acts just like a normal Section. You can access the Layer using ``Section::get_layer()``, and you can access the Layer's Section using ``Section::get_layer()->section``. You can perform any action on this layered Section like you would a normal Section, including adding an Animation or Canvas.

Since any Section can have a Layer, you can stack Layers on top of other Layers by calling ``Layer::section.set_layer()``. For example, to add two new Layers onto a Section, you could use ``Section::get_layer()->section.set_layer()->section.set_layer()``.

.. code-block:: c++

   Section base(10, 10);
   ...
   // Creates a basic Wave Animation on the base Section
   Animation& section_animation = section.set_animation(AnimationType::WaveAnimation);
   section_animation.set_palette(ColorPresets::Colorwheel_Palette);

   // Creates a new Layer using the Alpha mixmode. The final color will be 50% of the base color and 50% of the overlaid color.
   Layer& layer = base.set_layer(Colors::MixMode::Alpha, 127);

   // Adds a Radial Animation to the Layer using the Colorwheel Palette
   Animation& layer_animation = layer.section->set_animation(AnimationType::RadialAnimation);
   layer_animation.set_palette(ColorPresets::Colorwheel_Palette);

.. _sections-scrolling:
Scrolling
---------

Scrolling shifts the framebuffer across the Section, making it appear as if the Section is moving. ``Section::set_scroll(uint16_t x_interval, uint16_t y_interval, bool x_reverse, bool y_reverse)`` sets both the speed and direction of the scroll across the x and y axes.

The interval (or speed) is measured in terms of how long it takes for one pixel to move from one end of the Section to the other. For example, an x interval of ``5000`` means it will take 5000 ms (or 5 seconds) for the Section to complete a single scroll across the x axis. ``reverse`` swaps the direction of the scroll. By default, scrolling on the x axis moves the grid from right to left, and scrolling on the y axis moves the grid from bottom to top.

.. Tip:: The scrolling speed can appear to change based on the size of the framebuffer. For example, a 10x10 grid will appear to scroll much slower than a 50x50 grid, even if they both have the same scroll interval. This is because the 50x50 grid needs to cover a larger distance (50 pixels) in the same amount of time that the smaller grid only needs to cover 10.

This example scrolls to the right once every 2000 milliseconds and down once every 1000 milliseconds.

.. code-block:: c++

   section.set_scroll(2000, 1000, false, true);

To disable scrolling on either axis, set its scroll rate to 0. You can also completely disable scrolling by calling ``Section::remove_scroll()``.

.. Tip:: Disabling scrolling will stop the grid in its current location. If you want to move the grid back to the center, set its :ref:`offset <offsetting>` to 0.

.. _sections-offsetting:
Offsetting
^^^^^^^^^^

Offsetting shifts the Section from its default position by a number of pixels. This is similar to :ref:`scrolling`, except it's a one-time operation.

.. Note:: If scrolling is enabled, the offset values will be overridden when the Section updates.

.. code-block:: c++

   section.set_offset(5, 1);

.. _sections-wrapping:
Wrapping
^^^^^^^^

When a Section is offset, wrapping displays pixels that have been shifted "out of bounds" on the other side of the grid. If wrapping is disabled, these pixels are instead not shown at all, and the "empty" space on the other side of the framebuffer will not be rendered at all.

.. code-block:: c++

    section.set_wrap(false);

.. _sections-mirroring:
Mirroring
---------

Mirroring shows a reflection of the Section across the center of the x or y axis.

.. code-block:: c++

   bool mirror_x = true;
   bool mirror_y = false;
   section.set_mirror(mirror_x, mirror_y);

.. _sections-scale:
Changing the Scale
------------------

You can change the scale of the Section, which changes the size of an individual pixel. This defaults to ``1, 1``.

.. code-block:: c+++

   section.set_scale(scale_x, scale_y);