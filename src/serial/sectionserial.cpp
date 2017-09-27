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

#include "serial.h"
#include "sectionserial.h"

namespace PixelMaestro {
	void SectionSerial::add_canvas(unsigned char* buffer, unsigned char section_num, CanvasType::Type canvas_type) {
		unsigned char payload[] {
			(unsigned char)Serial::Component::Section,
			(unsigned char)Action::AddCanvas,
			section_num,
			canvas_type
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void SectionSerial::add_overlay(unsigned char* buffer, unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha) {
		unsigned char payload[] {
			(unsigned char)Serial::Component::Section,
			(unsigned char)Action::AddOverlay,
			section_num,
			mix_mode,
			alpha
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void SectionSerial::set_animation(unsigned char *buffer, unsigned char section_num, Animation::Type animation_type, bool preserve_cycle_index) {
		unsigned char payload[] {
			(unsigned char)Serial::Component::Section,
			(unsigned char)Action::SetAnimation,
			section_num,
			(unsigned char)animation_type,
			(unsigned char)preserve_cycle_index
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void SectionSerial::set_dimensions(unsigned char *buffer, unsigned char section_num, unsigned short x, unsigned short y) {
		IntByteConvert x_byte = IntByteConvert(x);
		IntByteConvert y_byte = IntByteConvert(y);
		unsigned char payload[] {
			(unsigned char)Serial::Component::Section,
			(unsigned char)Action::SetDimensions,
			section_num,
			x_byte.quotient_,
			x_byte.remainder_,
			y_byte.quotient_,
			y_byte.remainder_
		};

		Serial::build_packet(buffer, payload, sizeof(payload));
	}

	void SectionSerial::run(Maestro *maestro, unsigned char *buffer) {
		Section* section = maestro->get_section(buffer[Serial::payload_index_ + 2]);
		switch ((Action)buffer[Serial::payload_index_ + 1]) {
			case Action::AddCanvas:
				section->add_canvas(CanvasType::Type(buffer[Serial::payload_index_ + 3]));
				break;
			case Action::AddOverlay:
				section->add_overlay(Colors::MixMode(buffer[Serial::payload_index_ + 3]), buffer[Serial::payload_index_ + 4]);
				break;
			case Action::SetAnimation:
				{
					Animation* animation;
					switch((Animation::Type)buffer[Serial::payload_index_ + 3]) {
						case Animation::Type::Blink:
							animation = new BlinkAnimation();
							break;
						case Animation::Type::Cycle:
							animation = new CycleAnimation();
							break;
						case Animation::Type::Lightning:
							animation = new LightningAnimation();
							break;
						case Animation::Type::Mandelbrot:
							animation = new MandelbrotAnimation();
							break;
						case Animation::Type::Merge:
							animation = new MergeAnimation();
							break;
						case Animation::Type::Plasma:
							animation = new PlasmaAnimation();
							break;
						case Animation::Type::Radial:
							animation = new RadialAnimation();
							break;
						case Animation::Type::Random:
							animation = new RandomAnimation();
							break;
						case Animation::Type::Solid:
							animation = new SolidAnimation();
							break;
						case Animation::Type::Sparkle:
							animation = new SparkleAnimation();
							break;
						case Animation::Type::Wave:
							animation = new WaveAnimation();
							break;
					}
					section->set_animation(animation, (bool)buffer[Serial::payload_index_ + 4]);
				}
				break;
			case Action::SetDimensions:
				section->set_dimensions(
					IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 3], buffer[Serial::payload_index_ + 4]),
					IntByteConvert::byte_to_int(buffer[Serial::payload_index_ + 5], buffer[Serial::payload_index_ + 6]));
				break;
		}
	}
}
