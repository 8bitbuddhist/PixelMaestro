/*
 * Point.h - Defines a point on a grid.
 * Also used to define the size of a grid.
 */

#ifndef POINT_H
#define POINT_H

#include <stdint.h>

namespace PixelMaestro {
	class Point {
		public:
			/// X-coordinate.
			uint16_t x = 0;

			/// Y-coordinate.
			uint16_t y = 0;

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

			Point(uint16_t x = 0, uint16_t y = 0);
			uint32_t get_inline_index(Point* point);
			uint32_t get_inline_index(uint16_t x, uint16_t y);
			void set(uint16_t x, uint16_t y);
			uint32_t size();
	};
}

#endif // POINT_H
