#ifndef ANIMATIONCUE_H
#define ANIMATIONCUE_H

#include "../animation/animation.h"
#include "../core/colors.h"
#include "../core/maestro.h"
#include "cue.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class AnimationCue : public Cue {
		public:
			enum Action {
				SetColors,
				SetCycleIndex,
				SetFade,
				SetLightningOptions,
				SetOrientation,
				SetPlasmaOptions,
				SetReverse,
				SetSparkleOptions,
				SetSpeed
			};

			enum Bit {
				ComponentBit = CueController::Bit::PayloadBit,
				ActionBit,
				SectionBit,
				OptionsBit
			};

			AnimationCue(Maestro* maestro, unsigned char* buffer) : Cue(maestro, buffer) {}
			// Animation-specific calls
			void set_lightning_options(unsigned char section_num, unsigned char num_bolts, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance);
			void set_plasma_options(unsigned char section_num, float size, float resolution);
			void set_sparkle_options(unsigned char section_num, unsigned char threshold);

			// General Animation calls
			void set_colors(unsigned char section_num, Colors::RGB* colors, unsigned char num_colors);
			void set_cycle_index(unsigned char section_num, unsigned char cycle_index);
			void set_fade(unsigned char section_num, bool fade);
			void set_orientation(unsigned char section_num, Animation::Orientation orientation);
			void set_reverse(unsigned char section_num, bool reverse);
			void set_speed(unsigned char section_num, unsigned short speed, unsigned short pause);

			void run(unsigned char* cue);

			static Animation* initialize_animation(unsigned char* cue);
	};
}

#endif // ANIMATIONCUE_H
