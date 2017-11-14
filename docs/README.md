## Contents
1. [Structure](#structure)
2. [Quick Start](#quick-start)

# Structure
PixelMaestro has three main components:
* [Maestro](maestro.md): Maestros handle synchronizing one or more Sections. They are the primary PixelMaestro components.
* [Section](section.md): Sections manage groups of Pixels. Any actions that affect the display or output (e.g. Animations and Canvases) are managed by a Section.
* [Pixel](pixel.md): Pixels store color values for output. Each Pixel can store a 24-bit color value. Pixels are managed by Sections.

PixelMaestro also includes the following support classes:
* [Animation](animation.md): Animations display various patterns on a Section.
* [Canvas](canvas.md): Canvases draw custom shapes and patterns onto a Section.
* [Colors](colors.md): Colors store 24-bit RGB values (8 bits to the red, green, and blue channels each). This class provides tools for generating custom colors and palettes.
	* ColorPresets: Contains several pre-defined common colors.
* [Cue](cue.md): Cues let you convert PixelMaestro commands into packets that can be saved to a file or sent to other devices.
* [Point](point.md): Points correspond to Pixel coordinates on a Section. They are also used in some cases to set the size of the Pixel grid.
* [Show](show.md): Shows schedule Cues to run at certain times in the program's lifecycle.
* [Utility](utility.md): Utilities are common methods shared across classes.
