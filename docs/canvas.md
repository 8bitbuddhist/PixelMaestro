# Canvas
Canvases let you draw custom shapes and patterns on a Section. At its core, a Canvas is simply a tool for toggling certain Pixels on or off. When you set a Canvas to a Section, the Section displays its color animation over the Pixels that have been drawn over (i.e. enabled), and ignores the Pixels that have not been drawn over (i.e. disabled).

See the [CanvasDemo class](../gui/demo/canvasdemo.cpp) in the PixelMaestro QT application for an example.

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
The following code creates a 10 x 10 Canvas grid and assigns it to a Section. Note that this doesn't display anything by default. Ideally the size of the Canvas should match the size of its parent Section, but it doesn't have to.

```c++
Point *size = new Point(10, 10);
bool *canvas_pixels = new bool[size->x * size->y] {0};

Canvas* canvas = new Canvas(&canvas_pixels[0], size);
...
section->set_canvas(canvas);
```

## Setting Background and Foreground Colors
By default, anything drawn on the Canvas will show the parent Section's color animation, and any pixels not drawn will be set to black. The `bg_color` and `fg_color` properties let you override this by setting a custom background and foreground color, respectively. Note that these colors apply to the entire Canvas.

## Drawing Shapes
There are specific functions for drawing various shapes, elements, and patterns. For each shape you must specify where it will appear on the grid, its size, and any extra parameters that the shape requires.

For an example of drawing various shapes, see the [CanvasDemo](../gui/demo/canvasdemo.cpp) class in the GUI application.

### Drawing Lines
The `draw_line` method lets you draw a line from one point to another. Enter the point where the line starts and the point where the line ends.

```c++
// Draw a 10 Pixel-long horizontal line
Point* cursor = new Point(0, 0);
Point* target = new Point(0, 10);
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
The `draw_char()` and `draw_text()` methods let you draw individual characters and strings of text, respectively. For each method you must specify the origin `coordinates`, a `Font`, and the `text` or `character` to display. In the case of `draw_text()`, you must also specify the number of characters in the string.

```c++
// Draws the text "PixelMaestro" at the Canvas' origin
Point* cursor = new Point(0, 0);
Font *font = new Font5x8();
canvas_->draw_text(cursor, font, "PixelMaestro", 12);
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
The `clear()` method returns the Canvas to a blank slate by clearing out any drawn pixels. You can clear a single pixel using the `erase()` method.

## Scrolling
You can scroll a Canvas horizontally, vertically, or both by setting `Canvas::scroll_interval`. `scroll_interval` defines both the direction and amount of time before the Canvas is scrolled. Time is measured in terms of refresh cycles, e.g. a scroll interval of `2` means the Section will refresh twice before the Canvas is scrolled 1 pixel.

 `scroll_interval->x` scrolls along the horizontal axis and `scroll_interval->y` scrolls along the vertical axis. These values can be negative, which scrolls left instead of right for `scroll_interval->x` and up instead of down for `scroll_interval->y`.

Call `Canvas::scroll()` to trigger a scroll. A scroll is also triggered automatically on `Canvas::update()`. Setting `scroll_interval` to 0 on either axis disables scrolling on that axis.

The following code scrolls 1 Pixel to the right on each refresh cycle, and 1 Pixel up every other refresh cycle.
```c++
canvas->scroll_interval = new Point(1, -2);
```

### Repeated Scrolling
By default, the Canvas will "jump" back to its starting point when it reaches the end of the scroll, i.e, when the scroll amount becomes equivalent to the width of the Canvas. Setting the `repeat` property to `true` wraps the Canvas around from one end of the grid to the opposite end, making it appear to scroll infinitely.

## Offsetting
Offsetting shifts the Canvas' starting point to another place on the Pixel grid. By default the offset is set to 0, meaning the starting point is the same as the Pixel grid's starting point. These values can be negative.

The following code shifts the Canvas 5 Pixels to the right and 1 Pixel down.
```c++
canvas->offset = new Point(5, 1);
```

By default, if the Pattern extends beyond the Pixel grid, the rest of the Pattern will not be drawn, and the empty space is filled by the Section's ColorAnimation. However, setting `Pattern::repeat` to true wraps the Canvas to the opposite end of the grid, filling in this empty space.

## Interactive Canvases
For a demo on how to create an interactive Canvas, see the [CanvasDrawingArea](../gui/drawingarea/canvasdrawingarea.h) class in the PixelMaestro GUI.

[Home](README.md)
