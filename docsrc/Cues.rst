
Cues
====

A Cue is a serialized PixelMaestro command that can be saved to a file or sent to another device running PixelMaestro. Cues let you control PixelMaestro devices remotely, save your Maestro configurations to file, or even :doc:`schedule actions <Shows>` to run automatically at a later time.

.. _cues-overview:
Getting Started
---------------

Using Cues involves the following steps:

1. Initialize a ``CueController`` using ``Maestro::set_cue_controller()``. CueControllers handle serializing and deserializing Cues, and passing them to/from ``CueHandlers``.
2. Initialize one or more ``CueController::CueHandlers``, which translate PixelMaestro commands into Cues and vice versa. Each PixelMaestro component has its own dedicated ``CueHandler``, e.g. Sections have a ``SectionCueHandler``.
3. (Optional) Initialize a ``Show`` to schedule and store Cues to run at a later time. You can learn more in the :doc:`Show documentation <Shows>`.

.. Important:: Using both Cues and direct commands in the same Maestro could cause undefined behavior! If you enable Cues on a Maestro, then you should only use Cues.

.. _cues-initializing:
Initializing the CueController
------------------------------

The first step is to initialize the CueController. The CueController handles creating and processing all Cues. To initialize the CueController, use ``Maestro::set_cue_controller()``. Alternatively, you can initialize both the CueController and a Show simultaneously using :doc:`Maestro::set_show() <Shows>`.

.. code-block:: c++

   #include "core/maestro.h"
   #include "cue/cuecontroller.h"
   ...
   CueController& controller = maestro.set_cue_controller();

.. _cues-buffer-size:
Changing the Buffer Size
^^^^^^^^^^^^^^^^^^^^^^^^

The CueController allocates a buffer for temporarily holding Cues. When a Cue is being created or processed, it is held in this buffer. The buffer must be large enough to hold the entire Cue or else the CueController will drop the Cue. The default buffer size is 256 bytes to accomodate low-memory devices like Arduino.

While most Cues are relatively small (20-30 bytes), some Cues can be several kilobytes. You can increase the buffer size by passing in a size when calling ``maestro.set_cue_controller(uint32_t size)``. 100 KB is generally large enough for most Cues, although you might want to increase this if you plan on using ``Canvas`` Cues.

.. code-block:: c++

   uint32_t buffer_size = 100000; // 100 KB buffer
   CueController& controller = maestro.set_cue_controller(buffer_size);

.. _cues-enabling-cuehandlers:
Enabling CueHandlers
^^^^^^^^^^^^^^^^^^^^

``CueHandlers`` map Cues to PixelMaestro commands and vice versa. Each of the core PixelMaestro classes has an associated ``CueHandler`` that provides methods that translate directly to native PixelMaestro methods and generate Cues as a result. For example, ``SectionCueHandler`` has ``set_animation``, ``set_canvas``, ``set_dimensions``, and other methods that directly correspond to the methods in the ``Section`` class.

To use a CueHandler, you first need to initialize it using ``CueController::enable_<component name>_cue_handler();``. This initializes the CueHandler and registers it with the CueController so that the CueController can pass the appropriate Cues to it. For example, enabling a ``SectionCueHandler`` notifies the CueController to pass any Section-related Cues that it receives to the handler. If the CueController receives a Cue but can't match it to an appropriate CueHandler, it drops the Cue.

.. code-block:: c++

   // Creates a new SectionCueHandler
   SectionCueHandler& handler = static_cast<SectionCueHandler&>(controller.enable_section_cue_handler());

.. Tip:: To reduce program size and memory on low-power devices, only enable the CueHandlers that you need.

.. _cues-creating:
Creating and Running Cues
-------------------------

