# Canvas
Canvases let you draw custom shapes and patterns onto a Section. Where Animations show pre-defined patterns, Canvases let you draw freely using those patterns or using custom colors. Canvases can also display simple animations by scrolling the pattern or displaying multiple different patterns in rapid succession.

See the [CanvasDemo](../gui/demo/canvasdemo.cpp) in the PixelMaestro QT application for an example.

## Contents
1. [Canvas Types](#canvas-types)
2. [Creating a Canvas](#creating-a-canvas)
3. [Animating a Canvas](#animating-a-canvas)
	1. [Switching Frames](#switching-frames)
4. [Drawing Shapes](#drawing-shapes)
	1. [Drawing Lines](#drawing-lines)
	2. [Drawing Rectangles](#drawing-rectangles)
	3. [Drawing Text](#drawing-text)
	4. [Drawing Triangles](#drawing-triangles)
	5. [Clearing the Canvas](#clearing-the-canvas)
5. [Setting Background and Foreground Colors](#setting-background-and-foreground-colors)
6. [Scrolling](#scrolling)
	1. [Repeated Scrolling](#repeated-scrolling)
7. [Offsetting](#offsetting)
8. [Interactive Canvases](#interactive-canvases)

## Canvas Types
There are two different types of Canvases: `ColorCanvas` and `AnimationCanvas`. A `ColorCanvas` works similar to an image editor: you specify the shape to draw and the color to draw the shape in, and the Canvas draws the shape in the specified color.

**Tip:** Color Canvases are RAM-hungry. You might run into issues on memory-tight devices (e.g. Arduino Uno).

Instead of drawing a specific color, an `AnimationCanvas` draws the Section's underlying Animation. For example, if the Section is running a `BlinkAnimation`, anything drawn on the Canvas will blink. Pixels that are not drawn appear black.

## Creating a Canvas
Create a new Canvas by calling `Section::set_canvas(CanvasType::Type, num_frames)`, where CanvasType is either `AnimationCanvas` or `ColorCanvas` and `num_frames` sets the number of frames the Canvas contains (defaults to 1 if omitted). This initializes and returns a pointer to a new Canvas of the specified type.

Note that nothing is drawn to the Canvas by default, so the Section will appear to be blank.

```c++
ColorCanvas* canvas = static_cast<ColorCanvas*>(section->set_canvas(CanvasType::ColorCanvas));
```

If you want to display an animated Canvas, specify the number of frames. Frames are described in more detail in the section [Animating a Canvas](#animating-a-canvas).

```c++
int num_frames = 10;
section-set_canvas(CanvasType::ColorCanvas, num_frames);
```

## Animating a Canvas
The area that you draw on a Canvas is called a `frame`. A frame is a completely independent drawing surface with the same dimensions as the Pixel grid. Canvases can have multiple frames, and if multiple frames are set, the Canvas will cycle through each one on refresh. This lets you use custom drawn animations in addition to the [built-in Section animations](animation.md).

**Note:** The frame cycle rate is the same as the Maestro's refresh rate.

You can specify the number of frames in `Section::set_canvas()`. Omitting this value defaults to a single frame. You can also change the number of frames in an existing Canvas using `set_num_frames()`, but bear in mind this will delete the current frame set.

### Switching Frames
When using one of the `draw()` methods (detailed under [Drawing Shapes](#drawing-shapes)), drawing occurs on the current active frame, which you can find using `get_current_frame_index()`. Using `set_current_frame_index()` changes the active frame to the specified frame, causing the Canvas to render that frame instead. This also changes the target frame for any `draw()` actions. You can also quickly jump between frames using `next_frame()`, which jumps to the next available frame (or the first frame if you're currently on the last frame).

## Drawing Shapes
The Canvas class provides several `draw()` methods for drawing various shapes, elements, and patterns. For each shape you must specify where it will appear on the grid (as x and y coordinates) and any extra parameters that the shape requires.

**Note:** When calling a draw method on a ColorCanvas, you will also need to pass the Color you want to use to draw the shape.

The Canvas uses a Cartesian coordinate system. The origin (0, 0) is at the top-left corner of the Section, with increasing values moving to the right and down.

For an example of drawing various shapes, see the [CanvasDemo](../gui/demo/canvasdemo.cpp).

### Drawing Lines
The `draw_line` method lets you draw a line from one point to another. Enter the coordinate where the line starts and the coordinate where the line ends.

```c++
// Draw a 10 Pixel long diagonal line
canvas->draw_line(0, 0, 10, 10);
```

### Drawing Points
The `draw_point()` method lets you draw a single pixel at a time. You can erase a pixel using the `erase()` method.

```c++
// Draw a single point 5 pixels under the origin, then erase it.
canvas->draw_point(0, 5);
canvas->erase(0, 5);
```

### Drawing Rectangles
The `draw_rect()` method draws a box with the specified origin, size, and whether to `fill` the box or just draw the outline.

```c++
// Draw the outline of a 10 x 10 rectangle 
bool fill = false;
canvas->draw_rect(0, 0, 10, 10, fill);
```

### Drawing Text
The `draw_text()` method lets you draw text. Specify the origin, a `Font`, and the `text` to display.

```c++
// Draws "PixelMaestro" at the Canvas' origin
Font *font = new Font5x8();
canvas->draw_text(0, 0, font, "PixelMaestro");
```

PixelMaestro uses bitmap fonts. All fonts inherit from the [Font class](../src/canvas/fonts/font.h). For an example, see the included [5x8 font](../src/canvas/fonts/font5x8.h).

### Drawing Triangles
The `draw_triangle()` method draws a triangle with the three specified coordinates. You can also `fill` the triangle or only draw an outline.

```c++
// Draws a filled in right-angle triangle 10 pixels high and 10 pixels wide
canvas->draw_triangle(0, 0, 10, 0, 0, 10, true);
```

### Clearing the Canvas
The `clear()` method returns the Canvas to a blank slate by setting all Pixels back to their default state. You can clear a single pixel using the `erase()` method. Note that once you clear a Canvas, there's no way to recover anything you've drawn.

## Scrolling
Scrolling shifts the contents of a Canvas along the Section. Scroll time is measured in terms of refresh cycles, e.g. a value of `2` means the Section will refresh twice before the Canvas scrolls 1 pixel. Use `set_scroll()` to define the scroll rate along the x and y axes. When this value is positive, the Canvas scrolls left on the x-axis and up on the y-axis, otherwise it scrolls right on x and down on y.

Call `update_scroll()` to trigger a scroll. A scroll is also triggered automatically on `update()`. Setting either axis to 0 disables scrolling on that axis. You can also stop scrolling by calling `remove_scroll()`, which completely removes all scrolling behavior.

The following code scrolls 1 Pixel to the left on every refresh cycle and 1 Pixel down every other refresh cycle. `false` disables repeat scrolling, which is described in the next section.

```c++
canvas->set_scroll(1, -2, false);
```

### Repeated Scrolling
By default, the Canvas will scroll out of frame before jumping back to its starting point when it reaches the end of the scroll, i.e, when the scroll amount equals the Canvas width. Setting the `repeat` property to `true` wraps the Canvas around from one end of the grid to the opposite end, making it appear to scroll infinitely.

```c++
canvas->set_scroll(1, -2, true);
```

## Offsetting
Offsetting shifts the Canvas' starting point to another place on the Pixel grid. By default the offset is set to 0, meaning the starting point is the same as the Pixel grid's starting point. These values can be negative.

The following code shifts the Canvas 5 Pixels to the right and 1 Pixel down.
```c++
canvas->set_offset(5, 1);
```

**Note:** Offset will be disabled if scrolling is enabled, since scrolling modifies the offset values.

## Interactive Canvases
You can create Canvases that respond to user input using the [CanvasDrawingArea](../gui/drawingarea/canvasdrawingarea.h) class. For an example, open `Drawing Demo` in PixelMaestro Studio.

[Home](README.md)
