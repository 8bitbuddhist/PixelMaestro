
Components
==========

.. _components-primary:
Primary Components
------------------


* :doc:`Maestros <Maestros>` are responsible for managing all other components. They also manage global options such as the refresh rate, pixel brightness, and :doc:`event queue <Shows>`.

  * :doc:`Cues <Cues>` are serialized PixelMaestro commands. Cues can be stored for later execution via a :doc:`Show <Shows>`, saved to a file, or transmitted to another device.
  * :doc:`Shows <Shows>` let you schedule events to run at a later point in the Maestro's lifetime.
  * :doc:`Sections <Sections>` manage individual :doc:`Pixels <Pixels>` and arrange them into grids. Sections also coordinate :doc:`Animations <Animations>` and :doc:`Canvases <Canvases>`.

    * :doc:`Animations <Animations>` render visual effects on a Section.
    * :doc:`Canvases <Canvases>` let you draw shapes, patterns, and custom animations onto a Section.

.. _components-secondary:
Secondary Components
--------------------


* :doc:`Palettes <Palettes>` store colors used to draw Animations, Canvases, and other color-based components.

  * :doc:`Colors <Colors>` store individual colors as 24-bit RGB values (8 bits for red, green, and blue each). The Colors class also provides tools for generating custom colors and color palettes.
  * ColorPresets provide commonly used colors and color palettes.

* :doc:`Pixels <Pixels>` store color values for individual LEDs. They also handle color changes and color blending caused by Animations. Pixels are managed by Sections.
* :doc:`Points <Points>` identify specific locations on a Pixel grid. They're also used to define the size of grids for Sections, Canvases, and other components.
* :doc:`Timers <Timers>` track time intervals for many PixelMaestro components such as Maestros, Animations, and Canvases. They determine when each component updates by comparing its update interval to the program's current runtime.
* The ``Utility`` class stores commonly used functions.
