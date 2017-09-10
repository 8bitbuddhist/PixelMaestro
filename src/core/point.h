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

			void operator=(Point point_two) {
				x = point_two.x;
				y = point_two.y;
			}

			bool operator==(Point point_two) {
				return (x == point_two.x && y == point_two.y);
			}

			bool operator!=(Point point_two) {
				return !operator==(point_two);
			}

			Point operator+(Point point_two) {
				return {
					(short)(x + point_two.x),
					(short)(y + point_two.y)
				};
			}

			Point operator-(Point point_two) {
				return {
					(short)(x - point_two.x),
					(short)(y - point_two.y)
				};
			}

			Point operator*(Point point_two) {
				return {
					(short)(x * point_two.x),
					(short)(y * point_two.y)
				};
			}

			Point operator/(Point point_two) {
				return {
					(short)(x / point_two.x),
					(short)(y / point_two.y)
				};
			}

			Point(short x, short y);
			void set(short x, short y);
	};
}

#endif // POINT_H
