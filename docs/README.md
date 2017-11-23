## Contents
1. [Overview](#overview)
2. [Support Classes](#support-classes)

# Overview
PixelMaestro has two main components: Maestros and Sections. Each of these components has other sub-components that interact with or are managed by them. Each of these components is listed below.

1. [Maestros](maestro.md): Maestros manage one or more Sections. They are the top-level component.
	* [Cues](cue.md): Cues let you convert PixelMaestro commands into packets that can be saved to a file or sent to another Maestro.
	* [Shows](show.md): Shows let you schedule Cues to run at a later time in the Maestro's lifecycle.
2. [Sections](section.md): Sections manage groups of Pixels. Sections are the most important component since they manage components that modify the Pixel grid. Any actions that affect output (e.g. running an Animation or drawing on a Canvas) are done through a Section.
	* [Animations](animation.md): Animations display various patterns on a Pixel grid. These patterns can be customized using various options such as the type, speed, and orientation.
	* [Canvases](canvas.md): Canvases let you draw custom shapes and patterns onto a Pixel grid.

## Support Classes
The following components aren't used directly, but are still a vital part of the core library:

* [Colors](colors.md): Colors store 24-bit RGB values (8 bits for red, green, and blue each). This class provides tools for generating custom colors and color palettes. Colors are used primarily in Animations and Canvases.
	* ColorPresets: ColorPresets provides several pre-defined common colors.
* [Pixels](pixel.md): Pixels store color values which are then sent to an output device. Pixels are controlled by Sections.
* [Points](point.md): Points identify specific locations on the Pixel grid. They're also used to define the size of the grid.
* Timing: Timings track the update frequency for many PixelMaestro events such as component updates, Pixel redraws, and Canvas scrolls.
* [Utilities](utility.md): Utilities are common methods shared across classes.
