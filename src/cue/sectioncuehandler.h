#ifndef SECTIONCUEHANDLER_H
#define SECTIONCUEHANDLER_H

#include "../canvas/canvastype.h"
#include "../core/colors.h"
#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class SectionCueHandler : public CueHandler {
		public:
			enum Action {
				AddCanvas,
				AddOverlay,
				SetAnimation,
				SetDimensions
			};

			enum Byte {
				HandlerByte = (int)CueController::Byte::PayloadByte,
				ActionByte,
				SectionByte,
				OverlayByte,
				OptionsByte
			};

			SectionCueHandler(CueController* controller) : CueHandler(controller) { }
			~SectionCueHandler();
			void add_canvas(uint8_t section_num, uint8_t overlay_num, CanvasType::Type canvas_type);
			void add_overlay(uint8_t section_num, uint8_t overlay_num, Colors::MixMode mix_mode, uint8_t alpha);
			void set_animation(uint8_t section_num, uint8_t overlay_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, uint8_t num_colors);
			void set_dimensions(uint8_t section_num, uint8_t overlay_num, uint16_t x, uint16_t y);
			void run(uint8_t* cue);
	};
}

#endif // SECTIONCUEHANDLER_H
