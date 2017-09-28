#ifndef ANIMATIONCUE_H
#define ANIMATIONCUE_H

#include "../animation/animation.h"
#include "../core/colors.h"
#include "../core/maestro.h"
#include "cue.h"
#include "sectioncue.h"

namespace PixelMaestro {
	class AnimationCue {
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
				ComponentBit = Cue::Bit::PayloadBit,
				ActionBit,
				SectionBit,
				OptionsBit
			};

			// Animation-specific options
			static void set_lightning_options(unsigned char* buffer, unsigned char section_num, unsigned char num_bolts, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance);
			static void set_plasma_options(unsigned char* buffer, unsigned char section_num, float size, float resolution);
			static void set_sparkle_options(unsigned char* buffer, unsigned char section_num, unsigned char threshold);

			// General Animation calls
			static void set_colors(unsigned char* buffer, unsigned char section_num, Colors::RGB* colors, unsigned char num_colors);
			static void set_cycle_index(unsigned char* buffer, unsigned char section_num, unsigned char cycle_index);
			static void set_fade(unsigned char* buffer, unsigned char section_num, bool fade);
			static void set_orientation(unsigned char* buffer, unsigned char section_num, Animation::Orientation orientation);
			static void set_reverse(unsigned char* buffer, unsigned char section_num, bool reverse);
			static void set_speed(unsigned char* buffer, unsigned char section_num, unsigned short speed, unsigned short pause);

			static void run(Maestro* maestro, unsigned char* cue);

			static Animation* initialize_animation(unsigned char* cue);
	};
}

#endif // ANIMATIONCUE_H
