#include "../animation/fireanimation.h"
#include "../animation/lightninganimation.h"
#include "../animation/plasmaanimation.h"
#include "../animation/radialanimation.h"
#include "../animation/sparkleanimation.h"
#include "animationcuehandler.h"

namespace PixelMaestro {

	// Animation-specific Cues
	uint8_t* AnimationCueHandler::set_fire_options(uint8_t section_num, uint8_t layer_num, uint8_t multiplier) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetFireOptions;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = multiplier;

		return controller_->assemble((Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_lightning_options(uint8_t section_num, uint8_t layer_num, uint8_t num_bolts, uint8_t down_threshold, uint8_t up_threshold, uint8_t fork_chance) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetLightningOptions;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = num_bolts;
		controller_->get_buffer()[Byte::OptionsByte + 1] = down_threshold;
		controller_->get_buffer()[Byte::OptionsByte + 2] = up_threshold;
		controller_->get_buffer()[Byte::OptionsByte + 3] = fork_chance;

		return controller_->assemble((Byte::OptionsByte + 4));
	}

	uint8_t* AnimationCueHandler::set_plasma_options(uint8_t section_num, uint8_t layer_num, float size, float resolution) {
		FloatByteConvert size_byte(size);
		FloatByteConvert resolution_byte(resolution);

		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetPlasmaOptions;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = size_byte.converted.byte[0];
		controller_->get_buffer()[Byte::OptionsByte + 1] = size_byte.converted.byte[1];
		controller_->get_buffer()[Byte::OptionsByte + 2] = size_byte.converted.byte[2];
		controller_->get_buffer()[Byte::OptionsByte + 3] = size_byte.converted.byte[3];
		controller_->get_buffer()[Byte::OptionsByte + 4] = resolution_byte.converted.byte[0];
		controller_->get_buffer()[Byte::OptionsByte + 5] = resolution_byte.converted.byte[1];
		controller_->get_buffer()[Byte::OptionsByte + 6] = resolution_byte.converted.byte[2];
		controller_->get_buffer()[Byte::OptionsByte + 7] = resolution_byte.converted.byte[3];

		return controller_->assemble((Byte::OptionsByte + 7));
	}

	uint8_t* AnimationCueHandler::set_radial_options(uint8_t section_num, uint8_t layer_num, uint8_t resolution) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetRadialOptions;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = resolution;

		return controller_->assemble((Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_sparkle_options(uint8_t section_num, uint8_t layer_num, uint8_t threshold) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetSparkleOptions;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = threshold;

		return controller_->assemble((Byte::OptionsByte + 1));
	}

	// General-purpose Cues
	uint8_t* AnimationCueHandler::set_colors(uint8_t section_num, uint8_t layer_num, Colors::RGB *colors, uint8_t num_colors, bool delete_old_colors) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetColors;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = num_colors;

		uint16_t colors_index = Byte::OptionsByte + 1;
		for (uint8_t i = 0; i < num_colors; i++) {
			controller_->get_buffer()[colors_index] = colors[i].r;
			colors_index++;
			controller_->get_buffer()[colors_index] = colors[i].g;
			colors_index++;
			controller_->get_buffer()[colors_index] = colors[i].b;
			colors_index++;
		}

		controller_->get_buffer()[colors_index] = delete_old_colors;

		return controller_->assemble(colors_index);
	}

	uint8_t* AnimationCueHandler::set_cycle_index(uint8_t section_num, uint8_t layer_num, uint8_t cycle_index) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetCycleIndex;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = cycle_index;

		return controller_->assemble((Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_fade(uint8_t section_num, uint8_t layer_num, bool fade) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetFade;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = (uint8_t)fade;

		return controller_->assemble((Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_orientation(uint8_t section_num, uint8_t layer_num, Animation::Orientation orientation) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetOrientation;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = (uint8_t)orientation;

		return controller_->assemble((Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_reverse(uint8_t section_num, uint8_t layer_num, bool reverse) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetReverse;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = (uint8_t)reverse;

		return controller_->assemble((Byte::OptionsByte + 1));
	}

	uint8_t* AnimationCueHandler::set_timing(uint8_t section_num, uint8_t layer_num, uint16_t interval, uint16_t pause) {
		IntByteConvert interval_byte(interval);
		IntByteConvert pause_byte(pause);

		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::SetTiming;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;
		controller_->get_buffer()[Byte::OptionsByte] = interval_byte.converted_0;
		controller_->get_buffer()[Byte::OptionsByte + 1] = interval_byte.converted_1;
		controller_->get_buffer()[Byte::OptionsByte + 2] = pause_byte.converted_0;
		controller_->get_buffer()[Byte::OptionsByte + 3] = pause_byte.converted_1;

		return controller_->assemble((Byte::OptionsByte + 4));
	}

	uint8_t* AnimationCueHandler::start(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::Start;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;

		return controller_->assemble(Byte::OptionsByte);
	}

	uint8_t* AnimationCueHandler::stop(uint8_t section_num, uint8_t layer_num) {
		controller_->get_buffer()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_buffer()[Byte::ActionByte] = (uint8_t)Action::Stop;
		controller_->get_buffer()[Byte::SectionByte] = section_num;
		controller_->get_buffer()[Byte::LayerByte] = layer_num;

		return controller_->assemble(Byte::OptionsByte);
	}

	void AnimationCueHandler::run(uint8_t *cue) {

		Section* section = get_section(cue[Byte::SectionByte], cue[Byte::LayerByte]);
		if (section == nullptr) return;

		Animation* animation = section->get_animation();
		if (animation == nullptr) return;

		switch((Action)cue[Byte::ActionByte]) {
			case Action::SetColors:
				{
					uint8_t num_colors = cue[Byte::OptionsByte];
					uint16_t current_color_index = 1;
					Colors::RGB* colors = new Colors::RGB[num_colors];
					for (uint8_t i = 0; i < num_colors; i++) {
						colors[i].r = cue[Byte::OptionsByte + current_color_index];
						current_color_index++;
						colors[i].g = cue[Byte::OptionsByte + current_color_index];
						current_color_index++;
						colors[i].b = cue[Byte::OptionsByte + current_color_index];
						current_color_index++;
					}

					/*
					 * Delete the old palette after setting the new one.
					 * We force an update so that the Animation no longer references the old palette.
					 * WARNING: This throws off timing, but only for a single frame. Shouldn't be noticeable except for slow animations or when fading is disabled.
					 */
					Colors::RGB* old_palette = animation->get_colors();

					animation->set_colors(colors, num_colors);
					animation->update(0);

					delete [] old_palette;
				}
				break;
			case Action::SetCycleIndex:
				animation->set_cycle_index(cue[Byte::OptionsByte]);
				break;
			case Action::SetFade:
				animation->set_fade(cue[Byte::OptionsByte]);
				break;
			case Action::SetFireOptions:
				{
					FireAnimation* fa = static_cast<FireAnimation*>(animation);
					fa->set_multiplier(cue[Byte::OptionsByte]);
				}
				break;
			case Action::SetLightningOptions:
				{
					LightningAnimation* la = static_cast<LightningAnimation*>(animation);
					la->set_bolt_count(cue[Byte::OptionsByte]);
					la->set_thresholds(cue[Byte::OptionsByte + 1], cue[Byte::OptionsByte + 2]);
					la->set_fork_chance(cue[Byte::OptionsByte + 3]);
				}
				break;
			case Action::SetOrientation:
				animation->set_orientation((Animation::Orientation)cue[Byte::OptionsByte]);
				break;
			case Action::SetPlasmaOptions:
				{
					PlasmaAnimation* pa = static_cast<PlasmaAnimation*>(animation);
					pa->set_size(FloatByteConvert::byte_to_float(&cue[Byte::OptionsByte]));
					pa->set_resolution(FloatByteConvert::byte_to_float(&cue[Byte::OptionsByte + 4]));
				}
				break;
			case Action::SetRadialOptions:
				static_cast<RadialAnimation*>(animation)->set_resolution(cue[Byte::OptionsByte]);
				break;
			case Action::SetReverse:
				animation->set_reverse(cue[Byte::OptionsByte]);
				break;
			case Action::SetSparkleOptions:
				static_cast<SparkleAnimation*>(animation)->set_threshold(cue[Byte::OptionsByte]);
				break;
			case Action::SetTiming:
				animation->set_timing(
					IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]),
					IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]));
				break;
			case Action::Start:
				if (animation->get_timing()) {
					animation->get_timing()->start();
				}
				break;
			case Action::Stop:
				if (animation->get_timing()) {
					animation->get_timing()->stop();
				}
				break;
		}
	}

	AnimationCueHandler::~AnimationCueHandler() { }
}
