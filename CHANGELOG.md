# Changelog
All notable changes to this project will be documented in this file.

The format is loosely based on [Keep a Changelog](http://keepachangelog.com/).

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
