/*
 * Point.h - Defines a point on a grid.
 * Also used to define the size of a grid.
 */

#ifndef POINT_H
#define POINT_H

namespace PixelMaestro {
	class Point {
		public:
			/// X-coordinate.
			short x = 0;

			/// Y-coordinate.
			short y = 0;

			Point();
			Point(short x, short y);
	};
}

#endif // POINT_H
