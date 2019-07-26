
Tutorial
========

This tutorial will show you how to use PixelMaestro to animate a 10x10 grid of LEDs.

Core Concepts
-------------

Let's start with the two most important components: ``Sections`` and ``Maestros``.

What's a Section?
^^^^^^^^^^^^^^^^^

A :doc:`Section <Sections>` is a 2D representation of a pixel grid stored entirely in RAM. Each pixel corresponds to an individual LED and stores the LED's current color. This virtual grid is known as a *framebuffer*, and ``Sections`` act as gateways between you, other components, and the framebuffer.

``Sections`` are also responsible for managing components that interact with the framebuffer, such as :doc:`Animations <Animations>` and :doc:`Canvases <Canvases>`.

What's a Maestro?
^^^^^^^^^^^^^^^^^

A :doc:`Maestro <Maestros>` manages all other PixelMaestro components, particularly ``Sections`` and :doc:`Shows <Shows>`. They also store global parameters (such as the refresh rate). ``Maestros`` are essential for timing: they ensure that all components are continuously kept up-to-date and synchronized. For this reason, you should only create a single ``Maestro`` when using PixelMaestro.

Most important, a ``Maestro`` directly manages ``Sections``. A ``Maestro`` can manage one or more ``Sections``, but a ``Section`` can only be assigned to one ``Maestro``.

Using PixelMaestro
------------------

There are four steps to using PixelMaestro in your app:


#. Initialize a new ``Maestro`` object and any ``Sections`` that it will manage.
#. Configure the ``Maestro`` and ``Section(s)``. This might include adding ``Animations``, drawing ``Canvases``, enabling ``Shows``, etc.
#. Run the Maestro's ``update()`` method in a continuous loop and provide it with the application's current runtime in milliseconds.
#. Copy the contents of the ``Section's`` framebuffer to the output device. The exact implementation will vary depending on the type of device you're outputting to.

Sample Sketch
^^^^^^^^^^^^^

Below is a sample Arduino sketch created using `PlatformIO <http://platformio.org/>`_. It creates a ``Section`` containing a 10x10 grid and starts a blinking animation using a pre-defined color palette.

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
        * update() is non-blocking, so you can run other actions in the loop.
        */
       if (maestro.update(millis())) {
           // Step through the grid and retrieve each pixel's color.
           for (unsigned char y = 0; y < maestro.get_section(0)->get_dimensions().y; y++) {
               for (unsigned char x = 0; x < maestro.get_section(0)->get_dimensions().x; x++) {
                   Colors::RGB pixel_color = maestro.get_pixel_color(0, x, y);
                   // Here you would add code to send pixel_color to the corresponding LED.
               }
           }
       }
   }
