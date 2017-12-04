# Canvas
Canvases let you draw custom shapes and patterns onto a Section. Where Animations only show pre-defined patterns, Canvases let you draw specific shapes and patterns. Canvases can also display their own animations.

See the [CanvasDemo](../gui/demo/canvasdemo.cpp) in PixelMaestro Studio for an example.

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
6. [Interactive Canvases](#interactive-canvases)

## Canvas Types
There are two types of Canvases: `ColorCanvases` and `AnimationCanvases`. A `ColorCanvas` works like an image editor: you choose the shape you want to draw and the color to draw it in, and the Canvas draws the shape in that color.

An `AnimationCanvas` doesn't let you choose a color, but draws the shape using the Section's underlying Animation. For example, if the Section is running a `BlinkAnimation`, drawn Pixels appear to blink while the remaining Pixels appear off.

## Creating a Canvas
Create a new Canvas by calling `Section::set_canvas(CanvasType::Type, num_frames)`, where CanvasType is either `AnimationCanvas` or `ColorCanvas` and `num_frames` is the number of frames the Canvas contains (1 by default).

Note that nothing is drawn to the Canvas by default, so the Pixel grid will appear blank even if an Animation is running.

```c++
ColorCanvas* canvas = static_cast<ColorCanvas*>(section->set_canvas(CanvasType::ColorCanvas));
```

If you want to show an animated image, increase the number of frames to 2 or higher. Frames are described in more detail in the section [Animating a Canvas](#animating-a-canvas).

```c++
int num_frames = 10;
section-set_canvas(CanvasType::ColorCanvas, num_frames);
```

## Animating a Canvas
The area that you draw on a Canvas is called a `frame`. A frame is an independent drawing surface with the same dimensions as the Pixel grid. Canvases can have multiple frames and will cycle through each frame on a set interval. This essentially turns the Canvas into a video player.

You can specify the number of frames when calling `Section::set_canvas()`. Omitting this value defaults to a single frame. You can also change the number of frames in an existing Canvas using `Canvas::set_num_frames()`, but bear in mind this will delete the current frame set. You can set the amount of time (in milliseconds) between frames using `Canvas::set_frame_timing(milliseconds)`.

### Switching Frames
When using one of the `draw()` methods (detailed under [Drawing Shapes](#drawing-shapes)), drawing occurs on the current active frame, which you can find using `get_current_frame_index()`. Using `set_current_frame_index()` changes the active frame to the specified frame, causing any new actions to modify that frame instead. You can also switch between frames using `next_frame()`, which jumps to the next available frame (or the first frame if you're currently on the last frame).

## Drawing Shapes
The Canvas class provides several `draw()` methods for drawing various shapes and patterns. For each shape, specify its starting point on the grid (as x and y coordinates) and any extra parameters that the shape requires.

**Note:** When calling a draw method on a ColorCanvas, you will also need to pass the color that you want to draw the shape in. This is not required for an AnimationCanvas.

Canvases use a Cartesian coordinate system. The origin (0, 0) is at the top-left corner of the grid, with positive values moving to the right and down. For example, (5, 10) means 5 pixels to the right and 10 pixels down. If you tell the Canvas to draw outside of these dimensions, the Canvas will recognize it as 'out of bounds' and ignore the command.

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
The `draw_rect()` method draws a simple box with the specified origin, size, and whether to `fill` the box or just draw the outline.

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
Use `clear()` to return the current frame to a blank slate. You can clear a single Pixel using the `erase()` method. Note that once you clear a frame, there's no way to recover anything you've drawn.

## Interactive Canvases
You can create Canvases that respond to user input using the [CanvasDrawingArea](../gui/drawingarea/canvasdrawingarea.h) class. For an example, open the `Drawing Demo` in PixelMaestro Studio.

[Home](README.md)
