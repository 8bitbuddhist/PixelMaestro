# Canvas
A Canvas lets you draw custom shapes and patterns onto a Section. At its core, a Canvas simply toggles certain Pixels on or off. When you create a Canvas, the Section displays an Animation over the Pixels that have been drawn over (i.e. enabled), and ignores the Pixels that have not been drawn over (i.e. disabled).

See the [CanvasDemo](../gui/demo/canvasdemo.cpp) in the PixelMaestro QT application for an example.

## Contents
1. [Creating a Canvas](#creating-a-canvas)
2. [Setting Background and Foreground Colors](#setting-background-and-foreground-colors)
3. [Drawing Shapes](#drawing-shapes)
	1. [Drawing Lines](#drawing-lines)
	2. [Drawing Rectangles](#drawing-rectangles)
	3. [Drawing Text](#drawing-text)
	4. [Drawing Triangles](#drawing-triangles)
	5. [Clearing the Canvas](#clearing-the-canvas)
4. [Scrolling](#scrolling)
	1. [Repeated Scrolling](#repeated-scrolling)
5. [Offsetting](#offsetting)
6. [Interactive Canvases](#interactive-canvases)

## Creating a Canvas
You can create a Canvas by calling `Section::add_canvas()`. This initializes a new Canvas and assigns it to the Canvas. Note that this doesn't display anything by default, so the Section will appear to be blank.

```c++
Canvas* canvas = section->add_canvas();
```

You can also add an existing Canvas by using the `Section::set_canvas(Canvas*)` method.

## Setting Background and Foreground Colors
By default, anything drawn on the Canvas will cause the Section's running Animation to show through, and any pixels not drawn will be set to black. The `set_bg_color()` and `set_fg_color()` properties let you override this by setting custom background and foreground colors, respectively. Note that these colors apply to the entire Canvas. You can subsequently unset these colors using `remove_bg_color()` and `remove_fg_color()`.

## Drawing Shapes
The Canvas class provides several functions for drawing various shapes, elements, and patterns. For each shape you must specify where it will appear on the grid, its size, and any extra parameters that the shape requires.

For an example of drawing various shapes, see the [CanvasDemo](../gui/demo/canvasdemo.cpp) class in the GUI application.

### Drawing Lines
The `draw_line` method lets you draw a line from one point to another. Enter the point where the line starts and the point where the line ends.

```c++
// Draw a 10 Pixel long diagonal line
Point* cursor = new Point(0, 0);
Point* target = new Point(10, 10);
canvas_->draw_line(cursor, target);
```

### Drawing Points
The `draw_point()` method lets you activate a single pixel at a time. You can deactivate a pixel using the `erase()` method.

```c++
// Draw a single point 5 pixels over
Point* cursor = new Point(0, 5);
canvas_->draw_point(cursor);
```

### Drawing Rectangles
The `draw_rect()` method draws a box with the specified `origin` coordinates, the `size` of the box, and whether to `fill` the box or simply draw the border and leave the inside transparent.

```c++
// Draw the outline of a 10 x 10 rectangle 
Point* cursor = new Point(0, 0);
Point* size = new Point(10, 10);
bool fill = false;
canvas_->draw_rect(cursor, size, fill);
```

### Drawing Text
The `draw_text()` method lets you draw text to a Canvas. Specify the `origin`, a `Font`, and the `text` to display.

```c++
// Draws "PixelMaestro" at the Canvas' origin
Point* cursor = new Point(0, 0);
Font *font = new Font5x8();
canvas_->draw_text(cursor, font, "PixelMaestro");
```

PixelMaestro uses bitmap fonts when rendering text. All fonts inherit from the [Font](../src/canvas/fonts/font.h) class and require you to specify their size and character map. For an example, see the included [5x8 font](../src/canvas/fonts/font5x8.h).

### Drawing Triangles
The `draw_triangle()` method draws a triangle using the three specified coordinates. You can also `fill` the triangle or leave the center transparent.

```c++
// Draws a filled in right-angle triangle
Point* a = new Point(0, 0);
Point* b = new Point(10, 0);
Point* c = new Point(0, 10);
canvas_->draw_triangle(a, b, c, true);
```

### Clearing the Canvas
The `clear()` method returns the Canvas to a blank slate by clearing out any drawn shapes. You can clear a single pixel using the `erase()` method.

## Scrolling
Scrolling shifts the contents of a Canvas along the Pixel grid, similar to a marquee. You can scroll a Canvas horizontally, vertically, or both. Use the `set_scroll()` method to define both the direction and rate of scrolling. Scroll time is measured in terms of refresh cycles, e.g. a scroll interval of `2` means the Section will refresh twice before the Canvas is scrolled 1 pixel. This value can be negative, which scrolls left instead of right for the x-axis and up instead of down for y-axis.

Call `update_scroll()` to trigger a scroll. A scroll is also triggered automatically on `update()`. Setting either axis to 0 disables scrolling on that axis. You can disable scrolling entirely by calling `remove_scroll()`.

The following code scrolls 1 Pixel to the right on each refresh cycle, and 1 Pixel up every other refresh cycle.

```c++
canvas->set_scroll(1, -2);
```

### Repeated Scrolling
By default, the Canvas will "jump" back to its starting point when it reaches the end of the scroll, i.e, when the scroll amount becomes equivalent to the width of the Canvas. Setting the `repeat` property to `true` wraps the Canvas around from one end of the grid to the opposite end, making it appear to scroll infinitely.

```c++
canvas->set_scroll(1, -2, true);
```

## Offsetting
Offsetting shifts the Canvas' starting point to another place on the Pixel grid. By default the offset is set to 0, meaning the starting point is the same as the Pixel grid's starting point. These values can be negative.

The following code shifts the Canvas 5 Pixels to the right and 1 Pixel down.
```c++
canvas->set_offset(5, 1);
```

Note that if scrolling is enabled, the offset will be disabled.

## Interactive Canvases
For a demo on how to create an interactive Canvas, see the [CanvasDrawingArea](../gui/drawingarea/canvasdrawingarea.h) class in the PixelMaestro GUI.

[Home](README.md)
