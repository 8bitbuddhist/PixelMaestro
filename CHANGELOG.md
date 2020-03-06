# Changelog
All notable changes to PixelMaestro will be documented in this file.

The format is loosely based on [Keep a Changelog](http://keepachangelog.com/).

## [v2.1.1] - 2020-03-05

### Added
- Added `wrap` parameter to Sections. This lets you toggle whether to wrap Pixels in an offset Section from one side to another.

### Changed
- Fixed bug where a short Animation cycle could cause a division by 0.

## [v2.1.0] - 2019-11-26

### Changed
- Fixed `Canvas::draw_text()` bug.
- Fixed Pixel fading not working properly on 32-bit devices (PR #10).

### Removed
- Removed extra `map()` call from CycleAnimation.

## [v2.0.2-docs] - 2019-07-26

### Changed
- Migrated docs to Sphinx.

## [v2.0.2] - 2019-07-09

### Added
- Added ability to change where Animations are centered using `Animation::set_center()`.

### Changed
- Disabled Canvas Fonts by default. This means `Canvas::draw_text()` will not work unless you add the `CANVAS_ENABLE_FONTS` preprocessor directive to your sketch.
- Fixed interval calculation bug when scrolling a Section along the Y axis.
- Fixed bug when calculating Section brightness.
- Fixed bug when calculating the size of a Cue.
- Minor Pixel rendering optimiations.

## [v2.0.1] - 2019-06-30

### Added
- Readded EEPROM Arduino examples.

### Changed
- Fixed bugs where Animations didn't support maps larger than 255 x 255.
- Revised CueController logic to avoid executing Cues too early.

### Removed
- Removed LightWS2812 Arduino examples.


## [v2.0.0] - 2019-06-19

### Important Changes

#### Cue Changes

Due to changes in how Cues are formatted, Cues created in version 1.x are incompatible with this version.

#### Pixel Changes

Pixels now use a faster - but slightly less accurate - method of fading colors. You can enable accurate fading by adding the `PIXEL_ENABLE_ACCURATE_FADING` preprocessor directive to your project, but note that this uses an additional 3 bytes of RAM per Pixel.

If you don't need fading and want to disable it altogether, use the `PIXEL_DISABLE_FADING` preprocessor directive. This frees 3 bytes of RAM per Pixel and results in faster refresh times. If you want to toggle fading during runtime, don't use this directive but instead use `Animation::set_fade(bool toggle)`.

#### API Changes

Many pointers have been converted to references, requiring changes to your code. The Arduino code samples have been updated to reflect this.

#### Canvas Changes

Canvas drawing methods and Cues now require you to specify which frame to draw on. This lets you draw on a specific frame without having to switch to it first.

For example, if you wanted to draw a point on frame 5, you would normally have to do this:

```c++
canvas.set_current_frame_index(5);
canvas.draw_point(x, y);
```

Now, you can use:

```c++
canvas.draw_point(5, x, y);
```

### Added
- Added ability to allocate more than one Section when declaring a Maestro.
- Added ability to mirror Sections across the x and y axes.
- Added two new Animation orientations: `HorizontalFlipped` and `VerticalFlipped`
- Added `CueController:BlockedCues`, which let you block specific Cues from executing.
- Added performance-related preprocessor directives:
    - `PIXEL_DISABLE_FADING` disables fading, which saves 3 bytes of RAM per Pixel.
	- `PIXEL_ENABLE_ACCURATE_FADING` enables more accurate color reproduction when fading is enabled. Requires an additional 3 bytes of RAM.
- Added `Point::in_bounds(x, y)`, which checks whether the coordinates provided are within the boundaries of the Point (when used as a dimension).

### Changed
- Changed several internal pointers to references. This may require code changes to your Arduino sketches.
- Rewrote Pixel rendering logic to improve performance.
- Merged the `MappedAnimation` class into the base `Animation` class. All Animations now use maps to store color data per frame.
- Rewrote CueHandlers to reduce program size.
- Fixed `CanvasCueHandler::draw_frame()` not supporting frames larger than 255x255.
- Increased Canvas frame count from an 8-bit integer to a 16-bit integer.
- Fixed bug where `Section::set_offset()` wasn't affecting Canvases.
- Fixed bug where `AnimationTimer::delay_` wasn't being properly calculated or applied.
- Increased maximum Cue buffer size from a 16-bit integer to a 32-bit integer.
- Fixed Show crash when enabling relative time and looping after the Show has already ended.
- Renamed `Section::set_one()` to `Section::set_pixel_color()`.
- Modified `CueController::read()` to check the read index against the buffered Cue's size before trying to run the buffered Cue.
- Fixed memory leak when removing a Canvas or Animation without first removing its Palette.
- Added Handler nullptr checks to `CueController::run()` methods.

### Removed
- Removed `WaveAnimation` mirror option.
- Removed `Canvas::in_bounds()` (see `Point::in_bounds()` instead).
- Removed mirror option in `AnimationCueHandler::set_wave_options`.

## [v1.0.2] - 2018-12-03
### Added
- Added per-Section brightness controls.

## [v1.0.1] - 2018-11-23
### Added
- Added `Show::sync()` for synchronizing Show timer with Maestro timer.
- Added `Maestro::remove_show()` to allow Shows to be deleted.
- Added `Utility::srand()` for setting the initial RNG seed.

### Changed
- Added `library.json` for PlatformIO compatibility.
- Updated `platformio.ini`.

## [v1.0.0] - 2018-07-29
### Changed
- Fixed memory leak when building `MappedAnimations` maps.

## [v0.30.3] - 2018-06-30

### Changed
- Follow [Semantic Versioning](https://semver.org/) specifications.

## [v0.30 r2] - 2018-06-24

### Changed
- Merged Arduino IDE-compatible changes provided by [per1234](https://github.com/per1234/)

## [v0.30] - 2018-04-18
WARNING: This update breaks backwards compatability with v0.20.1 and earlier Cuefiles.

### Added
- Arduino
	- Added `USB` Arduino sketch for use with PixelMaestro Studio. This sketch lets you store Maestros in persistent memory (EEPROM) and run commands in real-time.
	- Added modified [light_WS2812](https://github.com/cpldcpu/light_ws2812) library to reduce sketch sizes.
	
### Changed
- Animations
	- Converted Plasma animation to a `MappedAnimation`.
- Canvas
	- Consolidated all three Canvas types into the base Canvas class. This "new" Canvas class is structured like a PaletteCanvas with transparency support.
- CueController
	- Replaced `enable_handler()` with separate methods to reduce Arduino sketch sizes.
	- Fixed crash when reading a Cue whose CueHandler isn't enabled.
- CueHandler: Added `serialize_palette()` and `deserialize_palette()` methods.
- Section
	- Pixels now reset their values after calling `Section::remove_animation()`.
	
### Removed
- Section: Removed `set_one(uint32_t index...)`
- Canvas: Removed different Canvas types.

## [v0.20] - 2018-03-17
WARNING: This update breaks backwards compatability with Cuefiles from v0.12 and earlier.

### Added
- Animations
	- Added new `Palette` class for managing color palettes. Palettes take and store an array of `RGB` colors for use in `Animations` and `PaletteCanvases`.
	- Added fire animation.
	- Added `skew` and `mirror` parameters to Wave animation. Skew offsets each row (or column) by the specified number of Pixels. Mirror reflects the grid along the orientation axis.
- Canvas
	- Added `Canvas::set_drawing_color()`, which sets the color used when calling `activate()`. Applies to ColorCanvases and PaletteCanvases.
- ColorPresets
	- Added Palette presets.
- Cues
	- Added `Canvas::activate()` and `Canvas::deactivate()` Cues.
	- Added `Section::remove_animation()` Cue.
	- Added `Maestro::set_brightness()` Cue.
- Maestros
	- Added boolean return value to `Maestro::update()`. This returns true if the Maestro runs its update (i.e. its refresh Timer triggers).
- Timers
	- Added `start()` and `stop()` methods to all Timers..
	
### Changed
- Animations
	- Removed vertical orientation from the Mandelbrot Animation.
	- Renamed `Animation::pause` to `Animation::delay`. Now it actually acts as a delay timer, waiting the specified amount of time before starting the next cycle.
	- Replaced `LightningAnimation::up_threshold` and `LightningAnimation::down_threshold` with `LightningAnimation::drift`. Drift is a signed integer, where negative values indicate a downward drift and positive values indicate a upward drift.
- Layers
	- Rewrote Layer mixing algorithm. This fixes an issue when combining the Overlay and Alpha MixModes in Sections with more than one Layer.
- Shows
	- Renamed `set_timing()` to `set_timing_mode()` to prevent confusion with `Timers`.
- Timers
	- Set default interval time to `1000`.
	- Changed `AnimationTimer::pause` to `delay`. Now it waits the specified amount of time before running the next cycle.
- _Many_ bugfixes.
	
### Removed
- Animations
	- Removed color parameters from `Section::set_animation()`. You must now set a color palette using `Animation::set_colors()`.
	- Replaced color arrays with new `Palette` class. You will have to set a Palette using `Animation::set_colors()`. Both Animations and PaletteCanvases can use Palettes.
	- Merge animation is replaced by the Wave animation. Use `WaveAnimation::set_mirror(true)` to simulate merging.
	- Removed Mandelbrot animation's vertical orientation.
- Cues
	- Removed Events list parameter from `MaestroCueHandler::set_show()`. You need to call `ShowCueHandler::set_events()` to initialize the Event list.
- Shows
	- Removed requirement that Events needed to have an Event time > 0. Events with an event time of 0 will now run immediately.

## [v0.12] - 2018-01-22
### Changed
- Event: Increased buffer size.
- Section:
	- Changed Scrolling parameters. Parameters now represent the amount of time to complete a scroll along the respective axis. Added separate reverse parameters for reversing the scrolling direction.
	- Modified `set_one()` so that it can be used without an Animation.

## [v0.11] - 2017-12-23
### Added
- Added `PaletteCanvas` class. PaletteCanvases draw shapes using colors defined in a palette, similar to Animations.

### Changed
- AnimationCueController: Fixed index counter overflow when processing large color palettes.
- Canvas:
	- Fixed exception when setting frame count below `current_frame_index`.
	- Fixed and added checks on `next_frame()`, `delete_frames()`, and `set_current_frame_index()`.
- Cues:
	- Fixed issue in `SectionCueHandler::set_animation()` where the old color palette was deleted before the new palette was assigned.
	- Fixed issue where `ShowCueHandler::Actions::SetTiming` was identified as `SetEvents`, causing Show Cues to fail.
- Section: Added ability to copy attributes when using `Section::set_animation()`.

## [v0.10] - 2017-12-05
### Added
- Arduino: Added new sketches and modified existing sketches for clarity.
- Docs: Moved all docs into a GitHub wiki.
- Show: Added `get_current_index()` to get the current queued Event.

### Changed
- Moved project into Beta state.
- Moved `arduino` folder into new `examples` folder.
- Canvas: Moved scrolling and offseting methods to Section.
- Pixel: Added nullptr check to `Pixel::set_next_color()` to prevent invalid colors when using color changing Cues.
- Several bugfixes and optimizations.

### Removed
- Removed ability to set an Animation's center (use Section offset instead).
- Removed `Scroll::repeat` parameter. The grid will repeat by default.

## [v0.9] - 2017-11-28
### Added
- New Timing class handles animations and other time-based actions.
- Arduino:
	- Added NeoPixel sketch.
- Canvas:
	- Added `set_frame_timing()` to control delay between frame switches.

### Changed
- All components that rely on timing (Animation speed/pause, Maestro refresh, Canvas scrolling, etc) now use the Timing class. `get/set_speed()`, `get/set_refresh_interval()` etc. now use `get/set_timing()`.
- Cue:
	- Fixed issue where Show Cues weren't properly saving or loading.
- Section:
	- Added a reference to each Section's parent Maestro.
	- Renamed `Overlays` to `Layers`.

### Removed
- Maestro:
	- Removed `running` option.
- Removed several redundant or unused functions/methods.

## [v0.8.1] - 2017-11-14
### Changed
- Split PixelMaestro Studio into separate project.

## [v0.8] - 2017-11-13
### Added
- Canvas:
	- Added support for animated drawings. Learn more in the [Canvas docs](docs/canvas.md).
- Cues:
	- Added CueHandler for Shows.
- Maestro:
	- Added simplified constructor for creating a Maestro with only one Section.
	- Added the option to bypass a Maestro's refresh rate and force it to update.
- Studio:
	- New Palette Editor dialog lets you create, edit, and delete color palettes.
	- New Simulated Device dialog lets you preview how actions performed in the Animation Editor will appear on serial devices.
	- Added support for displaying and controlling multiple Sections simultaneously. You can set the number of Sections in the Settings window.
	- Added the ability to add and remove Overlays.
	- Added number box to speed slider.
	- Added slider to control Animation pause threshold.
	- Added support for loading images into Canvases.
	- Added Show editor (in progress).

### Changed
- Canvas:
	- Fixed Canvas scrolling behavior.
- Colors:
	- Moved pre-defined colors and palettes into `ColorPresets` class.
	- Replaced `Colors::generate_random_colors()` with a truly random color generator.
- Cue:
	- Added and fixed several Cues.
- Pixel:
	- Improved Pixel color changing logic.
- Studio:
	- Renamed GUI project to "PixelMaestro Studio".
	- Renamed "Animation Previewer" to "Animation Editor".
	- Added Cues for several Animation Editor actions.
	- Fixed settings not populating correctly when switching between Sections.
	- Improved saving to and loading from Cue (.pmc) files.
	- Fixed Canvas contents getting deleted on resize.
	- Set minimum application window size.
	- Changed status bar text when opening Workspaces.
	- Updated several demos.

### Removed
- Removed pre-defined colors and color arrays from Colors class. You can now find them in the ColorPresets class.

## [v0.7] - 2017-10-07
### Added
- Animation Previewer:
	- Added support for sending commands to devices connected via USB/serial.
	- Added Preferences dialog. This lets you select a port for commands as well as change the appearance of the Animation Previewer. You can access it by clicking `Edit > Preferences`.
	- Added support for saving Maestro configurations to file as a series of Cues.
- Cue:
	- Added classes for converting PixelMaestro actions into portable commands. This allows you to control remote devices, save and load presets, schedule commands for later exection, and more. See the [`Cue` documentation page](docs/cue.md) for details.
	- Added Cue Demo to the GUI.
- Canvas:
	- Added `ColorCanvas` class for drawing Canvas objects using specified colors.
	- Added Color Canvas Demo to the GUI.

### Changed
- Animation Previewer:
	- Changed row and column fields to only update the grid when losing focus.
- Animations:
	- Sections now manage memory allocation for Animations. `Section::set_animation()` now takes an enum value as a parameter instead of an Animation object. The Animation is automatically allocated and destroyed when changing Animations or destroying the Section.
	- Fixed issue where LightningAnimations generated multiple bolts with the same starting location.
	- Added resolution parameter to Radial Animation (only affects vertical mode).
- Canvas:
	-Renamed `Canvas` to `AnimationCanvas`. The `Canvas` class now acts as a base class for new Canvas types.
- Maestro
	- Moved control of the refresh rate from Sections to Maestros.
	- Changed default refresh rate to 40ms (25fps).
- Section:
	- Changed `add_canvas()` and `add_overlay()` to `set_canvas()` and `set_overlay()`.
- Show:
	- Modified Events to store and run Cues. `Event` is essentially just a wrapper class for Cues.
	- Removed all extended Event classes.

### Removed
- Removed extended Event classes.

### Known Issues
- Loading Cues from a file is not supported.
- After opening the Animation Previewer, serial devices won't display animations until you change to a different animation.
- After changing the serial device port while the Animation Previewer is open, commands will continue being sent to the old port until you reopen the Animation Previewer.

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
