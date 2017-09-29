#include "../animation/blinkanimation.h"
#include "../animation/cycleanimation.h"
#include "../animation/lightninganimation.h"
#include "../animation/mandelbrotanimation.h"
#include "../animation/mergeanimation.h"
#include "../animation/plasmaanimation.h"
#include "../animation/radialanimation.h"
#include "../animation/randomanimation.h"
#include "../animation/solidanimation.h"
#include "../animation/sparkleanimation.h"
#include "../animation/waveanimation.h"

#include "animationcuehandler.h"
#include "sectioncuehandler.h"

namespace PixelMaestro {

	Animation* AnimationCueHandler::initialize_animation(unsigned char* cue) {
		int num_colors = cue[SectionCueHandler::Bit::OptionsBit + 2];
		int current_color_index = SectionCueHandler::Bit::OptionsBit + 3;
		Colors::RGB colors[num_colors];
		for (unsigned char i = 0; i < num_colors; i++) {
			colors[i].r = cue[current_color_index];
			current_color_index++;
			colors[i].g = cue[current_color_index];
			current_color_index++;
			colors[i].b = cue[current_color_index];
			current_color_index++;
		}

		switch((Animation::Type)cue[SectionCueHandler::Bit::OptionsBit]) {
			case Animation::Type::Blink:
				return new BlinkAnimation(colors, num_colors);
				break;
			case Animation::Type::Cycle:
				return new CycleAnimation(colors, num_colors);
				break;
			case Animation::Type::Lightning:
				return new LightningAnimation(colors, num_colors);
				break;
			case Animation::Type::Mandelbrot:
				return new MandelbrotAnimation(colors, num_colors);
				break;
			case Animation::Type::Merge:
				return new MergeAnimation(colors, num_colors);
				break;
			case Animation::Type::Plasma:
				return new PlasmaAnimation(colors, num_colors);
				break;
			case Animation::Type::Radial:
				return new RadialAnimation(colors, num_colors);
				break;
			case Animation::Type::Random:
				return new RandomAnimation(colors, num_colors);
				break;
			case Animation::Type::Solid:
				return new SolidAnimation(colors, num_colors);
				break;
			case Animation::Type::Sparkle:
				return new SparkleAnimation(colors, num_colors);
				break;
			case Animation::Type::Wave:
				return new WaveAnimation(colors, num_colors);
				break;
		}

		return nullptr;
	}

