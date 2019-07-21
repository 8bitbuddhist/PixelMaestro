
Maestros
========

Maestros are the brains behind PixelMaestro. They coordinate all other components including `Sections <Sections.html>`_\ , `Shows <Shows.html>`_\ , and `CueControllers <Cues.html>`_. Maestros also control global parameters such as the refresh rate and brightness level.

Creating a Maestro
------------------

When initializing a Maestro, pass in the number of Sections that you want to create and the dimensions you want to use when creating them. For example, this code createes a Maestro with two 16 x 32 Pixel Sections:

.. code-block:: c++

   Maestro maestro(16, 32, 2);

Note that these Sections will be deleted when the Maestro is deleted.

You can also pass an array of Sections with different dimensions. This example assigns three Sections with different sizes:

.. code-block:: c++

   int num_sections = 3;
   Section sections[] = {
       Section(10, 20),
       Section(20, 30),
       Section(30, 40)
   };
   Maestro maestro(sections, num_sections);

You can also use ``Maestro::set_sections()`` to set or reset the Maestro's Sections.

Updating the Maestro
--------------------

Maestros are responsible for updating all other components. This is done through the ``Maestro::update()`` method.

The time between updates is determined by the Maestro's ``refresh_interval``\ , which defaults to 50 milliseconds (or 20 refreshes per second). This means that every 50ms, every single component under the Maestro's control (Sections, Animations, Layers, Shows, etc.) runs through its update routine. ``Maestro::update()`` is non-blocking, meaning it will not prevent other tasks from running on the same thread.

The best way to call ``Maestro::update()`` is by running it in a continuous loop in your application. Pass in the program's current runtime (in milliseconds). If the Maestro is due for an update, then ``update()`` returns true. Otherwise, it returns false.

.. code-block:: c++

   if (maestro.update(runtime)) {
       // Run other methods here
   }

If you want to bypass the runtime check and force an immediate update, add ``true`` as a parameter to ``Maestro::update()``.

.. code-block:: c++

   // Force the Maestro to update
   maestro.update(runtime, true);

Changing the Refresh Interval
-----------------------------

The refresh interval is the amount of time (in milliseconds) between updates. This defaults to 50ms (or 20 updates per second). This interval is stored as a `Timer <Timers.html>`_. You can change the refresh interval using ``set_timer(interval)`` and get the current interval using ``get_timer()``.

Interacting with Sections
-------------------------

You can retrieve a Section using ``get_section()``. Pass in the index of the desired Section. For more information, see the `Section documentation <Sections.html>`_.

Setting a Global Brightness Level
---------------------------------

Use ``set_brightness()`` to set a global brightness level for all Sections. Global brightness changes each individual Section's brightness by calling ``Section::set_brightness()``. Brightness ranges from 0 (off) to 255 (full).

Creating a Show
---------------

Shows let you plan out actions that will execute at a later point in the Mastro's runtime. For more information, see the `Show documentation <Shows.html>`_.

Synchronizing Components
------------------------

Each component under a Maestro has one or more `Timers <Timers.html>`_ that tell it when to update. Although unlikely, these Timers may fall out of sync over time due to poor performance or latency. You can use ``Maestro::sync()`` to set each Timer's last run time to the same time. This ensures that going forward, each Timer starts from the same base time.
