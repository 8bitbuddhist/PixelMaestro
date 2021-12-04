
Home
====

Welcome to the PixelMaestro documentation!

What is PixelMaestro?
---------------------

PixelMaestro is a graphics library for LED displays. It features 24-bit colors, a variety of animations and visual effects, support for drawing bitmap images, and much more. It's designed to be simple to use, flexible, and compatible with existing LED libraries such as `Adafruit's NeoPixel Library <https://github.com/adafruit/Adafruit_NeoPixel>`_ and `FastLED <http://fastled.io/>`_.

This documentation is for the core PixelMaestro library. For the desktop app, see the `PixelMaestro Studio documentation <https://8bitbuddhist.github.io/PixelMaestro-Studio/>`_.

Contents
---------------

1. `Getting Started <Getting Started>`_: The basics of using PixelMaestro.
2. `Maestros <Maestros>`_: Initializing and use a Maestro.
3. `Sections <Sections>`_: Using Sections to manage your LEDs.
   1. `Points <Points>`_: Storing and interpreting x-y coordinates.
4. `Animations <Animations>`_: Using PixelMaestro's built-in animations.
5. `Colors <Colors>`_: Creating and managing colors.
   1. `Palettes <Palettes>`_: Storing multiple colors for use in Animations and Canvases.
6. `Pixels <Pixels>`_: Interacting with individual pixels and the Section framebuffer.
7. `Cues <Cues>`_: Storing PixelMaestro commands.
8. `Shows <Shows>`_: Scheduling PixelMaestro commands to run automatically.
9. `Timers <Timers>`_: How PixelMaestro schedules and times events.
10. `Components <Components>`_: The different components available in PixelMaestro and its architecture.

You can also find complete code examples in the `Arduino <https://github.com/8bitbuddhist/PixelMaestro/tree/master/examples/arduino>`_ folder.

.. _home-faq:
FAQ
---

How do I change a Pixel's color?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Use :ref:`Section::set_pixel_color() <sections-setting-pixel-color>`. For example, to immediately turn the first Pixel in the grid blue:

```c++
section.set_pixel_color(0, 0, ColorPresets::Blue};
```

See :ref:`How Pixels Work <pixels-how-pixels-work>` to learn more.

How do I connect PixelMaestro to my LEDs?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

PixelMaestro can't control LEDs directly, but you can combine it with an LED driver library like `FastLED <http://fastled.io/>`_, `NeoPixel <https://github.com/adafruit/Adafruit_NeoPixel>`_, or `LightWS2812 <https://github.com/cpldcpu/light_ws2812>`_. On each loop, grab the color value of each ``Pixel``  using ``maestro.get_pixel_color(section_id, x_coordinate, y_coordinate)`` and pass it to your LED library.

Why am I getting poor performance / running out of memory?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Performance is impacted by:


* How much RAM your device has and how fast its CPU is
* The number of :doc:`Pixels <Pixels>` being rendered
* How many :ref:`Layers <section-layers>` you have active
* Whether you're using :doc:`Animations <Animations>` or :doc:`Canvases <Canvases>`
* Whether you're using :doc:`Cues <Cues>`
* Any other libraries you are using simultaneously

For a device like an Arduino, your biggest limitation is memory. Each Pixel requires at least 3 bytes of RAM (one for each color channel). If fading is enabled (which it is by default), each Pixel requires 3 additional bytes to store its target color. If accurate fading is enabled (it's not by default), then each Pixel will require another 3 bytes. This means that a 10x10 grid needs anywhere between 300 and 900 bytes just to store color data.

Consider that adding a ``Layer`` doubles this amount, since it creates an entirely new framebuffer with the same dimensions as the base ``Section``. Adding an ``Animation`` or ``Canvas`` adds an additional byte per ``Pixel`` to track each Pixel's ``Palette`` color. You can reduce memory usage by tweaking :ref:`Pixel performance options <pixels-performance-options>`. Try using a library like `MemoryFree <https://github.com/McNeight/MemoryFree>`_ to monitor memory usage as you tweak your configuration and options.

For performance, PixelMaestro becomes slower as the number of Pixels and effects increases. If your device takes a long time to draw changes, try removing certain effects or decreasing the number of LEDs.
