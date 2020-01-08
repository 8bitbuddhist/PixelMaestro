#ifndef SECTIONCUEHANDLER_H
#define SECTIONCUEHANDLER_H

#include "../animation/animationtype.h"
#include "../core/colors.h"
#include "cuecontroller.h"

namespace PixelMaestro {
	class SectionCueHandler : public CueHandler {
		public:
			enum class Action : uint8_t {
				RemoveAnimation,
				RemoveCanvas,
				RemoveLayer,
				SetAnimation,
				SetCanvas,
				SetDimensions,
				SetLayer,
				SetOffset,
				SetScroll,
				SetBrightness,
				SetMirror,
				SetWrap
			};

			enum class Byte : uint8_t {
				HandlerByte = (uint8_t)CueController::Byte::PayloadByte,
				ActionByte,
				SectionByte,
				LayerByte,
				OptionsByte
			};

			explicit SectionCueHandler(CueController& controller) : CueHandler(controller) { }
			~SectionCueHandler() = default;
			uint8_t* remove_animation(uint8_t section_num, uint8_t layer_num, bool clear_pixels);
			uint8_t* remove_canvas(uint8_t section_num, uint8_t layer_num);
			uint8_t* remove_layer(uint8_t section_num, uint8_t layer_num);
			uint8_t* set_animation(uint8_t section_num, uint8_t layer_num, AnimationType animation_type, bool preserve_settings = false);
			uint8_t* set_brightness(uint8_t section_num, uint8_t layer_num, uint8_t brightness);
			uint8_t* set_canvas(uint8_t section_num, uint8_t layer_num, uint16_t num_frames = 1);
			uint8_t* set_dimensions(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y);
			uint8_t* set_layer(uint8_t section_num, uint8_t layer_num, Colors::MixMode mix_mode, uint8_t alpha);
			uint8_t* set_mirror(uint8_t section_num, uint8_t layer_num, bool x, bool y);
			uint8_t* set_offset(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y);
			uint8_t* set_scroll(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y, bool reverse_x = false, bool reverse_y = false);
			uint8_t* set_wrap(uint8_t section_num, uint8_t layer_num, bool wrap);
			void run(uint8_t* cue);
	};
}

#endif // SECTIONCUEHANDLER_H
