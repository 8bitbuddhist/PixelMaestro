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

#include "animationcue.h"
#include "cuecontroller.h"
#include "sectioncue.h"

namespace PixelMaestro {

	Animation* AnimationCue::initialize_animation(unsigned char* cue) {
		int num_colors = cue[SectionCue::Bit::OptionsBit + 2];
		int current_color_index = SectionCue::Bit::OptionsBit + 3;
		Colors::RGB colors[num_colors];
		for (unsigned char i = 0; i < num_colors; i++) {
			colors[i].r = cue[current_color_index];
			current_color_index++;
			colors[i].g = cue[current_color_index];
			current_color_index++;
			colors[i].b = cue[current_color_index];
			current_color_index++;
		}

		switch((Animation::Type)cue[SectionCue::Bit::OptionsBit]) {
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
	void AnimationCue::set_lightning_options(unsigned char section_num, unsigned char num_bolts, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance) {
		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetLightningOptions;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = num_bolts;
		buffer_[Bit::OptionsBit + 1] = down_threshold;
		buffer_[Bit::OptionsBit + 2] = up_threshold;
		buffer_[Bit::OptionsBit + 3] = fork_chance;

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 4));
	}

	void AnimationCue::set_plasma_options(unsigned char section_num, float size, float resolution) {
		FloatByteConvert size_byte(size);
		FloatByteConvert resolution_byte(resolution);

		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetPlasmaOptions;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = size_byte.converted.byte[0];
		buffer_[Bit::OptionsBit + 1] = size_byte.converted.byte[1];
		buffer_[Bit::OptionsBit + 2] = size_byte.converted.byte[2];
		buffer_[Bit::OptionsBit + 3] = size_byte.converted.byte[3];
		buffer_[Bit::OptionsBit + 4] = resolution_byte.converted.byte[0];
		buffer_[Bit::OptionsBit + 5] = resolution_byte.converted.byte[1];
		buffer_[Bit::OptionsBit + 6] = resolution_byte.converted.byte[2];
		buffer_[Bit::OptionsBit + 7] = resolution_byte.converted.byte[3];

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 7));
	}

	void AnimationCue::set_sparkle_options(unsigned char section_num, unsigned char threshold) {
		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetSparkleOptions;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = threshold;

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 1));
	}

	// General-purpose Cues

	void AnimationCue::set_colors(unsigned char section_num, Colors::RGB *colors, unsigned char num_colors) {
		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetColors;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = num_colors;

		unsigned char colors_index = Bit::OptionsBit + 1;
		for (unsigned char i = 0; i < num_colors; i++) {
			buffer_[colors_index] = colors[i].r;
			colors_index++;
			buffer_[colors_index] = colors[i].g;
			colors_index++;
			buffer_[colors_index] = colors[i].b;
			colors_index++;
		}

		CueController::assemble(buffer_, colors_index);
	}

	void AnimationCue::set_cycle_index(unsigned char section_num, unsigned char cycle_index) {
		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetCycleIndex;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = cycle_index;

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 1));
	}

	void AnimationCue::set_fade(unsigned char section_num, bool fade) {
		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetFade;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = (unsigned char)fade;

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 1));
	}

	void AnimationCue::set_orientation(unsigned char section_num, Animation::Orientation orientation) {
		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetOrientation;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = (unsigned char)orientation;

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 1));
	}

	void AnimationCue::set_reverse(unsigned char section_num, bool reverse) {
		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetReverse;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = (unsigned char)reverse;

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 1));
	}

	void AnimationCue::set_speed(unsigned char section_num, unsigned short speed, unsigned short pause) {
		IntByteConvert speed_byte(speed);
		IntByteConvert pause_byte(pause);

		buffer_[Bit::ComponentBit] = (unsigned char)CueController::Component::AnimationComponent;
		buffer_[Bit::ActionBit] = (unsigned char)Action::SetSpeed;
		buffer_[Bit::SectionBit] = section_num;
		buffer_[Bit::OptionsBit] = speed_byte.converted_0;
		buffer_[Bit::OptionsBit + 1] = speed_byte.converted_1;
		buffer_[Bit::OptionsBit + 2] = pause_byte.converted_0;
		buffer_[Bit::OptionsBit + 3] = pause_byte.converted_1;

		CueController::assemble(buffer_, (unsigned char)(Bit::OptionsBit + 4));
	}

	void AnimationCue::run(unsigned char *cue) {
		Animation* animation = maestro_->get_section(cue[Bit::SectionBit])->get_animation();
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
