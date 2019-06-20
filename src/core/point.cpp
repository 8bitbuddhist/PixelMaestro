/*
 * Point.cpp - Defines a point on a grid.
 * Also used to define the size of a grid.
 */

#include "point.h"

namespace PixelMaestro {
	/**
	 * Constructor.
	 * @param x X-axis coordinate.
	 * @param y Y-axis coordinate.
	 */
	Point::Point(uint16_t x, uint16_t y) {
		set(x, y);
	}

	/**
	 * Copy constructor.
	 * @param other Point to copy.
	 */
	Point::Point(const Point &other) {
		set(other.x, other.y);
	}

	/**
	 * When used as a dimension, translates a coordinate into a 1-dimensional array index.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @return Index of the coordinate when translated to a 1D array.
	 */
	uint32_t Point::get_inline_index(uint16_t x, uint16_t y) const {
		return (y * this->x) + x;
	}

	/**
	 * When used as a dimension, checks whether a point falls within the dimensions.
	 * @param x X coordinate to check.
	 * @param y Y coordinate to check.
	 * @return True if in bounds.
	 */
	bool Point::in_bounds(uint16_t x, uint16_t y) const {
		return (x < this->x && y < this->y);
	}

	/**
	 * Shortcut for setting the x and y coordinates.
	 * @param x X-axis coordinate.
	 * @param y Y-axis coordinate.
	 */
	void Point::set(uint16_t x, uint16_t y) {
		this->x = x;
		this->y = y;
	}

	/**
	 * When used as a dimension, returns x * y.
	 * @return X value multiplied by the Y value.
	 */
	uint32_t Point::size() const {
		return x * y;
	}
}
