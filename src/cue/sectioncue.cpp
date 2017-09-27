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

#include "cue.h"
#include "sectioncue.h"

namespace PixelMaestro {
	void SectionCue::add_canvas(unsigned char* buffer, unsigned char section_num, CanvasType::Type canvas_type) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Section,
			(unsigned char)Action::AddCanvas,
			section_num,
			canvas_type
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::add_overlay(unsigned char* buffer, unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha) {
		unsigned char payload[] {
			(unsigned char)Cue::Component::Section,
			(unsigned char)Action::AddOverlay,
			section_num,
			mix_mode,
			alpha
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::set_animation(unsigned char *buffer, unsigned char section_num, Animation::Type animation_type, bool preserve_cycle_index, Colors::RGB* colors, unsigned char num_colors) {

		unsigned char payload[3 + (num_colors * 3)];
		payload[0] = (unsigned char)Cue::Component::Section;
		payload[1] = (unsigned char)Action::SetAnimation;
		payload[2] = section_num;
		payload[3] = (unsigned char)animation_type;
		payload[4] = (unsigned char)preserve_cycle_index;

		int colors_index = 5;
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

	void SectionCue::set_dimensions(unsigned char *buffer, unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);
		unsigned char payload[] {
			(unsigned char)Cue::Component::Section,
			(unsigned char)Action::SetDimensions,
			section_num,
			x_byte.index_0,
			x_byte.index_1,
			y_byte.index_0,
			y_byte.index_1
		};

		Cue::assemble(buffer, payload, sizeof(payload));
	}

	void SectionCue::run(Maestro *maestro, unsigned char *cue) {
		Section* section = maestro->get_section(cue[Cue::payload_index_ + 2]);
		switch ((Action)cue[Cue::payload_index_ + 1]) {
			case Action::AddCanvas:
				section->add_canvas(CanvasType::Type(cue[Cue::payload_index_ + 3]));
				break;
			case Action::AddOverlay:
				section->add_overlay(Colors::MixMode(cue[Cue::payload_index_ + 3]), cue[Cue::payload_index_ + 4]);
				break;
			case Action::SetAnimation:
				{
					Animation* animation;
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
							animation = new BlinkAnimation(colors, num_colors);
							break;
						case Animation::Type::Cycle:
							animation = new CycleAnimation(colors, num_colors);
							break;
						case Animation::Type::Lightning:
							animation = new LightningAnimation(colors, num_colors);
							break;
						case Animation::Type::Mandelbrot:
							animation = new MandelbrotAnimation(colors, num_colors);
							break;
						case Animation::Type::Merge:
							animation = new MergeAnimation(colors, num_colors);
							break;
						case Animation::Type::Plasma:
							animation = new PlasmaAnimation(colors, num_colors);
							break;
						case Animation::Type::Radial:
							animation = new RadialAnimation(colors, num_colors);
							break;
						case Animation::Type::Random:
							animation = new RandomAnimation(colors, num_colors);
							break;
						case Animation::Type::Solid:
							animation = new SolidAnimation(colors, num_colors);
							break;
						case Animation::Type::Sparkle:
							animation = new SparkleAnimation(colors, num_colors);
							break;
						case Animation::Type::Wave:
							animation = new WaveAnimation(colors, num_colors);
							break;
					}
					section->set_animation(animation, (bool)cue[Cue::payload_index_ + 4]);
				}
				break;
			case Action::SetDimensions:
				section->set_dimensions(
					IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 3], cue[Cue::payload_index_ + 4]),
					IntByteConvert::byte_to_int(cue[Cue::payload_index_ + 5], cue[Cue::payload_index_ + 6]));
				break;
		}
	}
}
