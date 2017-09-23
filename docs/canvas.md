# Canvas
A Canvas lets you draw custom shapes and patterns onto a Section. In essence, a Canvas is a way of quickly toggling certain Pixels on or off. Pixels that are on will show the Section's underlying Animation, while Pixels that are off won't show anything.

See the [CanvasDemo](../gui/demo/canvasdemo.cpp) in the PixelMaestro QT application for an example.

## Contents
1. [Canvas Types](#canvas-types)
2. [Creating a Canvas](#creating-a-canvas)
3. [Drawing Shapes](#drawing-shapes)
	1. [Drawing Lines](#drawing-lines)
	2. [Drawing Rectangles](#drawing-rectangles)
	3. [Drawing Text](#drawing-text)
	4. [Drawing Triangles](#drawing-triangles)
	5. [Clearing the Canvas](#clearing-the-canvas)
4. [Setting Background and Foreground Colors](#setting-background-and-foreground-colors)
5. [Scrolling](#scrolling)
	1. [Repeated Scrolling](#repeated-scrolling)
6. [Offsetting](#offsetting)
7. [Interactive Canvases](#interactive-canvases)

## Canvas Types
There are two different types of Canvases: `ColorCanvas` and `AnimationCanvas`. A `ColorCanvas` works similar to an image editor: you specify the shape to draw and the color to use when drawing the shape. You can pass any color, and the Canvas will store it internally. This type of Canvas is limited on embedded devices, since it stores an additional RGB value for each pixel.

An `AnimationCanvas` works almost identical to a `ColorCanvas`, except instead of drawing a specific color it draws the Section's underlying Animation. For example, if the Section is running a `BlinkAnimation`, any shapes drawn on the Canvas will appear to blink using the colors in the Animation. This is done by assigning a boolean value to each pixel: if the boolean is `true`, then the pixel is drawn (i.e. it shows the color from the Animation). If it's `false`, then the pixel is not drawn and it appears black.

## Creating a Canvas
Create a new Canvas by calling `Section::add_canvas(CanvasType::Type)`, where CanvasType is one of the values in the `CanvasType::Type` enum. This automatically creates and initializes a new Canvas of the specified type. The Section will return a pointer to the Canvas of the base Canvas class, which you can then cast to the actual Canvas type.

Note that nothing is drawn to the Canvas by default, so the Section will appear to be blank.

```c++
ColorCanvas* canvas = static_cast<ColorCanvas*>(section->add_canvas(CanvasType::COLORCANVAS);
```

## Drawing Shapes
The Canvas class provides several functions for drawing various shapes, elements, and patterns. For each shape you must specify where it will appear on the grid (typically as x and y coordinates), its size, and any extra parameters that the shape requires.

**Note:** When calling one of the `draw_` methods on a ColorCanvas, you will also need to pass the Color you want to use to draw the shape.

The Canvas uses a Cartesian coordinate system. The origin (0, 0) is at the top-left corner of the Section.

For an example of drawing various shapes, see the [CanvasDemo](../gui/demo/canvasdemo.cpp).

### Drawing Lines
The `draw_line` method lets you draw a line from one point to another. Enter the point where the line starts and the point where the line ends.

```c++
// Draw a 10 Pixel long diagonal line
canvas_->draw_line(0, 0, 10, 10);
```

### Drawing Points
The `draw_point()` method lets you draw a single pixel at a time. You can deactivate a pixel using the `erase()` method.

```c++
// Draw a single point 5 pixels to the right of the origin
canvas_->draw_point(0, 5);
```

### Drawing Rectangles
The `draw_rect()` method draws a box with the specified origin, a size, and whether to `fill` the box or simply draw the border and leave the inside transparent.

```c++
// Draw the outline of a 10 x 10 rectangle 
bool fill = false;
canvas_->draw_rect(0, 0, 10, 10, fill);
```

### Drawing Text
The `draw_text()` method lets you draw text to a Canvas. Specify the origin, a `Font`, and the `text` to display.

```c++
// Draws "PixelMaestro" at the Canvas' origin
Font *font = new Font5x8();
canvas_->draw_text(0, 0, font, "PixelMaestro");
```

PixelMaestro supports bitmap fonts. All fonts inherit from the [Font](../src/canvas/fonts/font.h). For an example, see the included [5x8 font](../src/canvas/fonts/font5x8.h).

### Drawing Triangles
The `draw_triangle()` method draws a triangle using the three specified coordinates. You can also `fill` the triangle or leave the center transparent.

```c++
// Draws a filled in right-angle triangle 10 pixels high and 10 pixels wide
canvas_->draw_triangle(0, 0, 10, 0, 0, 10, true);
```

### Clearing the Canvas
The `clear()` method returns the Canvas to a blank slate by clearing out any drawn shapes. You can clear a single pixel using the `erase()` method. Note that there's no way to recover anything you've drawn after clearing them.

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
