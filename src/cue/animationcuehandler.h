#ifndef ANIMATIONCUEHANDLER_H
#define ANIMATIONCUEHANDLER_H

#include "../animation/animation.h"
#include "../core/colors.h"
#include "cuehandler.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class AnimationCueHandler : public CueHandler {
		public:
			enum Action : uint8_t {
				SetColors,
				SetCycleIndex,
				SetFade,
				SetLightningOptions,
				SetOrientation,
				SetPlasmaOptions,
				SetRadialOptions,
				SetReverse,
				SetSparkleOptions,
				SetSpeed
			};

			enum Byte : uint8_t {
				HandlerByte = CueController::Byte::PayloadByte,
				ActionByte,
				SectionByte,
				OverlayByte,
				OptionsByte
			};

			AnimationCueHandler(CueController* controller) : CueHandler(controller) { }
			~AnimationCueHandler();

			// Animation-specific calls
			void set_lightning_options(uint8_t section_num, uint8_t overlay_num, uint8_t num_bolts, uint8_t down_threshold, uint8_t up_threshold, uint8_t fork_chance);
			void set_plasma_options(uint8_t section_num, uint8_t overlay_num, float size, float resolution);
			void set_radial_options(uint8_t section_num, uint8_t overlay_num, uint8_t resolution);
			void set_sparkle_options(uint8_t section_num, uint8_t overlay_num, uint8_t threshold);

			// General Animation calls
			void set_colors(uint8_t section_num, uint8_t overlay_num, Colors::RGB* colors, uint8_t num_colors, bool delete_old_colors = true);
			void set_cycle_index(uint8_t section_num, uint8_t overlay_num, uint8_t cycle_index);
			void set_fade(uint8_t section_num, uint8_t overlay_num, bool fade);
			void set_orientation(uint8_t section_num, uint8_t overlay_num, Animation::Orientation orientation);
			void set_reverse(uint8_t section_num, uint8_t overlay_num, bool reverse);
			void set_speed(uint8_t section_num, uint8_t overlay_num, uint16_t speed, uint16_t pause);

			void run(uint8_t* cue);
	};
}

#endif // ANIMATIONCUEHANDLER_H
