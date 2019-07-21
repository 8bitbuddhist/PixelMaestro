
Points
======

A Point is a location on a grid identified by an x and y value. Points have a variety of applications such as storing the dimensions of a Section, locating an individual Pixel, or specifying the size of a shape drawn on a Canvas.

Creating a Point
----------------

Create a new Point by defining its x and y values respectively:

.. code-block:: c++

   int x = 5;
   int y = 10;
   Point point(x, y);

Coordinates Versus Dimensions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Points have two main purposes:


#. Identify a location/coordinate on a grid (e.g. a Pixel on a Section).
#. Define the size of a grid (e.g. the width and height of a Section).

When used as a coordinate, a Point is simply a point: a single x-y coordinate pair. For example, {2, 4} refers to a location 2 steps along the x-axis and 4 steps along the y-axis. When used as a dimension, a Point dictates how big the x and y axes are. In this case, {2, 4} indicates a grid that has 2 points along the x-axis and 4 points along the y-axis.

Syntactically, defining a dimension is the same as defining a coordinate. The only difference is how other components interpret the actual ``Point`` object.

Other Methods
-------------


* ``uint32_t Point::get_inline_index(x, y)``\ : When the Point is used as a dimension, this translates an x and y coordinate into an array index. This is especially useful for accessing Pixels, which are stored in 1-dimensional arrays.
* ``bool Point::in_bounds(uint16_t x, uint16_t y)``\ : When used a dimension, this checks whether the x or y values fall within the boundaries of the dimension. If so, it returns true.
* ``void Point::set(uint16_t x, uint16_t y)``\ : This changes the Point's x and y values to the new specified values.
* ``uint32_t Point::size()``\ : When the Point is used as a dimension, this identifies the size of the dimension by multiplying the x and y values.
