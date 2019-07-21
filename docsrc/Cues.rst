
Cues
====

Cues are serialized PixelMaestro commands. Using Cues, you can control a device running PixelMaestro remotely, save your configurations to a file, or `schedule actions <Shows.html>`_ to run at a later time.

.. Important:: Avoid using both Cues and standard commands on the same device, as it could cause undefined behavior!

Overview
--------

There are several components involved in managing Cues:


* ``CueHandlers`` translate PixelMaestro commands into Cues, and vice versa.
* ``CueControllers`` transport Cues to and from ``CueHandlers``. All Cues pass through the CueController. CueControllers are managed by `Maestros <Maestros.html>`_.
* ``Shows`` schedule and store Cues for later execution. You can learn more in the `Show documentation <Shows.html>`_.

Initializing the CueController
------------------------------

The first step is to initialize the CueController by calling ``Maestro::set_cue_controller()``. Calling `Maestro::set_show() <Shows.html>`_ also starts the CueController.

.. code-block:: c++

   #include "core/maestro.h"
   #include "cue/cuecontroller.h"
   ...
   CueController& controller = maestro.set_cue_controller();

Setting the Buffer Size
^^^^^^^^^^^^^^^^^^^^^^^

When a Cue is being created or processed, it is temporarily held in a buffer. This buffer must be large enough to hold the entire Cue or else the CueController will drop the Cue. While most Cues are relatively small (20-30 bytes), some Cues can be several kilobytes. The default buffer size is 256 bytes.

You can specify a custom buffer size when calling ``maestro.set_cue_controller(uint32_t size)``. This way, you can allocate a larger or smaller buffer depending on the amount of memory available on your device.

.. code-block:: c++

   uint32_t buffer_size = 70000; // 70 KB
   CueController& controller = maestro.set_cue_controller(buffer_size);

Enabling CueHandlers
^^^^^^^^^^^^^^^^^^^^

``CueHandlers`` are responsible for mapping Cues to and from PixelMaestro commands. Each of the core PixelMaestro classes has an associated ``CueHandler`` that translates the class' methods to and from Cues. For example, ``SectionCueHandler`` has ``set_animation``\ , ``set_canvas``\ , ``set_dimensions``\ , and other methods that directly correspond to the methods in the ``Section`` class.

To use a CueHandler, you first need to initialize it using ``CueController::enable_<component name>_cue_handler();``. This initializes the CueHandler and registers it with the CueController so that the CueController can pass the appropriate Cues to it. For example, enabling a ``SectionCueHandler`` notifies the CueController to pass any Section-related Cues that it receives to the handler. If the CueController receives a Cue but can't match it to an appropriate CueHandler, it drops the Cue.

.. code-block:: c++

   // Creates a new SectionCueHandler
   SectionCueHandler& handler = static_cast<SectionCueHandler&>(controller.enable_section_cue_handler());

.. Tip:: To reduce program size and memory, only enable the CueHandlers that you need.

Creating Cues
-------------

