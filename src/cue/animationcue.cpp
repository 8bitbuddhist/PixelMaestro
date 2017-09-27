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
#include "cue.h"

namespace PixelMaestro {
	Animation* AnimationCue::initialize_animation(unsigned char* cue) {
		int num_colors = cue[Cue::payload_index_ + 3];
		int current_color_index = 5;
		Colors::RGB* colors = new Colors::RGB[num_colors];
		for (unsigned char i = 0; i < num_colors; i++) {
			colors[i].r = cue[Cue::payload_index_ + current_color_index];
			current_color_index++;
			colors[i].g = cue[Cue::payload_index_ + current_color_index];
			current_color_index++;
			colors[i].b = cue[Cue::payload_index_ + current_color_index];
			current_color_index++;
		}

		switch((Animation::Type)cue[Cue::payload_index_ + 3]) {
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
	void AnimationCue::set_lightning_options(unsigned char* buffer, unsigned char section_num, unsigned char num_bolts, unsigned char down_threshold, unsigned char up_threshold, unsigned char fork_chance) {
		unsigned char payload[] = {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetLightningOptions,
			section_num,
			num_bolts,
			down_threshold,
			up_threshold,
			fork_chance
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_plasma_options(unsigned char *buffer, unsigned char section_num, float size, float resolution) {
		FloatByteConvert size_byte(size);
		FloatByteConvert resolution_byte(resolution);

		unsigned char payload[] = {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetPlasmaOptions,
			section_num,
			size_byte.converted.byte[0],
			size_byte.converted.byte[1],
			size_byte.converted.byte[2],
			size_byte.converted.byte[3],
			resolution_byte.converted.byte[0],
			resolution_byte.converted.byte[1],
			resolution_byte.converted.byte[2],
			resolution_byte.converted.byte[3]
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_sparkle_options(unsigned char *buffer, unsigned char section_num, unsigned char threshold) {
		unsigned char payload[] = {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetSparkleOptions,
			section_num,
			threshold
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	// General-purpose Cues

	void AnimationCue::set_colors(unsigned char *buffer, unsigned char section_num, Colors::RGB *colors, unsigned char num_colors) {
		int colors_index = 4;

		unsigned char payload[colors_index + (num_colors * 3)];
		payload[0] = (unsigned char)Cue::Component::Animation;
		payload[1] = (unsigned char)Action::SetColors;
		payload[2] = section_num;
		payload[3] = num_colors;

		for (unsigned char i = 0; i < num_colors; i++) {
			payload[colors_index] = colors[i].r;
			colors_index++;
			payload[colors_index] = colors[i].g;
			colors_index++;
			payload[colors_index] = colors[i].b;
			colors_index++;
		}

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_cycle_index(unsigned char *buffer, unsigned char section_num, unsigned char cycle_index) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetCycleIndex,
			section_num,
			cycle_index
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_fade(unsigned char* buffer, unsigned char section_num, bool fade) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetFade,
			section_num,
			(unsigned char)fade
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_orientation(unsigned char *buffer, unsigned char section_num, Animation::Orientation orientation) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetReverse,
			section_num,
			(unsigned char)orientation
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_reverse(unsigned char *buffer, unsigned char section_num, bool reverse) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetReverse,
			section_num,
			(unsigned char)reverse
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::set_speed(unsigned char* buffer, unsigned char section_num, unsigned short speed, unsigned short pause) {
		IntByteConvert speed_byte(speed);
		IntByteConvert pause_byte(pause);
		unsigned char payload[] {
			(unsigned char)Cue::Component::Animation,
			(unsigned char)Action::SetSpeed,
			section_num,
			speed_byte.converted_0,
			speed_byte.converted_1,
			pause_byte.converted_0,
			pause_byte.converted_1
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void AnimationCue::run(Maestro *maestro, unsigned char *cue) {
		Animation* animation = maestro->get_section(cue[Cue::payload_index_ + 2])->get_animation();
		switch((Action)cue[Cue::payload_index_ + 1]) {
			case Action::SetColors:
				{
					unsigned char num_colors = cue[Cue::payload_index_ + 3];
					unsigned char current_color_index = 4;
					Colors::RGB colors[num_colors];
					for (unsigned char i = 0; i < num_colors; i++) {
						colors[i].r = cue[Cue::payload_index_ + current_color_index];
						current_color_index++;
						colors[i].g = cue[Cue::payload_index_ + current_color_index];
						current_color_index++;
						colors[i].b = cue[Cue::payload_index_ + current_color_index];
						current_color_index++;
					}
					animation->set_colors(colors, num_colors);
				}
				break;
			case Action::SetCycleIndex:
				animation->set_cycle_index(cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetFade:
				animation->set_fade(cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetLightningOptions:
				{
					static_cast<LightningAnimation*>(animation)->set_bolt_count(cue[Cue::payload_index_ + 3]);
					static_cast<LightningAnimation*>(animation)->set_thresholds(cue[Cue::payload_index_ + 4], cue[Cue::payload_index_ + 5]);
					static_cast<LightningAnimation*>(animation)->set_fork_chance(cue[Cue::payload_index_ + 6]);
				}
				break;
			case Action::SetPlasmaOptions:
				{
					float size = FloatByteConvert::byte_to_float(&cue[Cue::payload_index_ + 3]);
					float resolution = FloatByteConvert::byte_to_float(&cue[Cue::payload_index_ + 7]);
					static_cast<PlasmaAnimation*>(animation)->set_size(size);
					static_cast<PlasmaAnimation*>(animation)->set_resolution(resolution);
				}
				break;
			case Action::SetOrientation:
				animation->set_orientation((Animation::Orientation)cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetReverse:
				animation->set_reverse(cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetSparkleOptions:
				static_cast<SparkleAnimation*>(animation)->set_threshold(cue[Cue::payload_index_ + 3]);
				break;
			case Action::SetSpeed:
				animation->set_speed(
					IntByteConvert::byte_to_int(&cue[Cue::payload_index_ + 3]),
					IntByteConvert::byte_to_int(&cue[Cue::payload_index_ + 5]));
				break;
		}
	}
}
