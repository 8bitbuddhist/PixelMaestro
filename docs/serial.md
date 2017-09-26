# Serial
The Serial library lets you generate PixelMaestro commands to send to other devices via a serial interface. This allows you to control a Maestro remotely, split a Maestro across multiple devices, or create a "headless" Maestro that simply communicates instructions to actual rendering devices.

## Contents
1. [Creating Commands](#creating-commands)
	1. [Command Components](#command-components)
2. [Running Commands](#running-commands)

## Creating Commands
A _command_ is a set of instructions stored as a byte array. Each component of PixelMaestro has its own _ComponentSerial_ class. These classes (or handlers) contain static method calls similar to the component's actual method calls. When you call a method, it encodes each of the parameters into the provided byte array, allowing you to immediately send out the command via the serial interface.

The following example demonstrates using two commands to create a Canvas and draw a circle in the center:
```c++
#include "serial/serial.h"
#include "serial/canvasserial.h"
#include "serial/sectionserial.h"

unsigned char buffer[100] = {0};
SectionSerial::add_canvas(buffer, 0, CanvasType::ColorCanvas);
Serial::run(maestro, buffer);

CanvasSerial::draw_circle(buffer, 0, Colors::GREEN, 5, 5, 2, true);
Serial::run(maestro, buffer);
``

### Command Components
**Note:** This isn't necessary for running commands, it's just for informational purposes.

Each command has four parts:
1. **Header**: a unique identifier used to confirm that this command is specifically a PixelMaestro command. All commands begin with "PM".
2. **Size**: the size of the payload.
3. **Checksum**: a value calculated to confirm the integrity of the data received. This is done by summing up the entire command, dividing by 256, and taking the remainder.
4. **Payload**: the actual command to be executed.

The `Serial` class handles bundling the payload into packets that can be sent to other devices. It also unbundles and verifies the payload on the receiving side.

## Running Commands
To run a command, use the `Serial::run()` method, passing in the Maestro you want to run the command on and the command itself. The Serial class will unpack the command and send it off to the correct handler.

**Note:** Don't run the handler's run methods directly (e.g. `CanvasSerial::run()`, `SectionSerial::run()`, etc), as this will bypass error checking and validation.

[Home](README.md)
