
Components
==========

Primary Components
------------------


* **\ `Maestros <Maestros.html>`_\ ** are responsible for managing all other components. They also manage global options such as the refresh rate, pixel brightness, and `event queue <Shows.html>`_.

  * **\ `Cues <Cues.html>`_\ ** are serialized PixelMaestro commands. Cues can be stored for later execution via a `Show <Shows.html>`_\ , saved to a file, or transmitted to another device.
  * **\ `Shows <Shows.html>`_\ ** let you schedule events to run at a later point in the Maestro's lifetime.
  * **\ `Sections <Sections.html>`_\ ** manage individual `Pixels <Pixels.html>`_ and arrange them into grids. Sections also coordinate `Animations <Animations.html>`_ and `Canvases <Canvases.html>`_.

    * **\ `Animations <Animations.html>`_\ ** render visual effects on a Section.
    * **\ `Canvases <Canvases.html>`_\ ** let you draw shapes, patterns, and custom animations onto a Section.

Secondary Components
--------------------


* **\ `Palettes <Palettes.html>`_\ ** store colors used to draw Animations, Canvases, and other color-based components.

  * **\ `Colors <Colors.html>`_\ ** store individual colors as 24-bit RGB values (8 bits for red, green, and blue each). The Colors class also provides tools for generating custom colors and color palettes.
  * **ColorPresets** provide commonly used colors and color palettes.

* **\ `Pixels <Pixels.html>`_\ ** store color values for individual LEDs. They also handle color changes and color blending caused by Animations. Pixels are managed by Sections.
* **\ `Points <Points.html>`_\ ** identify specific locations on a Pixel grid. They're also used to define the size of grids for Sections, Canvases, and other components.
* **\ `Timers <Timers.html>`_\ ** track time intervals for many PixelMaestro components such as Maestros, Animations, and Canvases. They determine when each component updates by comparing its update interval to the program's current runtime.
* **Utility** stores commonly used functions.
