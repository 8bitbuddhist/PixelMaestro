
Maestros
========

Maestros are the top-level objects in PixelMaestro. They coordinate all other components including :doc:`Sections <Sections>`, :doc:`Shows <Shows>`, and :doc:`CueControllers <Cues>`. Maestros also control global parameters such as the refresh rate and brightness level.

.. _maestros-creating:
Creating a Maestro
------------------

When initializing a Maestro, you'll need to assign one or more Sections to it. There are two ways to do this: implicitly, or explicitly.

With implicit initialization, the Maestro automatically creates the Sections for you. You just need to provide the dimensions of the Section(s) you want to create, and the number of Section(s) to create, in the Maestro's constructor. For example, this code creates a new Maestro with two 16 x 32 Sections:

.. code-block:: c++

   Maestro maestro(16, 32, 2);

With explicit initialization, you first create an array of Sections, then pass this array to the Maestro's constructor. This example creates three Sections with different sizes, then assigns them to the Maestro:

.. code-block:: c++

   int num_sections = 3;
   Section sections[] = {
       Section(10, 20),
       Section(20, 30),
       Section(30, 40)
   };
   Maestro maestro(sections, num_sections);

You can also use ``Maestro::set_sections()`` to set or reset the Maestro's Sections after it's been initialized.

.. _maestros-updating:
Updating the Maestro
--------------------

For PixelMaestro to work, the ``Maestro::update()`` method must be executed in a continuous loop (reference for `Arduino <https://www.arduino.cc/reference/en/language/structure/sketch/loop/>`_). Calling this method updates every other component managed by the Maestro and their subcomponents. This is necessary for updating Pixels, Animations, Canvases, Shows, etc.

Although ``Maestro::update()`` should be called continuously, the actual update interval is determined by the Maestro's ``refresh_interval``, which defaults to 50 milliseconds (or 20 refreshes per second). In other words, the Maestro will only update after 50ms have passed, including subcomponents. You'll need to pass the program's current runtime in milliseconds to ``Maestro::update()``. This method will return ``true`` if the Maestro needs to update, and ``false`` if it doesn't.

.. Tip:: ``Maestro::update()`` is non-blocking, which means it will not prevent other commands from running in the loop.

.. code-block:: c++

   if (maestro.update(runtime)) {
       // Maestro has updated. Place your other commands here.
   }

If you want to bypass the refresh interval check and force an update, add ``true`` as a parameter to ``Maestro::update()``.

.. code-block:: c++

   // Force the Maestro to update
   maestro.update(runtime, true);

.. _maestros-refresh-interval:
Changing the Refresh Interval
-----------------------------

The refresh interval is the amount of time (in milliseconds) between updates. This defaults to 50ms (or 20 updates per second). You can change the refresh interval using ``set_timer(interval)`` and get the current interval using ``get_timer()``. See :doc:`Timers <Timers>` for details.

.. _maestros-sections:
Interacting with Sections
-------------------------

You can retrieve a Section using ``get_section()``. Pass in the index of the desired Section. For more information, see the :doc:`Section documentation <Sections>`.

.. _maestros-brightness:
Setting a Global Brightness Level
---------------------------------

Use ``set_brightness()`` to set the brightness level for all Sections. Global brightness changes each individual Section's brightness by calling ``Section::set_brightness()``. Brightness ranges from 0 (off) to 255 (full).

.. _maestros-show:
Creating a Show
---------------

Shows let you plan out actions that will execute at a later point in the Mastro's runtime. For more information, see the :doc:`Show documentation <Shows>`.

.. _maestros-synchronizing:
Synchronizing Components
------------------------

Each component under a Maestro has one or more :doc:`Timers <Timers>` that tell it when to update. Although unlikely, these Timers may fall out of sync over time due to poor performance or latency. You can use ``Maestro::sync()`` to set each Timer's last run time to the same time. This ensures that going forward, each Timer starts from the same base time.
