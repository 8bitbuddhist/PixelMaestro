#ifndef CANVASTYPE_H
#define CANVASTYPE_H

namespace PixelMaestro {
	class CanvasType {
		public:
			/// Lists the types of Canvases available.
			enum Type {

				/// Traditional Canvas. Draws Pixels using the underlying Section Animation.
				ANIMATIONCANVAS,

				/// Draws Pixels using custom colors.
				COLORCANVAS
			};
	};
}

#endif // CANVASTYPE_H
