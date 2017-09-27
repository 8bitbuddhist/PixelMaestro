# Cue
The Cue class converts PixelMaestro commands into a serialized format that you can send to other devices via a serial interface. This allows you to control a Maestro remotely, split a Maestro across multiple devices, or create a headless Maestro that simply communicates instructions to actual rendering devices.

Cues are also used to store commands for later processing via a [Show](#show.md).

## Contents
1. [Creating Cues](#creating-cues)
	1. [Cue Components](#command-cues)
	2. [Payload Components](#payload-components)
2. [Running Cues](#running-cues)

## Creating Cues
At the core of each Cue is a _command_, which is a set of instructions stored as a byte array. Each component of PixelMaestro has its own _[Component]Cue_ class. These classes (called _handlers_) contain static method calls similar to the component's actual method calls. When you call a method, it encodes each of the method's parameters into the command. On the receiving side, the Cue class decodes each parameter and calls the appropriate method.

The following example demonstrates using two commands to create a Canvas and draw a circle:
```c++
#include "cue/cue.h"
#include "cue/canvascue.h"
#include "cue/sectioncue.h"

int section_index = 0;		// The index of the Section (in `Maestro::sections_`). This is required for almost all Cues.

// Storage for the Cue commands.
unsigned char canvas_buffer[50];
unsigned char circle_buffer[50];
SectionCue::add_canvas(canvas_buffer, section_index, CanvasType::ColorCanvas);
Cue::run(maestro, canvas_buffer);

CanvasCue::draw_circle(circle_buffer, section_index, Colors::GREEN, 5, 5, 2, true);
Cue::run(maestro, circle_buffer);
``

**Note:** The following info is for reference/curiosity only.

### Cue Components
Each Cue consists of four parts:

1. **Header**: a semi-unique string used to identify the start of a PixelMaestro Cue.
2. **Size**: the size of the command (or _payload_).
3. **Checksum**: a value calculated to confirm the integrity of the data received. This is done by summing up the entire command, dividing by 256, and taking the remainder.
4. **Payload**: the actual command to be executed.

The header and checksum are used primarily as validation when sending a Cue to another device.

### Payload Components
Payloads can vary in length depending on the command (hence the _size_ part of the Cue), but all payloads start with at least three of these parts:

1. **Component**: the PixelMaestro class that the Cue is acting on. This helps the Cue class delegate incoming Cues to different handlers.
2. **Action**: the component-specific action to perform.
3. **Type**: identifies one of several possible options in the command, e.g. a canvas type or font name.
4. **Section**: the Section affected by this Cue.

## Running Cues
To run a Cue, use the `Cue::run()` method, passing in the Maestro you want to run the Cue on and the Cue itself. The Cue class will unpack the command and send it off to the correct handler.

**Note:** Don't run the handler's run methods directly (`CanvasCue::run()`, `SectionCue::run()`, etc.), as this will bypass error checking and validation.

[Home](README.md)
