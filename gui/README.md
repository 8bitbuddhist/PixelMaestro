# PixelMaestro Studio
PixelMaestro Studio is a Qt-based application that lets you use the core PixelMaestro library on a PC. PixelMaestro Studio lets you preview commands, mix custom Animations, save configurations, and send commands to devices via serial connection.

## Build Requirements
- QT 5
	- QSerialPort

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
Running the application opens a blank window. Use the *File* menu to access different areas of the program, such as the *Animation Editor* or various demos. Use the *Edit* menu to access the program's *Settings*. Use the *Help* menu to access documentation.

### Navigating Workspaces
Opening a link in the *File* menu creates a new *Workspace*. When you first open the app, no Workspaces are running. After opening a Workspace, you can see details about the Workspace in the status bar at the bottom of the window. To close the current workspace, click *Close Workspace* in the menu, or just select another Workspace.

### Changing Settings
You can change the program's settings by clicking *Edit* > *Settings*.

*Rendering Options* control how the Maestro is rendered to the screen.

*Animation Editor Options* control options specific to the Animation Editor. The *Send serial commands* option lets you control a Maestro running on a device connected via USB. The device must be actively listening for PixelMaestro Cues. For an example, see the [CueServer Arduino sketch](../arduino/CueServer/CueServer.cpp).

You may need to reopen any open Workspaces before setting changes will take effect.

## Using the Animation Editor
The Animation Editor lets you modify a Maestro in real-time. When you open the Animation Editor, it creates a new Maestro with a single Section and Overlay. You can perform actions such as adjusting the Section's size, configuring Animations, and adding Canvases.

If *Send serial commands* is configured in the Settings dialog, any actions performed in the Animation Editor will get sent to the specified serial device.

### Additional Animation Parameters
TODO

### Custom Color Schemes
TODO

### Using Canvases
TODO

### Saving and Loading Configurations
You can save the current Maestro configuration to a file by clicking *File* > *Save Maestro...*. Likewise, you can open a Maestro configuration using *File* > *Open Maestro...*. This file works on any device running PixelMaestro. For more information, see the [Cue documentation](../docs/cue.md).
