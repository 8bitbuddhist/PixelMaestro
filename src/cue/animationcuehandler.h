#ifndef ANIMATIONCUEHANDLER_H
#define ANIMATIONCUEHANDLER_H

#include "../animation/animation.h"
#include "../core/colors.h"
#include "cuehandler.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class AnimationCueHandler : public CueHandler {
		public:
			enum class Action : uint8_t {
				SetCycleIndex,
				SetFade,
				SetLightningOptions,
				SetOrientation,
				SetPalette,
				SetPlasmaOptions,
				SetRadialOptions,
				SetReverse,
				SetSparkleOptions,
				SetTimer,
				SetFireOptions,
				Start,
				Stop,
				SetWaveOptions
			};

			enum class Byte : uint8_t {
				HandlerByte = (uint8_t)CueController::Byte::PayloadByte,
				ActionByte,
				SectionByte,
				LayerByte,
				OptionsByte
			};

			explicit AnimationCueHandler(CueController* controller) : CueHandler(controller) { }
			~AnimationCueHandler();

			// Animation-specific calls
			uint8_t* set_fire_options(uint8_t section_num, uint8_t layer_num, uint8_t multiplier);
			uint8_t* set_lightning_options(uint8_t section_num, uint8_t layer_num, uint8_t num_bolts, uint8_t down_threshold, uint8_t up_threshold, uint8_t fork_chance);
			uint8_t* set_plasma_options(uint8_t section_num, uint8_t layer_num, float size, float resolution);
			uint8_t* set_radial_options(uint8_t section_num, uint8_t layer_num, uint8_t resolution);
			uint8_t* set_sparkle_options(uint8_t section_num, uint8_t layer_num, uint8_t threshold);
			uint8_t* set_wave_options(uint8_t section_num, uint8_t layer_num, bool mirror, int8_t skew);

			// General Animation calls
			uint8_t* set_cycle_index(uint8_t section_num, uint8_t layer_num, uint8_t cycle_index);
			uint8_t* set_fade(uint8_t section_num, uint8_t layer_num, bool fade);
			uint8_t* set_orientation(uint8_t section_num, uint8_t layer_num, Animation::Orientation orientation);
			uint8_t* set_palette(uint8_t section_num, uint8_t layer_num, Palette* palette);
			uint8_t* set_reverse(uint8_t section_num, uint8_t layer_num, bool reverse);
			uint8_t* set_timer(uint8_t section_num, uint8_t layer_num, uint16_t interval, uint16_t delay = 0);
			uint8_t* start(uint8_t section_num, uint8_t layer_num);
			uint8_t* stop(uint8_t section_num, uint8_t layer_num);

			void run(uint8_t* cue);
	};
}

#endif // ANIMATIONCUEHANDLER_H