Cues are created by calling a method on an enabled CueHandler. CueHandler methods are generally identical to the methods present in their corresponding PixelMaestro class, but Section-related CueHandler methods require two new parameters: ``section`` and ``layer``. ``section`` is the index of the Section that you want to modify (according to the Maestro's section array), and ``layer`` is the index of the Layer you want to modify relative to the Section itself. For instance, a Layer index of ``1`` modifies the Section's direct Layer, and an index of ``2`` modifies that Layer's Layer. Leaving the Layer index at 0 modifies the Section itself.

For example, let's use Cues to add a Layer to a Section and an Animation to the Layer. We'll start by enabling the required CueHandlers. Note that enabling a CueHandler returns a pointer to the CueHandler instance. We'll use this to call the CueHandler's methods. Each call generates a new Cue and stores it in the CueController's buffer. We then tell the CueController to run the Cue stored in the buffer before moving to the next Cue.

.. Tip:: You can get the currently buffered Cue using ``CueController::get_cue()``.

.. code-block:: c++

   #include "cue/sectioncuehandler.h"

   ...
   // The index of the Section (in `Maestro::sections_`).
   int section_index = 0;

   // How far down the Layer is.
   // For example, an index of 1 affects the base Section's Layer, while an index of 2 affects the Layer's Layer.
   int layer_index = 0;

   // Enable CueHandlers
   SectionCueHandler& section_handler = static_cast<SectionCueHandler&>(controller.enable_section_cue_handler());
   AnimationCueHandler& animation_handler = static_cast<AnimationCueHandler&>(controller.enable_animation_cue_handler());

   // Set the new Layer
   section_handler.set_layer(section_index, layer_index, Colors::MixMode::Overlay);
   controller.run();

   // Create an Animation on the new Layer
   layer_index += 1;
   section_handler.set_animation(section_index, layer_index, AnimationType::Solid);
   controller.run();

   // Set the Animation's Palette
   animation_handler.set_palette(section_index, layer_index, &ColorPresets::Colorwheel_Palette);
   controller.run();

Running Cues
------------

To run a Cue stored in the CueController buffer, use ``CueController::run()``. You can also run a Cue using ``CueController::run(unsigned char* cue)``\ , where ``cue`` is a pointer to the Cue you want to run.

For cases where you need to read in parts of a Cue at a time (e.g. using ``Serial.read()`` on an Arduino), use ``CueController::read(byte)``. This reads the Cue byte-by-byte into the CueController's buffer until the Cue is completely loaded, then runs the Cue. The CueController then resets the buffer and repeats the process for the next incoming Cue. You can feed in a continuous stream of bytes and the CueController will automatically detect when one Cue ends and the next one begins.

.. code-block:: c++

   // Setup
   Serial.begin(9600);

   // Loop
   if (Serial.available()) {
       controller.read(Serial.read());
   }

Blocking Cues
-------------

You can tell the CueController to prevent certain Cues from executing. This is useful for blocking expensive Cues (such as Section::SetDimensions and Canvas::DrawFrame) from running on low-memory devices.

Start by creating an array of ``CueController::BlockedCues``. A ``BlockedCue`` consists of a ``CueHandler``\ , and the integer representation of an action handled by that CueHandler. For example, here we block ``SectionCueHandler::SetDimensions``\ :

.. code-block:: c++

   CueController::BlockedCue* block = new CueController::BlockedCue[1] {
     CueController::BlockedCue(CueController::Handler::SectionCueHandler, (uint8_t)SectionCueHandler::Action::SetDimensions)
   };

   controller.set_blocked_cues(block, 1);

Now, if the device receives a Cue to change its dimensions, it will ignore the Cue instead of running it.

**The following sections are for reference only.**

Structure
---------

Cues are byte arrays approximately 20-50 bytes long. Each Cue consists of a *header* and a *payload*. A CueHandler assembles a payload, and the CueController assembles the header.

.. Note:: The ID and checksum are used as validation only when reading in Cues from outside.

 Payloads vary in length depending on the command, but each payload contains most of the following parameters.

.. list-table::
   :header-rows: 1

   * - Index
     - Name
     - Description
   * - 0
     - IDByte1
     - The first character marking the start of a Cue ('P').
   * - 1
     - IDByte2
     - The second character marking the start of a Cue ('M').
   * - 2
     - IDByte3
     - The third character marking the start of a Cue ('C').
   * - 3
     - ChecksumByte
     - Calculated value for checking the integrity of a Cue.
   * - 4
     - SizeByte1
     - Stores the first part of the Cue's size.
   * - 5
     - SizeByte2
     - Stores the second part of the Cue's size.
   * - 6
     - SizeByte3
     - Stores the third part of the Cue's size.
   * - 7
     - SizeByte4
     - Stores the fourth part of the Cue's size.
   * - 8
     - PayloadByte/HandlerByte
     - The CueHandler that generated this Cue, and the start of the payload. This tells the CueController which CueHandler to forward the Cue to.
   * - 9
     - ActionByte
     - The PixelMaestro command that this Cue represents.
   * - 10
     - SectionByte
     - The index of the Section that this Cue modifies. Only applies to Section-level Cues.
   * - 11
     - LayerByte
     - The index of the Layer that this Cue modifies in relation to its base Section (e.g. a value of *1* refers to the Section's Layer).
   * - 12
     - OptionsByte
     - A variable-length set of options specific to each Action. Most Options are less than 10 bytes long, but some (e.g. drawing a Canvas frame) can be several kilobytes. If the payload doesn't fit within the CueController's buffer, the CueController will ignore the Cue.

