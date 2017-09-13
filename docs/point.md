# Point
A Point is a single location on a grid specified by an x and y value. Points have a variety of applications from tracking the size of a Section to locating individual Pixels to drawing shapes on a Canvas.

## Contents
1. [Coordinates Versus Layouts](#coordinates-versus-layouts)
2. [Creating a Point](#creating-a-point)
3. [Other Methods](#other-methods)

## Coordinates Versus Layouts
Points have two main purposes:
1. Identify a location on a grid (e.g. a Pixel in a Section)
2. Determine the size of a grid (e.g. the total number of values on the x and y axes).
When used as a location identifer, a Point is simply a point: a single x-y coordinate on a grid. {2, 4} refers to a location 2 steps along the x-axis and 4 steps along the y-axis. When used as a size identifier, a Point dictates how big the x and y axes are. {2, 4} then refers to a grid that _has_ 2 steps along the x-axis and 4 steps along the y-axis. You might see the first use referred to as a _coordinate_, and the second use referred to as a _layout_.

## Creating a Point
Create a new Point by defining its x and y values:
```c++
int x = 5;
int x = 10;
Point* point = new Point(x, y);
```

## Other Methods
* `Point::set(unsigned short x, unsigned short y)`: This changes the Point's x and y values to the new specified values.
* `Point::size()`: When the Point is used as a layout, this identifies the size of the grid by multiplying the x-value by the y-value.

[Home](README.md)
