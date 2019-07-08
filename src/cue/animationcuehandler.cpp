#include "../animation/fireanimation.h"
#include "../animation/lightninganimation.h"
#include "../animation/plasmaanimation.h"
#include "../animation/radialanimation.h"
#include "../animation/sparkleanimation.h"
#include "../animation/waveanimation.h"
#include "animationcuehandler.h"

namespace PixelMaestro {

	// Animation-specific Cues
	uint8_t* AnimationCueHandler::set_fire_options(uint8_t section_num, uint8_t layer_num, uint8_t multiplier) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetFireOptions,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = multiplier;

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_lightning_options(uint8_t section_num, uint8_t layer_num, uint8_t num_bolts, int8_t drift, uint8_t fork_chance) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetLightningOptions,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = num_bolts;
		controller_.get_buffer()[++index] = (uint8_t)drift;
		controller_.get_buffer()[++index] = fork_chance;

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_plasma_options(uint8_t section_num, uint8_t layer_num, float size, float resolution) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetPlasmaOptions,
			section_num,
			layer_num
		);

		add_float_to_cue(index, size);
		add_float_to_cue(index, resolution);

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_radial_options(uint8_t section_num, uint8_t layer_num, uint8_t resolution) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetRadialOptions,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = resolution;

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_sparkle_options(uint8_t section_num, uint8_t layer_num, uint8_t threshold) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetSparkleOptions,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = threshold;

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_wave_options(uint8_t section_num, uint8_t layer_num, int8_t skew) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetWaveOptions,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = (uint8_t)skew;

		return controller_.assemble(++index);
	}

	// General-purpose Cues
	uint8_t* AnimationCueHandler::set_center(uint8_t section_num, uint8_t layer_num, uint16_t x, uint16_t y) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetCenter,
			section_num,
			layer_num
		);

		add_uint16_to_cue(index, x);
		add_uint16_to_cue(index, y);

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_cycle_index(uint8_t section_num, uint8_t layer_num, uint8_t cycle_index) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetCycleIndex,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = cycle_index;

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_fade(uint8_t section_num, uint8_t layer_num, bool fade) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetFade,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = (uint8_t)fade;

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_orientation(uint8_t section_num, uint8_t layer_num, Animation::Orientation orientation) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetOrientation,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = (uint8_t)orientation;

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_palette(uint8_t section_num, uint8_t layer_num, const Palette& palette) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetPalette,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = palette.get_num_colors();

		uint16_t palette_size= serialize_palette(&controller_.get_buffer()[++index], palette);

		return controller_.assemble(index + palette_size);
	}

	uint8_t* AnimationCueHandler::set_reverse(uint8_t section_num, uint8_t layer_num, bool reverse) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetReverse,
			section_num,
			layer_num
		);
		controller_.get_buffer()[++index] = (uint8_t)reverse;

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::set_timer(uint8_t section_num, uint8_t layer_num, uint16_t interval, uint16_t delay) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::SetTimer,
			section_num,
			layer_num
		);

		add_uint16_to_cue(index, interval);
		add_uint16_to_cue(index, delay);

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::start(uint8_t section_num, uint8_t layer_num) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::Start,
			section_num,
			layer_num
		);

		return controller_.assemble(++index);
	}

	uint8_t* AnimationCueHandler::stop(uint8_t section_num, uint8_t layer_num) {
		uint32_t index = start_cue(
			(uint8_t)CueController::Handler::AnimationCueHandler,
			(uint8_t)Action::Stop,
			section_num,
			layer_num
		);

		return controller_.assemble(++index);
	}

	void AnimationCueHandler::run(uint8_t *cue) {

		Section* section = get_section(cue[(uint8_t)Byte::SectionByte], cue[(uint8_t)Byte::LayerByte]);
		if (section == nullptr) return;

		Animation* animation = section->get_animation();
		if (animation == nullptr) return;

		switch((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::SetCenter:
				animation->set_center(IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]),
						IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 2]));
				break;
			case Action::SetCycleIndex:
				animation->set_cycle_index(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetFade:
				animation->set_fade(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetFireOptions:
				{
					FireAnimation* fa = static_cast<FireAnimation*>(animation);
					fa->set_multiplier(cue[(uint8_t)Byte::OptionsByte]);
				}
				break;
			case Action::SetLightningOptions:
				{
					LightningAnimation* la = static_cast<LightningAnimation*>(animation);
					la->set_bolt_count(cue[(uint8_t)Byte::OptionsByte]);
					la->set_drift((int8_t)cue[(uint8_t)Byte::OptionsByte + 1]);
					la->set_fork_chance(cue[(uint8_t)Byte::OptionsByte + 2]);
				}
				break;
			case Action::SetOrientation:
				animation->set_orientation((Animation::Orientation)cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetPalette:
				{
					uint8_t num_colors = cue[(uint8_t)Byte::OptionsByte];

					// Delete the old palette after setting the new one.
					Palette* old_palette = animation->get_palette();
					animation->set_palette(*deserialize_palette(&cue[(uint8_t)Byte::OptionsByte + 1], num_colors));
					delete old_palette;
				}
				break;
			case Action::SetPlasmaOptions:
				{
					PlasmaAnimation* pa = static_cast<PlasmaAnimation*>(animation);
					pa->set_size(FloatByteConvert::byte_to_float(&cue[(uint8_t)Byte::OptionsByte]));
					pa->set_resolution(FloatByteConvert::byte_to_float(&cue[(uint8_t)Byte::OptionsByte + 4]));
				}
				break;
			case Action::SetRadialOptions:
				static_cast<RadialAnimation*>(animation)->set_resolution(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetReverse:
				animation->set_reverse(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetSparkleOptions:
				static_cast<SparkleAnimation*>(animation)->set_threshold(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetTimer:
				animation->set_timer(
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_uint16(&cue[(uint8_t)Byte::OptionsByte + 2]));
				break;
			case Action::SetWaveOptions:
				static_cast<WaveAnimation*>(animation)->set_skew((int8_t)cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::Start:
				if (animation->get_timer()) {
					animation->get_timer()->start();
				}
				break;
			case Action::Stop:
				if (animation->get_timer()) {
					animation->get_timer()->stop();
				}
				break;
		}
	}
}
