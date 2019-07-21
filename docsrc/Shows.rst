
Shows
=====

Shows let you schedule the execution of `Cues <Cues.html>`_ at various points over the Maestro's runtime. Using a Show, you can create a list of actions that will automatically play out as the Maestro runs.

Creating a Show
---------------

To create a Show, call ``Maestro::set_show()`` and pass in an array of `Events <#adding-events>`_. To remove a Show, use ``Maestro::remove_show()``.

.. Note:: ``set_show()`` automatically initializes the `CueController <Cues.html>`_ if you haven't already done so, but you'll still need to `enable the necessary CueHandlers <Cues.html>`_ before any ``Events`` can be processed.

Adding Events
-------------

An ``Event`` is an object that stores an action to perform (a ``Cue``\ ) and the time that the action will be executed. Events consist of:


* The ``time`` when the Event will run (in milliseconds), and
* The `Cue <Cues.html>`_ that runs when the Event executes.

An Event is executed when the program's runtime (in milliseconds) matches or exceeds its ``time``. When an Event runs, its ``Cue`` is loaded and executed by the Maestro. After an Event executes, the Show automatically moves to the next Event in the queue so that each Event runs sequentially.

You can pass an Event list when creating the Show using ``Maestro::set_show()``. You can also change the Event list mid-show using ``Show::set_events()``.

This example creates two Events: one that adds a new Canvas, and one that draws a circle onto the newly created Canvas. Both of these events occur 5 seconds (5000 milliseconds) into the Maestro's runtime. This means that after 5000 milliseconds, the Show executes the first Event, then immediately executes the second Event.

.. code-block:: c++

   #include "cue/canvascuehandler.h"
   #include "cue/event.h"
   #include "cue/sectioncuehandler.h"

   // Create 10x10 Maestro
   Maestro maestro(10, 10);

   // Initialize Event list
   int num_events = 2;
   Event events[num_events] = {
       Event(5000, section_handler.set_canvas(0, 0)),
       Event(5000, canvas_handler.draw_circle(0, 0, Colors::Green, 5, 5, 2, true))
   }

   // Initialize the show
   Show& show = maestro.set_show(events, num_events);

Timing Modes
------------

The timing mode determines how the Show tracks time between Events. Shows can use one of two timing modes: relative or absolute.

*Relative time* tracks the amount of time since the last Event executed. For example, if Event 1 has a time of 1000 and Event 2 has a time of 2000 ms, Event 1 executes 1000 ms after the program starts, and Event 2 executes 2000 ms after Event 1.

*Absolute time* tracks the amount of time since the program started. Using the above example, Event 1 executes 1000 ms after the program starts, and Event 2 executes 2000 ms after the program starts (1000 ms after Event 1 starts).

To set the timing mode, use ``Show::set_timing_mode()``.

.. code-block:: c++

   // Use relative time
   show.set_timing_mode(Show::TimingMode::Relative);

Looping
-------

After a Show completes its last Event, it won't do anything. However, with looping enabled, the Show will jump back to the first event and repeat indefinitely. To enable looping, call ``Show::set_looping(boolean)``. To determine whether a Show is looping, call ``Show::get_looping()``. Looping only works when using relative time.
