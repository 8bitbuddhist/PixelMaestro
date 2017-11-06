#include "../animation/lightninganimation.h"
#include "../animation/plasmaanimation.h"
#include "../animation/radialanimation.h"
#include "../animation/sparkleanimation.h"
#include "animationcuehandler.h"

namespace PixelMaestro {

	// Animation-specific Cues
	void AnimationCueHandler::set_lightning_options(uint8_t section_num, uint8_t overlay_num, uint8_t num_bolts, uint8_t down_threshold, uint8_t up_threshold, uint8_t fork_chance) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetLightningOptions;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = num_bolts;
		controller_->get_cue()[Byte::OptionsByte + 1] = down_threshold;
		controller_->get_cue()[Byte::OptionsByte + 2] = up_threshold;
		controller_->get_cue()[Byte::OptionsByte + 3] = fork_chance;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 4));
	}

	void AnimationCueHandler::set_plasma_options(uint8_t section_num, uint8_t overlay_num, float size, float resolution) {
		FloatByteConvert size_byte(size);
		FloatByteConvert resolution_byte(resolution);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetPlasmaOptions;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = size_byte.converted.byte[0];
		controller_->get_cue()[Byte::OptionsByte + 1] = size_byte.converted.byte[1];
		controller_->get_cue()[Byte::OptionsByte + 2] = size_byte.converted.byte[2];
		controller_->get_cue()[Byte::OptionsByte + 3] = size_byte.converted.byte[3];
		controller_->get_cue()[Byte::OptionsByte + 4] = resolution_byte.converted.byte[0];
		controller_->get_cue()[Byte::OptionsByte + 5] = resolution_byte.converted.byte[1];
		controller_->get_cue()[Byte::OptionsByte + 6] = resolution_byte.converted.byte[2];
		controller_->get_cue()[Byte::OptionsByte + 7] = resolution_byte.converted.byte[3];

		controller_->assemble((uint8_t)(Byte::OptionsByte + 7));
	}

	void AnimationCueHandler::set_radial_options(uint8_t section_num, uint8_t overlay_num, uint8_t resolution) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetRadialOptions;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = resolution;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 1));
	}

	void AnimationCueHandler::set_sparkle_options(uint8_t section_num, uint8_t overlay_num, uint8_t threshold) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetSparkleOptions;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = threshold;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 1));
	}

	// General-purpose Cues

	void AnimationCueHandler::set_colors(uint8_t section_num, uint8_t overlay_num, Colors::RGB *colors, uint8_t num_colors, bool delete_old_colors) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetColors;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = num_colors;

		uint8_t colors_index = Byte::OptionsByte + 1;
		for (uint8_t i = 0; i < num_colors; i++) {
			controller_->get_cue()[colors_index] = colors[i].r;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].g;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].b;
			colors_index++;
		}

		controller_->get_cue()[colors_index] = delete_old_colors;

		controller_->assemble(colors_index);
	}

	void AnimationCueHandler::set_cycle_index(uint8_t section_num, uint8_t overlay_num, uint8_t cycle_index) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetCycleIndex;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = cycle_index;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 1));
	}

	void AnimationCueHandler::set_fade(uint8_t section_num, uint8_t overlay_num, bool fade) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetFade;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = (uint8_t)fade;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 1));
	}

	void AnimationCueHandler::set_orientation(uint8_t section_num, uint8_t overlay_num, Animation::Orientation orientation) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetOrientation;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = (uint8_t)orientation;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 1));
	}

	void AnimationCueHandler::set_reverse(uint8_t section_num, uint8_t overlay_num, bool reverse) {
		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetReverse;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = (uint8_t)reverse;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 1));
	}

	void AnimationCueHandler::set_speed(uint8_t section_num, uint8_t overlay_num, uint16_t speed, uint16_t pause) {
		IntByteConvert speed_byte(speed);
		IntByteConvert pause_byte(pause);

		controller_->get_cue()[Byte::HandlerByte] = (uint8_t)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Byte::ActionByte] = (uint8_t)Action::SetSpeed;
		controller_->get_cue()[Byte::SectionByte] = section_num;
		controller_->get_cue()[Byte::OverlayByte] = overlay_num;
		controller_->get_cue()[Byte::OptionsByte] = speed_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 1] = speed_byte.converted_1;
		controller_->get_cue()[Byte::OptionsByte + 2] = pause_byte.converted_0;
		controller_->get_cue()[Byte::OptionsByte + 3] = pause_byte.converted_1;

		controller_->assemble((uint8_t)(Byte::OptionsByte + 4));
	}

	void AnimationCueHandler::run(uint8_t *cue) {

		Section* section = get_section(cue[Byte::SectionByte], cue[Byte::OverlayByte]);
		if (section == nullptr) return;

		Animation* animation = section->get_animation();
		if (animation == nullptr) return;

		switch((Action)cue[Byte::ActionByte]) {
			case Action::SetColors:
				{
					uint8_t num_colors = cue[Byte::OptionsByte];
					uint8_t current_color_index = 1;
					Colors::RGB* colors = new Colors::RGB[num_colors];
					for (uint8_t i = 0; i < num_colors; i++) {
						colors[i].r = cue[Byte::OptionsByte + current_color_index];
						current_color_index++;
						colors[i].g = cue[Byte::OptionsByte + current_color_index];
						current_color_index++;
						colors[i].b = cue[Byte::OptionsByte + current_color_index];
						current_color_index++;
					}

					if (cue[current_color_index] && animation->get_colors() != nullptr) {
						delete[] animation->get_colors();
					}

					animation->set_colors(colors, num_colors);
				}
				break;
			case Action::SetCycleIndex:
				animation->set_cycle_index(cue[Byte::OptionsByte]);
				break;
			case Action::SetFade:
				animation->set_fade(cue[Byte::OptionsByte]);
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
					float size = FloatByteConvert::byte_to_float(&cue[Byte::OptionsByte]);
					float resolution = FloatByteConvert::byte_to_float(&cue[Byte::OptionsByte + 4]);
					PlasmaAnimation* pa = static_cast<PlasmaAnimation*>(animation);
					pa->set_size(size);
					pa->set_resolution(resolution);
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
			case Action::SetSpeed:
				{
					uint16_t speed = IntByteConvert::byte_to_int(&cue[Byte::OptionsByte]);
					uint16_t pause = IntByteConvert::byte_to_int(&cue[Byte::OptionsByte + 2]);
					animation->set_speed(speed, pause);
				}
				break;
		}
	}

	AnimationCueHandler::~AnimationCueHandler() { }
}
