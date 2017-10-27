# PixelMaestro GUI
This is a QT-based application that lets you preview PixelMaestro animations on a PC.

## Requirements
- QT 5
	- QSerialPort

## Contents
1. [Main Window](#main-window)
	1. [Navigating Workspaces](#navigating-workspaces)
	2. [Changing Preferences](#changing-preferences)
2. [Using the Animation Previewer](#animation-previewer)
	1. [Additional Animation Parameters](#additional-animation-parameters)
	2. [Custom Color Schemes](#custom-color-schemes)
	3. [Using Canvases](#using-canvases)
	4. [Saving and Loading Configurations](#saving-and-loading-configurations)

## Main Window
When you open the application for the first time, the main window is blank. Use the *File* menu to access different areas of the program, such as the *Animation Previewer* or various demos. Use the *Help* link to access the library documentation.

### Navigating Workspaces
A *Workspace* is a screen showing a running Maestro. Some Workspaces show pre-configured demos, while others let you manipulate the Maestro.

Open a Workspace by clicking *File*, then select either a Demo or the Animation Previewer. You can see details about the workspace in the status bar at the bottom of the window. If you want to close the current workspace, click *Close Workspace* in the menu, or simply select another Workspace.

### Changing Preferences
You can set preferences for the program by clicking *Edit* > *Preferences*.

The *Pixel size* and *Pixel shape* options change the appearance of Pixels drawn to the screen. You may need to close and reopen any open Workspaces before these settings will take effect.

The *Send serial commands* option lets you control a Maestro running on a device connected via USB. The device must be actively listening for PixelMaestro Cues. See the SerialCue Arduino sketch for an example.

## Using the Animation Previewer
The Animation Previewer lets you perform actions on a running Maestro in real-time. When you open the Animation Previewer, it draws a grid of Pixels with a set of controls underneath it. It also adds a single Section and Overlay. You can perform actions such as adjust the Section's size, configure Animations, and add a Canvas.

If *Send serial commands* is enabled, any actions performed in the Animation Previewer will get sent to the specified USB device.

### Additional Animation Parameters
TODO

### Custom Color Schemes
TODO

### Using Canvases
TODO

### Saving and Loading Configurations
You can save the current Maestro configuration to a file by clicking *File* > *Save Maestro*. Enter a filename with the `.pmc` (PixelMaestro Cue) extension and click Save. This creates a file with a set of Cues stored on each line. You can use this file to restore your configuration at a later time or on another device by using the `CueController::run()` methods.

**Note**: Saving and loading is a WIP feature. Not all settings will be saved, and loading is not currently available.
