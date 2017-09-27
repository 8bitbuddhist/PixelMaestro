#ifndef SECTIONSERIAL_H
#define SECTIONSERIAL_H

#include "../canvas/canvastype.h"
#include "../core/colors.h"
#include "../core/maestro.h"

namespace PixelMaestro {
	class SectionSerial {
		public:
			enum Action {
				AddCanvas,
				AddOverlay,
				SetAnimation,
				SetDimensions
			};

			static void add_canvas(unsigned char* buffer, unsigned char section_num, CanvasType::Type canvas_type);
			static void add_overlay(unsigned char* buffer, unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha);
			static void set_animation(unsigned char* buffer, unsigned char section_num, Animation::Type animation_type, bool preserve_cycle_index = false);
			static void set_dimensions(unsigned char* buffer, unsigned char section_num, unsigned short x, unsigned short y);

			static void run(Maestro* maestro, unsigned char* buffer);
	};
}

#endif // SECTIONCOMMAND_H
