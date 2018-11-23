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
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetFireOptions;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = multiplier;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_lightning_options(uint8_t section_num, uint8_t layer_num, uint8_t num_bolts, int8_t drift, uint8_t fork_chance) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetLightningOptions;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = num_bolts;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = (uint8_t)drift;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = fork_chance;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 3));
	}

	uint8_t* AnimationCueHandler::set_plasma_options(uint8_t section_num, uint8_t layer_num, float size, float resolution) {
		FloatByteConvert size_byte(size);
		FloatByteConvert resolution_byte(resolution);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetPlasmaOptions;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = size_byte.converted.byte[0];
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = size_byte.converted.byte[1];
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = size_byte.converted.byte[2];
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = size_byte.converted.byte[3];
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 4] = resolution_byte.converted.byte[0];
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 5] = resolution_byte.converted.byte[1];
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 6] = resolution_byte.converted.byte[2];
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 7] = resolution_byte.converted.byte[3];

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 7));
	}

	uint8_t* AnimationCueHandler::set_radial_options(uint8_t section_num, uint8_t layer_num, uint8_t resolution) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetRadialOptions;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = resolution;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_sparkle_options(uint8_t section_num, uint8_t layer_num, uint8_t threshold) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetSparkleOptions;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = threshold;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_wave_options(uint8_t section_num, uint8_t layer_num, bool mirror, int8_t skew) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetWaveOptions;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)mirror;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = (uint8_t)skew;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 2));
	}

	// General-purpose Cues
	uint8_t* AnimationCueHandler::set_cycle_index(uint8_t section_num, uint8_t layer_num, uint8_t cycle_index) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetCycleIndex;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = cycle_index;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_fade(uint8_t section_num, uint8_t layer_num, bool fade) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetFade;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)fade;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_orientation(uint8_t section_num, uint8_t layer_num, Animation::Orientation orientation) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetOrientation;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)orientation;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_palette(uint8_t section_num, uint8_t layer_num, Palette* palette) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetPalette;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = palette->get_num_colors();

		uint16_t final_index = serialize_palette(&controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1], palette);

		return controller_->assemble(final_index + (uint8_t)Byte::OptionsByte + 1);
	}

	uint8_t* AnimationCueHandler::set_reverse(uint8_t section_num, uint8_t layer_num, bool reverse) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetReverse;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = (uint8_t)reverse;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_timer(uint8_t section_num, uint8_t layer_num, uint16_t interval, uint16_t delay) {
		IntByteConvert interval_byte(interval);
		IntByteConvert delay_byte(delay);

		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::SetTimer;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte] = interval_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 1] = interval_byte.converted_1;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 2] = delay_byte.converted_0;
		controller_->get_buffer()[(uint8_t)Byte::OptionsByte + 3] = delay_byte.converted_1;

		return controller_->assemble(((uint8_t)Byte::OptionsByte + 4));
	}

	uint8_t* AnimationCueHandler::start(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::Start;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	uint8_t* AnimationCueHandler::stop(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[(uint8_t)Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationCueHandler;
		controller_->get_buffer()[(uint8_t)Byte::ActionByte] = (uint8_t)Action::Stop;
		controller_->get_buffer()[(uint8_t)Byte::SectionByte] = section_num;
		controller_->get_buffer()[(uint8_t)Byte::LayerByte] = layer_num;

		return controller_->assemble((uint8_t)Byte::OptionsByte);
	}

	void AnimationCueHandler::run(uint8_t *cue) {

		Section* section = get_section(cue[(uint8_t)Byte::SectionByte], cue[(uint8_t)Byte::LayerByte]);
		if (section == nullptr) return;

		Animation* animation = section->get_animation();
		if (animation == nullptr) return;

		switch((Action)cue[(uint8_t)Byte::ActionByte]) {
			case Action::SetCycleIndex:
				animation->set_cycle_index(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetFade:
				animation->set_fade(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetFireOptions:
				{
					FireAnimation* fa = dynamic_cast<FireAnimation*>(animation);
					fa->set_multiplier(cue[(uint8_t)Byte::OptionsByte]);
				}
				break;
			case Action::SetLightningOptions:
				{
					LightningAnimation* la = dynamic_cast<LightningAnimation*>(animation);
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

					/*
					 * Delete the old palette after setting the new one.
					 * We force an update so that the Animation no longer references the old palette.
					 * This throws off the timer, but only for a single frame.
					 */
					Palette* old_palette = animation->get_palette();
					animation->set_palette(deserialize_palette(&cue[(uint8_t)Byte::OptionsByte + 1], num_colors));
					animation->update(0);
					delete old_palette;
				}
				break;
			case Action::SetPlasmaOptions:
				{
					PlasmaAnimation* pa = dynamic_cast<PlasmaAnimation*>(animation);
					pa->set_size(FloatByteConvert::byte_to_float(&cue[(uint8_t)Byte::OptionsByte]));
					pa->set_resolution(FloatByteConvert::byte_to_float(&cue[(uint8_t)Byte::OptionsByte + 4]));
				}
				break;
			case Action::SetRadialOptions:
				dynamic_cast<RadialAnimation*>(animation)->set_resolution(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetReverse:
				animation->set_reverse(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetSparkleOptions:
				dynamic_cast<SparkleAnimation*>(animation)->set_threshold(cue[(uint8_t)Byte::OptionsByte]);
				break;
			case Action::SetTimer:
				animation->set_timer(
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[(uint8_t)Byte::OptionsByte + 2]));
				break;
			case Action::SetWaveOptions:
				{
					WaveAnimation* wa = dynamic_cast<WaveAnimation*>(animation);
					wa->set_mirror((bool)cue[(uint8_t)Byte::OptionsByte]);
					wa->set_skew((int8_t)cue[(uint8_t)Byte::OptionsByte + 1]);
				}
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
