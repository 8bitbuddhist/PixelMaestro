#ifndef SECTIONSERIAL_H
#define SECTIONSERIAL_H

#include "canvas/canvastype.h"
#include "core/colors.h"
#include "core/maestro.h"

namespace PixelMaestro {
	class SectionSerial {
		public:
			enum Action {
				AddCanvas,
				AddOverlay,
				SetAnimation
			};

			static void add_canvas(unsigned char* buffer, unsigned char section_num, CanvasType::Type canvas_type);
			static void add_overlay(unsigned char* buffer, unsigned char section_num, Colors::MixMode mix_mode, unsigned char alpha);
			//TODO static unsigned char* set_animation(unsigned short section_num)

			static void run(Maestro* maestro, unsigned char* buffer);
	};
}

#endif // SECTIONCOMMAND_H
