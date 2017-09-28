#ifndef SECTIONCUE_H
#define SECTIONCUE_H

#include "../canvas/canvastype.h"
#include "../core/colors.h"
#include "../core/maestro.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class SectionCue : public Cue {
		public:
			enum Action {
				AddCanvas,
				AddOverlay,
				SetAnimation,
				SetDimensions
			};

			enum Bit {
				ComponentBit = (int)CueController::Bit::PayloadBit,
				ActionBit,
				SectionBit,
				OptionsBit
			};

			SectionCue(Maestro* maestro, unsigned char* buffer) : Cue(maestro, buffer) {}
			void add_canvas(unsigned char section_num, CanvasType::Type canvas_type);
			void add_overlay(unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha);
			void set_animation(unsigned char section_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, unsigned char num_colors);
			void set_dimensions(unsigned char section_num, unsigned short x, unsigned short y);
			void run(unsigned char* cue);
	};
}

#endif // SECTIONCUE_H
