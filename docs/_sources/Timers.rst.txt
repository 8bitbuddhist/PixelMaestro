
Timers
======

Timers track the passage of time for components with repeating actions, such as Animations and Canvases.

.. _timers-overview:
Overview
--------

Timers are used to determine when to perform a repeated action such as scrolling a Section or redrawing an Animation. There are two components to a Timer: the ``last_run_time`` and the ``interval``. The last_run_time stores the last time that the Timer executed, and the interval is the amount of time that must pass from the ``last_run_time`` before the Timer runs again. When the Timer does run, it sets a flag that its parent component watches for. The Timer then changes its ``last_run_time`` to the current time, and the process starts over.

Timers are designed to repeat - that is, if the ``interval`` is set to 1000 milliseconds, the Timer will fire every 1000 ms.

.. _timers-creating:
Creating a Timer
----------------

To create a Timer, pass in the amount of time (in milliseconds) before the Timer goes off. Update the Timer in a loop using ``Timer::update()``, passing in the program's current runtime. As long as the interval has not passed, ``update()`` returns true. Once the interval passes, the Timer runs and its ``update()`` method returns true. Immediately after this, the Timer returns false until the next interval.

The following Arduino example creates a Timer that performs an action every 5000ms:

.. code-block:: c++

   // ...
   Timer timer(5000);
   // ...
   void loop()
     if (timer.update(millis())) {
       // Perform some action
     }

You mostly likely won't need to interact with Timers directly. Any PixelMaestro component that uses a Timer will wrap its Timer in a ``set_timer()`` method. The functionality is the same, but it saves you the effort of having to create and run your own Timer objects.

.. _timers-interval:
Changing the Interval
---------------------

To change the update interval on an existing Timer, use ``Timer::set_interval()`` and pass in your new update interval.

.. code-block:: c++

   // Changes the interval to 10 seconds
   timer.set_interval(10000);

You can also change the Timer's last update time by using ``Timer::set_last_time()``. This is useful when synchronizing multiple Timers.

.. _timers-starting:
Starting and Stopping a Timer
-----------------------------

Timers include a ``start()`` and ``stop()`` method for starting and stopping the Timer, respectively. If a Timer is stopped, running ``Timer::update()`` will always return false and the last time will not update.