	// Animation-specific Cues
	void AnimationCueHandler::set_lightning_options(unsigned char section_num, unsigned char num_bolts, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetLightningOptions;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = num_bolts;
		controller_->get_cue()[Bit::OptionsBit + 1] = down_threshold;
		controller_->get_cue()[Bit::OptionsBit + 2] = up_threshold;
		controller_->get_cue()[Bit::OptionsBit + 3] = fork_chance;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 4));
	}

	void AnimationCueHandler::set_plasma_options(unsigned char section_num, float size, float resolution) {
		FloatByteConvert size_byte(size);
		FloatByteConvert resolution_byte(resolution);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetPlasmaOptions;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = size_byte.converted.byte[0];
		controller_->get_cue()[Bit::OptionsBit + 1] = size_byte.converted.byte[1];
		controller_->get_cue()[Bit::OptionsBit + 2] = size_byte.converted.byte[2];
		controller_->get_cue()[Bit::OptionsBit + 3] = size_byte.converted.byte[3];
		controller_->get_cue()[Bit::OptionsBit + 4] = resolution_byte.converted.byte[0];
		controller_->get_cue()[Bit::OptionsBit + 5] = resolution_byte.converted.byte[1];
		controller_->get_cue()[Bit::OptionsBit + 6] = resolution_byte.converted.byte[2];
		controller_->get_cue()[Bit::OptionsBit + 7] = resolution_byte.converted.byte[3];

		controller_->assemble((unsigned char)(Bit::OptionsBit + 7));
	}

	void AnimationCueHandler::set_sparkle_options(unsigned char section_num, unsigned char threshold) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetSparkleOptions;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = threshold;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 1));
	}

	// General-purpose Cues

	void AnimationCueHandler::set_colors(unsigned char section_num, Colors::RGB *colors, unsigned char num_colors) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetColors;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = num_colors;

		unsigned char colors_index = Bit::OptionsBit + 1;
		for (unsigned char i = 0; i < num_colors; i++) {
			controller_->get_cue()[colors_index] = colors[i].r;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].g;
			colors_index++;
			controller_->get_cue()[colors_index] = colors[i].b;
			colors_index++;
		}

		controller_->assemble(colors_index);
	}

	void AnimationCueHandler::set_cycle_index(unsigned char section_num, unsigned char cycle_index) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetCycleIndex;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = cycle_index;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 1));
	}

	void AnimationCueHandler::set_fade(unsigned char section_num, bool fade) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetFade;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = (unsigned char)fade;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 1));
	}

	void AnimationCueHandler::set_orientation(unsigned char section_num, Animation::Orientation orientation) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetOrientation;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = (unsigned char)orientation;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 1));
	}

	void AnimationCueHandler::set_reverse(unsigned char section_num, bool reverse) {
		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetReverse;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = (unsigned char)reverse;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 1));
	}

	void AnimationCueHandler::set_speed(unsigned char section_num, unsigned short speed, unsigned short pause) {
		IntByteConvert speed_byte(speed);
		IntByteConvert pause_byte(pause);

		controller_->get_cue()[Bit::HandlerBit] = (unsigned char)CueController::Handler::AnimationHandler;
		controller_->get_cue()[Bit::ActionBit] = (unsigned char)Action::SetSpeed;
		controller_->get_cue()[Bit::SectionBit] = section_num;
		controller_->get_cue()[Bit::OptionsBit] = speed_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 1] = speed_byte.converted_1;
		controller_->get_cue()[Bit::OptionsBit + 2] = pause_byte.converted_0;
		controller_->get_cue()[Bit::OptionsBit + 3] = pause_byte.converted_1;

		controller_->assemble((unsigned char)(Bit::OptionsBit + 4));
	}

	void AnimationCueHandler::run(unsigned char *cue) {
		Animation* animation = controller_->get_maestro()->get_section(cue[Bit::SectionBit])->get_animation();
		switch((Action)cue[Bit::ActionBit]) {
			case Action::SetColors:
				{
					unsigned char num_colors = cue[Bit::OptionsBit];
					unsigned char current_color_index = 1;
					Colors::RGB colors[num_colors];
					for (unsigned char i = 0; i < num_colors; i++) {
						colors[i].r = cue[Bit::OptionsBit + current_color_index];
						current_color_index++;
						colors[i].g = cue[Bit::OptionsBit + current_color_index];
						current_color_index++;
						colors[i].b = cue[Bit::OptionsBit + current_color_index];
						current_color_index++;
					}
					animation->set_colors(colors, num_colors);
				}
				break;
			case Action::SetCycleIndex:
				animation->set_cycle_index(cue[Bit::OptionsBit]);
				break;
			case Action::SetFade:
				animation->set_fade(cue[Bit::OptionsBit]);
				break;
			case Action::SetLightningOptions:
				{
					LightningAnimation* la = static_cast<LightningAnimation*>(animation);
					la->set_bolt_count(cue[Bit::OptionsBit]);
					la->set_thresholds(cue[Bit::OptionsBit + 1], cue[Bit::OptionsBit + 2]);
					la->set_fork_chance(cue[Bit::OptionsBit + 3]);
				}
				break;
			case Action::SetPlasmaOptions:
				{
					float size = FloatByteConvert::byte_to_float(&cue[Bit::OptionsBit]);
					float resolution = FloatByteConvert::byte_to_float(&cue[Bit::OptionsBit + 4]);
					PlasmaAnimation* pa = static_cast<PlasmaAnimation*>(animation);
					pa->set_size(size);
					pa->set_resolution(resolution);
				}
				break;
			case Action::SetOrientation:
				animation->set_orientation((Animation::Orientation)cue[Bit::OptionsBit]);
				break;
			case Action::SetReverse:
				animation->set_reverse(cue[Bit::OptionsBit]);
				break;
			case Action::SetSparkleOptions:
				static_cast<SparkleAnimation*>(animation)->set_threshold(cue[Bit::OptionsBit]);
				break;
			case Action::SetSpeed:
				{
					unsigned short speed = IntByteConvert::byte_to_int(&cue[Bit::OptionsBit]);
					unsigned short pause = IntByteConvert::byte_to_int(&cue[Bit::OptionsBit + 2]);
					animation->set_speed(speed, pause);
				}
				break;
		}
	}
}
