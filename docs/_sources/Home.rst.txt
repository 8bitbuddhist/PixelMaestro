
Home
====

Welcome to the PixelMaestro documentation!

What is PixelMaestro?
---------------------

PixelMaestro is a graphics library for LED displays. It features 24-bit colors, a variety of animations and visual effects, support for drawing bitmap images, and much more. It's designed to be simple to use, flexible, and compatible with existing LED libraries such as `Adafruit's NeoPixel Library <https://github.com/adafruit/Adafruit_NeoPixel>`_ and `FastLED <http://fastled.io/>`_.

This documentation is for the core PixelMaestro library. For the desktop app, see the `PixelMaestro Studio documentation <https://8bitbuddhist.github.io/PixelMaestro-Studio/>`_.

Getting Started
---------------

To jump right in, see the `Tutorial <Tutorial>`_. You can find complete code examples in the `Arduino <https://github.com/8bitbuddhist/PixelMaestro/tree/master/examples/arduino>`_ folder.

To learn about PixelMaestro's architecture and components, see the :doc:`Components <Components>` page.

.. _home-faq:
FAQ
---

How do I change a Pixel's color?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Use :ref:`Section::set_pixel_color() <sections-setting-pixel-color>`. For example, to immediately turn a Pixel blue:

```c++
section.set_step_count(1);
section.set_pixel_color(0, 0, ColorPresets::Blue};
```

You can also use a :doc:`Canvas <Canvases>`, although this is a bit more complicated. See :ref:`How Pixels Work <pixels-how-pixels-work>` to learn more.

How do I connect my LEDs to PixelMaestro?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

PixelMaestro can't control LEDs directly, but you can use it with a library like `NeoPixel <https://github.com/adafruit/Adafruit_NeoPixel>`_ or `LightWS2812 <https://github.com/cpldcpu/light_ws2812>`_. On each loop, grab the color value of each ``Pixel``  using ``maestro.get_pixel_color(section_id, x_coordinate, y_coordinate)`` and pass it to the library.

Why am I getting poor performance / running out of memory?
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Performance is affected by:


* How much RAM your device has and how fast its CPU is
* The number of :doc:`Pixels <Pixels>`_ being rendered
* How many :ref:`Layers <section-layers>`_ you have active
* Whether you're using :doc:`Animations <Animations>` or :doc:`Canvases <Canvases>`
* Whether you're using :doc:`Cues <Cues>`_
* Any other libraries you are using simultaneously

For a device like an Arduino, your biggest limitation is memory. Each Pixel requires at least 3 bytes of RAM (one for each color channel). If fading is enabled (which it is by default), each Pixel requires 3 additional bytes to store its target color. If accurate fading is enabled (it's not by default), then each Pixel will require another 3 bytes. This means that a 10x10 grid needs anywhere between 300 and 900 bytes just to store color data.

Consider that adding a ``Layer`` doubles this amount, since it creates an entirely new framebuffer with the same dimensions as the base ``Section``. Adding an ``Animation`` or ``Canvas`` adds an additional byte per ``Pixel`` to track each Pixel's ``Palette`` color. You can reduce memory usage by tweaking :ref:`Pixel performance options <pixels-performance-options>`. Try using a library like `MemoryFree <https://github.com/McNeight/MemoryFree>`_ to monitor memory usage as you tweak your configuration and options.

For performance, PixelMaestro becomes slower as the number of Pixels and effects increases. If your device takes a long time to draw changes, try removing certain effects or decreasing the number of LEDs.