Cues are created by calling a method on an enabled CueHandler. CueHandler methods are generally identical to the methods present in their corresponding PixelMaestro class. ``SectionCueHandler`` methods require two new parameters: ``section`` and ``layer``, where ``section`` is the index of the Section that you want to modify (according to the Maestro's section array), and ``layer`` is the index of the Layer you want to modify relative to the Section itself. For instance, a Layer index of ``0`` modifies the base Section, and an index of ``1`` modifies the Section's immediate Layer. If a Section or Layer doesn't exist at those indices, then PixelMaestro will drop the Cue.

For example, let's use Cues to add a Layer to a Section, then add an Animation to the Layer. We'll start by enabling the required CueHandlers, then use the returned pointer to call a CueHandler method. Each call generates a new Cue and stores it in the CueController's buffer, which we then execute. We have to execute the Cue after each CueHandler call, or else the CueController will overwrite the buffer with the next Cue.

.. Tip:: You can get the currently buffered Cue using ``CueController::get_cue()``.

.. code-block:: c++

   #include "cue/sectioncuehandler.h"

   // Initialize the CueController
   CueController& controller = maestro.set_cue_controller();

   // The index of the Section (in `Maestro::sections_`).
   int section_index = 0;

   // The index of the Layer.
   int layer_index = 0;

   // Enable Section and Animation CueHandlers
   SectionCueHandler& section_handler = static_cast<SectionCueHandler&>(controller.enable_section_cue_handler());
   AnimationCueHandler& animation_handler = static_cast<AnimationCueHandler&>(controller.enable_animation_cue_handler());

   // Create a new Layer
   section_handler.set_layer(section_index, layer_index, Colors::MixMode::Overlay);
   controller.run();

   // Create an Animation on the new Layer
   layer_index = 1;
   section_handler.set_animation(section_index, layer_index, AnimationType::Solid);
   controller.run();

   // Set the Animation's Palette
   animation_handler.set_palette(section_index, layer_index, &ColorPresets::Colorwheel_Palette);
   controller.run();

.. _cues-running:
More Ways of Running Cues
-------------------------

To run a Cue stored in the CueController buffer, use ``CueController::run()``. You can also run a Cue using ``CueController::run(unsigned char* cue)``, where ``cue`` is a pointer to the Cue you want to run.

For cases where you need to read in parts of a Cue at a time (e.g. using ``Serial.read()`` on an Arduino), use ``CueController::read(byte)``. This reads the Cue byte-by-byte into the CueController's buffer until the Cue is completely loaded, then runs the Cue. The CueController then resets the buffer and repeats the process for the next incoming Cue. You can feed in a continuous stream of bytes and the CueController will automatically detect when one Cue ends and the next one begins.

.. code-block:: c++

   // Setup
   Serial.begin(9600);

   // Loop
   if (Serial.available()) {
       controller.read(Serial.read());
   }

.. _cues-blocking:
Blocking Cues
-------------

If you want to prevent a CueController from running certain Cues, you can block them, and the CueController will drop them. This is useful for preventing expensive Cues from running on low-power devices, such as ``Section::SetDimensions`` and ``Canvas::DrawFrame``.

First, create an array of ``CueController::BlockedCues``. A ``BlockedCue`` consists of a ``CueHandler`` and the integer representation of an ``Action``. For example, here we block ``SectionCueHandler::SetDimensions``:

.. code-block:: c++

   CueController::BlockedCue* block = new CueController::BlockedCue[1] {
     CueController::BlockedCue(CueController::Handler::SectionCueHandler, (uint8_t)SectionCueHandler::Action::SetDimensions)
   };

   controller.set_blocked_cues(block, 1);

Now, if the device receives a Cue to change its dimensions, it will ignore the Cue instead of running it.

.. _cues-structure:
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
     - An index representing the PixelMaestro command that this Cue maps to.
   * - 10
     - SectionByte
     - The index of the Section that this Cue modifies. Only applies to Section-level Cues.
   * - 11
     - LayerByte
     - The index of the Layer that this Cue modifies in relation to its base Section (e.g. a value of *1* refers to the Section's Layer).
   * - 12
     - OptionsByte
     - A variable-length set of options specific to each Action. Most Options are less than 10 bytes long, but some (e.g. drawing a Canvas frame) can be several kilobytes. If the payload doesn't fit within the CueController's buffer, the CueController will ignore the Cue.

