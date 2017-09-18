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
			unsigned short x = 0;

			/// Y-coordinate.
			unsigned short y = 0;

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
					(unsigned short)(x + point_two.x),
					(unsigned short)(y + point_two.y)
				};
			}

			Point operator-(Point point_two) {
				return {
					(unsigned short)(x - point_two.x),
					(unsigned short)(y - point_two.y)
				};
			}

			Point operator*(Point point_two) {
				return {
					(unsigned short)(x * point_two.x),
					(unsigned short)(y * point_two.y)
				};
			}

			Point operator/(Point point_two) {
				return {
					(unsigned short)(x / point_two.x),
					(unsigned short)(y / point_two.y)
				};
			}

			Point(unsigned short x, unsigned short y);
			void set(unsigned short x, unsigned short y);
			unsigned int size();
	};
}

#endif // POINT_H
