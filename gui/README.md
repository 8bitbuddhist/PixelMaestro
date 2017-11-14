# PixelMaestro Studio
PixelMaestro Studio is a Qt-based desktop application that lets you run PixelMaestro on a PC. PixelMaestro Studio lets you run demos, mix custom animations, save and load configurations, and control other devices running PixelMaestro over USB.

## Build Requirements
- QT 5 with the QtSerialPort module

## Contents
1. [Main Window](#main-window)
	1. [Navigating Workspaces](#navigating-workspaces)
	2. [Changing Settings](#changing-settings)
2. [Using the Animation Previewer](#animation-previewer)
	1. [Additional Animation Parameters](#additional-animation-parameters)
	2. [Custom Color Schemes](#custom-color-schemes)
	3. [Using Canvases](#using-canvases)
	4. [Saving and Loading Configurations](#saving-and-loading-configurations)

## Main Window
When first started, the application shows a blank window. Use the *File* menu to access different areas of the program such as the *Animation Editor* or various demos. Use the *Edit* menu to access the program's Settings. Use the *Help* menu to access documentation.

### Navigating Workspaces
Opening a link in the *File* menu creates a new *Workspace*. A Workspace is any screen that shows a running Maestro, such as a demo. After opening a Workspace, you can see details about the Workspace in the status bar at the bottom of the window. To close the current workspace, click *Close Workspace* in the File menu, or select another Workspace.

### Changing Settings
You can change the program's settings by clicking *Edit* > *Settings*.

#### Rendering Options
*Rendering Options* control how the Maestro is rendered to the screen. The *Pixel Size* and *Pixel Shape* options define the appearance of each Pixel on the screen. The *Refresh Rate* defines how quickly the Maestro updates. This may impact how smooth certain animations appear.

**Tip:** For best performance, set the Pixel Size to *Full* and the Pixel Shape to *Square*.

#### Animation Editor Options
*Animation Editor Options* control options specific to the Animation Editor. The *Number of Sections* option sets the number of Sections assigned to the Maestro when opening the Animation Editor.

The *Send serial commands* option lets you control a Maestro running on a device connected via USB. You can select any device connected via USB. Note that the device must be actively listening for PixelMaestro Cues. For an example, see the [CueServer Arduino sketch](../arduino/CueServer/CueServer.cpp). Alternatively, select *Simulated Device* to open a "virtual Maestro" in a new window. This Maestro receives and executes Cues just like a regular device and is designed for debugging and previewing actions.

You may need to reopen any open Workspaces before setting changes will take effect.

## Using the Animation Editor
The Animation Editor is an interactive tool for modifying a Maestro in real-time. When you open the Animation Editor, it displays each of the Maestro's sections and a set of controls for modifying each Section. You can perform actions such as adjusting the Section's size, configuring Animations, and adding Canvases.

To modify a Section, you must first set it as the *Active Section*. Despite its name, the Active Section is determined by both the *Section* and *Overlay* drop-down boxes. That is, if Section 1 and Overlay 3 are selected, then the active Section is Section 1's third Overlay. If the Overlay box is set to "Not Selected", then the base Section is modified.

If *Send serial commands* is configured in the Settings dialog, any actions performed in the Animation Editor will get sent to the specified serial device. PixelMaestro Studio automatically detects and lists USB devices connected to your PC. You can also run a simulated USB device for testing Cues by selecting *Simulated Device* in the drop-down.

### Additional Animation Parameters
TODO

### Custom Color Schemes
TODO

### Using Canvases
TODO

### Saving and Loading Configurations
You can save the current Maestro configuration to a file by clicking *File* > *Save Maestro...*. Likewise, you can open a Maestro configuration using *File* > *Open Maestro...*. This file works on any device running PixelMaestro. For more information, see the [Cue documentation](../docs/cue.md).
