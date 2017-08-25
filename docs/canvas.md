# Canvas
A Canvas is a special class for drawing custom shapes and patterns on a Section. Canvases are rendered independently from animations, making it possible to show both at the same time.

At its core, a Canvas is a grid of pixels. Instead of containing a color value, these pixels contain a boolean value set to false. When you draw something on a canvas, the pixels that have been drawn over are set to true. When the Section renders the Canvas, it draws all of the pixels that have been set to true and ignores the pixels that were set to false.

Tip: See the [CanvasDemo class](../gui/demo/canvasdemo.cpp) in the PixelMaestro QT application for an example.

## Contents
1. [Creating a Canvas](#creating-a-canvas)
2. [Setting Background and Foreground Colors](#setting-background-and-foreground-colors)
3. [Drawing Shapes](#drawing-shapes)
	1. [Drawing Text](#drawing-text)
	2. [Drawing Rectangles](#drawing-rectangles)
4. [Scrolling](#scrolling)
	1. [Repeated Scrolling](#repeated-scrolling)
5. [Offsetting](#offsetting)

## Creating a Canvas
The following code creates a 10 x 10 Canvas grid and assigns it to a Section. Note that this doesn't display anything by default. The size of the Canvas *should* be the same as the size of the Section, but it doesn't have to be.

```c++
Point *size = new Point(10, 10);
bool *canvas_pixels = new bool[size->x * size->y] {0};

Canvas canvas = new Canvas(&canvas_pixels[0], size);
...
section->setCanvas(canvas);
```

## Setting Background and Foreground Colors
By default, any patterns displayed on the Canvas will display the color of the parent Section's color animation, and any pixels not displayed by the Canvas will be set to black. The `bg_color` and `fc_color` properties let you override the color animation by setting a custom background and foreground color on the Canvas, respectively.

## Drawing Shapes
The Canvas class provides specific functions for drawing various shapes, elements, and patterns. For each shape you must specify an origin on the grid, as well as any extra parameters that the shape requires.

Note that you can draw multiple shapes on a single Canvas. Depending on the shape and Canvas configuration, any empty space is treated as transparency.

### Drawing Text
The `drawChar` and `drawText` methods let you draw individual characters and strings of text, respectively. For each method you must specify the origin `coordinates`, a `Font`, and the `text` or `character` to display. In the case of `drawText`, you must also specify the number of characters in the string.

### Drawing Rectangles
The `drawRect` method draws a box with the specified `origin` coordinates, the `size` of the box, and whether to `fill` the box or simply draw the border and leave the inside transparent.

## Scrolling
You can scroll a Canvas horizontally, vertically, or both by setting `Canvas::scroll_interval`. `scroll_interval` defines both the direction and amount of time before the Canvas is scrolled. Time is measured in terms of refresh cycles, e.g. a scroll interval of `2` means the Section will refresh twice before the Canvas is scrolled 1 pixel. The same goes for `-2` as well.

 `scrollRate->x` scrolls along the horizontal axis and `scrollRate->y` scrolls along the vertical axis. These values can be negative, which scrolls left instead of right for `scrollRate->x` and up instead of down for `scrollRate->y`.

The following code scrolls 1 Pixel to the right on each refresh cycle, and 1 Pixel up every other refresh cycle.
```c++
canvas->scroll_interval = new Point(1, -2);
```

### Repeated Scrolling
By default, the Canvas will "jump" back to its starting point when it reaches the end of the scroll. Setting the `repeat` property to `true` wraps the Canvas around from one end of the grid to the opposite end, making it appear to scroll infinitely.

## Offsetting
Offsetting shifts the Canvas' starting point to another place on the Pixel grid. By default the offset is set to 0, meaning the starting point is the same as the Pixel grid's starting point. These values can be negative.

The following code shifts the Canvas 5 Pixels to the right and 1 Pixel down.
```c++
canvas->offset->x = 5;
canvas->offset->y = 1;
section->setCanvas(canvas);
```

By default, if the Pattern extends beyond the Pixel grid, the rest of the Pattern will not be drawn. However, setting `Pattern::repeat` to true draws the hidden part by wrapping it to the opposite end of the Canvas.

[Home](README.md)
