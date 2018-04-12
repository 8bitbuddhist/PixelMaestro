/*
 * CanvasType - List of available Canvases.
 */

#ifndef CANVASTYPE_H
#define CANVASTYPE_H

namespace PixelMaestro {
	/// The types of Canvases available.
	enum class CanvasType : uint8_t {

		/// Draws Pixels using custom colors.
		ColorCanvas,

		/// Draws Pixels using a pre-defined color palette.
		PaletteCanvas
	};
}

#endif // CANVASTYPE_H
