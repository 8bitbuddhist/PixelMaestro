# Changelog
All notable changes to this project will be documented in this file.

The format is loosely based on [Keep a Changelog](http://keepachangelog.com/).

## [v0.6r2] - 2017-09-18
### Changed
- Animations:
	- Animations now track their speed and update times instead of Sections.
	- Animations now take speed and pause parameters in constructor.
- Animation Previewer:
	- Changed name of the animation editor to animation previewer.
	- Fixed speed slider.
- Canvas:
	- Canvases no longer modify Pixels directly. Instead, the Section checks the Canvas during get_pixel_color().
- Colors:
	- Renamed "Alpha Blending" mix mode to "Alpha"
	- Colors::MixMode takes alpha as unsigned char instead of float.
- Other
	- GUI opens maximized by default.

### Removed
- Canvas:
	- Removed background and foreground color options.
- Colors:
	- Removed "Normal" mixing mode.

### Known Issues
- Fatal exception when closing the Animation Previewer without quitting the program.

## [v0.6] - 2017-09-17 
### Added
- Animations:
	- New Animations interface.
	- Added Radial, Mandelbrot, Plasma, and Lightning animations.
	- Added customizable options to Sparkle, Plasma, and Lightning animations.
- Animation Editor:
	- Added support for Animation-specific controls.
	- Added preview to custom color controls.
	- Added a default Overlay.
	- Added Orientation support.
- Show:
	- Added RunFunctionEvent, which uses std::functional to trigger custom function calls at runtime.

### Changed
- Animations:
	- Moved animation logic from Sections into separate Animations classes.
- Animation Editor:
	- Replaced custom color dials with sliders.
	- Fixed broken Overlay behavior.
	- Fixed several bugs when switching Sections.
	- Set default ColorAnimation to SOLID.
	- Set default Overlay MixMode to NONE.
	- Improved SimpleDrawingArea dynamic scaling.
- Canvas:
	- Canvas contents now scroll independently of Animations.
	- Dynamic allocation of pattern arrays on Canvas initialization.
	- Dynamic resizing of Canvases when Section sizes change.
	- Canvas methods now take x and y coordinates as ints.
- General:
	- Optimized data types across core classes.
- Section:
	- Swapped set_one() parameters.
	- Added dynamic Pixel allocation on Section initialization.
	- Added dynamic Overlay allocation.
- Show:
	- Moved Shows under Maestros.

### Removed
- Animations:
	- Removed Pong, Next, and None animations.
- Animation Editor:
	- Temporarily removed ability to dynamically add and remove Sections and Overlays.
- Canvas:
	- Removed num_chars parameter from draw_text().

### Known Issues
- Fatal exception when closing the Animation Previewer without quitting the program.


## [v0.5] - 2017-09-02
### Added
- New Canvas class for drawing text and shapes over Sections (replaces Section::Pattern).
- New Point class for storing x and y coordinates. Replaces Section::Layout.
- Added Canvas demo to GUI application.
- Added Overlay support to GUI application.

### Changed
- Revamped GUI to allow switching between the main animation screen and various demo animations.
- Reorganized file and code structure.
- Layouts use the new Point class and are referred to as "dimensions".

### Removed
- Removed Section::Pattern. Replaced by the Canvas class.
- Removed Section::Layout. Replaced by the Point class.
- Removed Section::ColorAnimations::Pattern. Patterns are now stored in a Canvas.
- Removed several unused variables and functions.

## [v0.4.1] - 2017-08-16
### Added
- Added several Color, Section, and Utility unit tests.

### Changed
- Changed the name of "Transitions" to "Events".
- Changed Section::Overlay to pointers.

### Removed
- Removed unused Colors::HSVtoRGB function.

## [v0.4] - 2017-08-15
### Added
- Added working Arduino sketches for use in [PlatformIO](http://platformio.org/).
- Added random color generator to Colors.
- Added multiplication and division operators to Colors::RGB.

### Changed
- Restructured layout of source files (easier to manage in QT Creator).
- Rebuilt Show class (again) using custom Transitions instead of functional.h. See the `src/show` folder for current available Transitions.
- Removed stdlib dependency from Colors.h. The library is now completely self-contained.
- Changed Sections to store Patterns as pointers.
- Initialized pointer variables used in if statements (e.g. Show::maestro_) to nullptr.

## [v0.3.1] - 2017-08-09
### Added
- Added Show support to PixelMaestro_QT
- Added Show demo to PixelMaestro_QT

## [v0.3] - 2017-07-19
### Added
- Added QT-based GUI with controls for user input.
- Added initial support for extended animation options. At the moment, it only allows you to set the threshold of lit LEDS in the Sparkle animation.
- Added Colors::MixMode::NONE. This is currently used to disable an Overlay and/or flag it as uninitialized.
- Added NEXT ColorAnimation as a shortcut for incrementing the currently active animation.

### Removed
- Removed GTK-based GUI

### Known Issues
- GUI does not support Overlays or multiple Sections.

## [v0.2] - 2017-05-01
### Added
- Added Changelog file.
- Added documentation for all classes.
- Added simple GTK-based GUI (with demos) for testing animations.
- Added (some) unit tests using [Catch](https://github.com/philsquared/Catch).
- Added demo Arduino sketch with PlatformIO project config and instructions.

### Changed
- Rebuilt Show class.
- Fixed Doxygen formatting errors with some classes.
- *Many* code cleanup changes.

## [v0.1] - 2017-04-13
- Initial public release.
