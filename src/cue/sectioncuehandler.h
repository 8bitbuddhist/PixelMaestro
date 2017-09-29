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
			void add_canvas(unsigned char section_num, unsigned char overlay_num, CanvasType::Type canvas_type);
			void add_overlay(unsigned char section_num, unsigned char overlay_num, Colors::MixMode mix_mode, unsigned char alpha);
			void set_animation(unsigned char section_num, unsigned char overlay_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, unsigned char num_colors);
			void set_dimensions(unsigned char section_num, unsigned char overlay_num, unsigned short x, unsigned short y);
			void run(unsigned char* cue);
	};
}

#endif // SECTIONCUEHANDLER_H
