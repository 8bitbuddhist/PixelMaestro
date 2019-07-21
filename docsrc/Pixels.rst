
Pixels
======

A Pixel represents a single LED. Pixels are used to store color values until they can be sent to an output device.

Creating Pixels
---------------

Pixels don't take any parameters. Pixels are automatically allocated and managed by Sections, so you shouldn't have to initialize one yourself.

.. code-block:: c++

   Pixel pixel();

.. Important:: While you *can* work with Pixels directly, it's much easier to manage them through a Section. Even if you only need a single Pixel, you should still create a 1x1 Section and use it to control the Pixel.

How Pixels Work
---------------

Each Pixel stores two key bits of information: its ``current_color_`` and ``step_``.

``current_color_`` is the color that the Pixel is set to right now. You can access this color using ``Pixel::get_color()``\ , ``Section::get_pixel_color(x, y)`` or ``Maestro::get_pixel_color(section, x, y)``.

``step_`` is an array used to fade the Pixel to its new color. It stores the amount that each color channel will increment by when calling the Pixel's ``update()`` method. For example, if the Pixel is currently black and you want to set it to white, ``step_`` stores ``{255, 255, 255}``. On ``update()``\ , the value of ``step_`` is applied to ``current_color_``\ , changing it to white.

In order to support gradual color transitions (i.e. fading), the Pixel's parent Section stores a ``step_count_``. ``step_count_`` tracks the number of iterations the Pixel must go through before it reaches its target color. For example, if the Pixel the Pixel is currently black, and you want it to fade to white over 5 frames, you can use:

.. code-block:: c++

   section.set_step_count(5);
   section.set_pixel_color(x, y, ColorPresets::White);

Now instead of storing ``{255, 255, 255}`` in ``step_``\ , the Pixel stores ``{51, 51, 51}``. Note that ``set_step_count()`` applies to *all* Pixels managed by the Section, and will automatically decrement on each ``update()``.

.. Tip:: Setting ``step_count_`` to ``1`` before using ``set_next_color()`` will force the color to change immediately. Otherwise, the color will fade.

.. code-block:: c++

   // Change colors immediately
   section.set_step_count(1);
   section.set_pixel_color(x, y, ColorPresets::Black);

Calling a Pixel's ``update()`` method triggers an immediate refresh of the Pixel. As long as the ``step_count_`` is greater than 0, the Pixel will step towards its next color. ``update()`` is automatically called by the Pixel's parent ``Section`` when it updates.

Performance Options
-------------------

Disabling Fading
^^^^^^^^^^^^^^^^

To save on RAM, you can disable fading by enabling the ``PIXEL_DISABLE_FADING`` preprocessor directive, which reduces each Pixel's RAM use from 6 bytes to 3. In the Arduino IDE, add ``#define PIXEL_DISABLE_FADING`` to the top of your .ino file. In PlatformIO, add the following to your platformio.ini file:

.. code-block:: ini

   [common]
   build_flags = -D PIXEL_DISABLE_FADING

Enabling Accurate Fading
^^^^^^^^^^^^^^^^^^^^^^^^

When fading is enabled, each Pixel calculates a ``step_`` value, which is the difference between its current color and its next color. ``step_`` is not 100% accurate, especially for small changes or long fade intervals.

To rectify this, each Pixel can store its target color in the ``next_color_`` variable, then apply the color at the end of the fade period. This guarantees that the Pixel reaches its target color, but uses an additional 3 bytes of RAM. Accurate fading is disabled by default, but you can enable it by adding the ``PIXEL_ENABLE_ACCURATE_FADING`` preprocessor directive. In the Arduino IDE, add ``#define PIXEL_ENABLE_ACCURATE_FADING`` to the top of your .ino file. In PlatformIO, add the following to your platformio.ini file:

.. code-block:: ini

   [common]
   build_flags = -D PIXEL_ENABLE_ACCURATE_FADING

.. Note:: Accurate fading requires fading to be enabled.
