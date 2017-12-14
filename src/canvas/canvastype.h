/*
 * CanvasType - List of available Canvases.
 */

#ifndef CANVASTYPE_H
#define CANVASTYPE_H

namespace PixelMaestro {
	class CanvasType {
		public:
			/// Lists the types of Canvases available.
			enum Type : uint8_t {

				/// Traditional Canvas. Draws Pixels using the underlying Section Animation.
				AnimationCanvas,

				/// Draws Pixels using custom colors.
				ColorCanvas,

				/// Draws Pixels using a pre-defined color palette.
				PaletteCanvas
			};
	};
}

#endif // CANVASTYPE_H
