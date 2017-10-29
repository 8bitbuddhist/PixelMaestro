#ifndef SECTIONCUEHANDLER_H
#define SECTIONCUEHANDLER_H

#include "../animation/animationtype.h"
#include "../canvas/canvastype.h"
#include "../core/colors.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class SectionCueHandler : public CueHandler {
		public:
			enum Action : uint8_t {
				RemoveCanvas,
				SetAnimation,
				SetCanvas,
				SetDimensions,
				SetOverlay
			};

			enum Byte : uint8_t {
				HandlerByte = (int)CueController::Byte::PayloadByte,
				ActionByte,
				SectionByte,
				OverlayByte,
				OptionsByte
			};

			SectionCueHandler(CueController* controller) : CueHandler(controller) { }
			~SectionCueHandler();
			void remove_canvas(uint8_t section_num, uint8_t overlay_num);
			void set_animation(uint8_t section_num, uint8_t overlay_num, AnimationType::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, uint8_t num_colors);
			void set_canvas(uint8_t section_num, uint8_t overlay_num, CanvasType::Type canvas_type, uint16_t num_frames = 1);
			void set_dimensions(uint8_t section_num, uint8_t overlay_num, uint16_t x, uint16_t y);
			void set_overlay(uint8_t section_num, uint8_t overlay_num, Colors::MixMode mix_mode, uint8_t alpha);
			void run(uint8_t* cue);
	};
}

#endif // SECTIONCUEHANDLER_H
