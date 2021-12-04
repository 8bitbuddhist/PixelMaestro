
Getting Started
===============

This guide will show you the basics of how to use PixelMaestro.

Key Concepts
-------------

There are two key concepts in PixelMaestro: ``Sections`` and ``Maestros``.

What's a Section?
^^^^^^^^^^^^^^^^^

A :doc:`Section <Sections>` is a virtual representation of an LED grid. This is commonly called a `*framebuffer* <https://en.wikipedia.org/wiki/Framebuffer>`_, and it stores a set of pixels using `Cartesian coordinates <https://en.wikipedia.org/wiki/Cartesian_coordinate_system>`. In PixelMaestro, each virtual LED is represented by a :doc:`Pixel <Pixels>`. ``Sections`` also manage other PixelMaestro components that modify the framebuffer, such as :doc:`Animations <Animations>` and :doc:`Canvases <Canvases>`.


What's a Maestro?
^^^^^^^^^^^^^^^^^

:doc:`Maestros <Maestros>` are controllers that manage multiple different PixelMaestro components, especially ``Sections``. They are controllers that manage timing, refreshing, and other global controls. They also manage :doc:`Cues <Cues>` and :doc:`Shows <Shows>`.

.. Note:: A ``Maestro`` can manage multiple ``Sections`` simultaneously, but a ``Section`` can only be assigned to one ``Maestro`` at a time.

Using PixelMaestro
------------------

Now that you know how PixelMaestro works, here's how you use it. There are four steps:

#. Create a new ``Maestro`` and any ``Sections`` that it will manage.
#. Configure the ``Maestro`` and ``Section(s)`` by adding ``Animations``, ``Canvases``, ``Shows``, etc.
#. Create a continuous loop in your application and add ``maestro.update(runtime)``, where ``runtime`` is the application's current runtime in milliseconds.
#. Retrieve the color of each pixel in the framebuffer using ``maestro.get_pixel_color(section, x, y)``, then pass it to your output device. The details will vary depending on the device you're outputting to, the LED library you're using, and the physical configuration of your LEDs.

Example: Creating an Animated 10x10 Grid
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Here's an example sample Arduino sketch created using `PlatformIO <http://platformio.org/>`_. This example displays a blinking animation made of a rainbow color palette on a 10 x 10 LED grid. You can find a complete example in the `examples/Arduino <https://github.com/8bitbuddhist/PixelMaestro/blob/master/examples/arduino/Blink/Blink.cpp>`_ folder.

First, we initialize a ``Maestro``. Passing `10`, `10`, and `1` in the Maestro's constructor means the Maestro will automatically initialize a single 10 x 10 ``Section``, which we can access using ``maestro.get_section(0)``. Next, we apply an ``Animation`` to the Section. An :doc:`Animation <Animations>` is a dynamically generated pattern: in this case, the pattern alternates between showing the color palette, and turning the LEDs off. ``Animations`` use :doc:`Palettes <Palettes>` which are collections of colors. PixelMaestro comes with some pre-defined colors and palettes in the `colorpresets <https://github.com/8bitbuddhist/PixelMaestro/blob/master/src/colorpresets.h>`_ class, which we'll use here. We'll also change some of the Animation's settings by increasing the animation speed using ``animation.set_timer(500)``, and by disabling smooth fading so that the colors change immediately by using ``animation.set_fade(false)``.

Finally, in the ``loop()`` function, we update the Maestro using ``maestro.update(millis)``, where ``millis`` is the current runtime. This function runs through all of the different PixelMaestro components we initialized, performs any updates, then draws to the LED framebuffer. However, the framebuffer still only exists in memory: we still need to update our physical LEDs. To do this, we'll loop over each individual pixel in the framebuffer and send its color data to the corresponding LED. First, we'll iterate over the ``y`` axis, then the ``x`` axis. We find the maximum height and width of the Section using ``maestro.get_section(0)->get_dimensions()``. Then, we get the pixel's raw color value using ``maestro.get_pixel_color(0, x, y)``, where ``0`` is the numeric index of the Section we want to retrieve the color from (remember that a Maestro can manage multiple Sections). We store this value in ``pixel_color``. Now, we just need to pass the r, g, and b values from ``pixel_color`` to our LED library, then send it out to the LED.

.. code-block:: c++

   #include <Arduino.h>
   #include <PixelMaestro/animation/blinkanimation.h>
   #include <PixelMaestro/colorpresets.h>
   #include <PixelMaestro/core/colors.h>
   #include <PixelMaestro/core/maestro.h>

   using namespace PixelMaestro;

   /*
    * Create a Maestro with a single 10x10 Section.
    */
   Maestro maestro(10, 10, 1);

   void setup () {
       Section* section = maestro.get_section(0);

       /*
        * Create and configure a Blink Animation.
        * The ColorPresets class provides several pre-built colors and palettes.
        * We'll decrease the Animation's cycle time (making it blink every second) and disable fading.
        */
       Animation& animation = section->set_animation(AnimationType::Blink);
       animation.set_palette(ColorPresets:Rainbow_Palette);
       animation.set_timer(500);
       animation.set_fade(false);
   }

   void loop() {
       /*
        * Update the Maestro. This refreshes every component including the Section and its Animation.
        * Note that update() is non-blocking, so you can run other actions in this loop.
        */
       if (maestro.update(millis())) {
           // Step through the grid.
           for (unsigned char y = 0; y < maestro.get_section(0)->get_dimensions().y; y++) {
               for (unsigned char x = 0; x < maestro.get_section(0)->get_dimensions().x; x++) {
                   // Retrieve the pixel's color.
                   Colors::RGB pixel_color = maestro.get_pixel_color(0, x, y);

                   // Here you would add code to send pixel_color to your output device.
               }
           }
       }
   }

And that's it! If you want to see how this works with an LED library, check out the `examples <https://github.com/8bitbuddhist/PixelMaestro/tree/master/examples/arduino>`_. From here, try playing around with different :doc:`Animations <Animations>`, or try using a :doc:`Canvas <Canvases>`. When you're ready to move onto more advanced features, check out :doc:`Cues <Cues>` and :doc:`Shows <Shows>`.