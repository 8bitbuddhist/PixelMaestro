#ifndef ANIMATIONCUEHANDLER_H
#define ANIMATIONCUEHANDLER_H

#include "../animation/animation.h"
#include "../core/colors.h"
#include "../core/maestro.h"
#include "cuehandler.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class AnimationCueHandler : public CueHandler {
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

			enum Byte {
				HandlerByte = CueController::Byte::PayloadByte,
				ActionByte,
				SectionByte,
				OverlayByte,
				OptionsByte
			};

			AnimationCueHandler(CueController* controller) : CueHandler(controller) { }
			~AnimationCueHandler();
			// Animation-specific calls
			void set_lightning_options(unsigned char section_num, unsigned char overlay_num, unsigned char num_bolts, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance);
			void set_plasma_options(unsigned char section_num, unsigned char overlay_num, float size, float resolution);
			void set_sparkle_options(unsigned char section_num, unsigned char overlay_num, unsigned char threshold);

			// General Animation calls
			void set_colors(unsigned char section_num, unsigned char overlay_num, Colors::RGB* colors, unsigned char num_colors);
			void set_cycle_index(unsigned char section_num, unsigned char overlay_num, unsigned char cycle_index);
			void set_fade(unsigned char section_num, unsigned char overlay_num, bool fade);
			void set_orientation(unsigned char section_num, unsigned char overlay_num, Animation::Orientation orientation);
			void set_reverse(unsigned char section_num, unsigned char overlay_num, bool reverse);
			void set_speed(unsigned char section_num, unsigned char overlay_num, unsigned short speed, unsigned short pause);

			void run(unsigned char* cue);

			static Animation* initialize_animation(unsigned char* cue);
	};
}

#endif // ANIMATIONCUEHANDLER_H
