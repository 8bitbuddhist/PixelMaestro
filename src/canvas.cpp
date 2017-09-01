/*
 * Canvas.cpp - Utilities for drawing patterns on a Section.
 */

#include "canvas.h"
#include "utility.h"

namespace PixelMaestro {
	/**
	 * Constructor. This also initializes the Canvas' offset to 0.
	 * @param pattern The array containing the Canvas' individual pixels.
	 */
	Canvas::Canvas(bool* pattern) {
		this->pattern = pattern;

		// Initial offset is set to 0
		offset = new Point(0, 0);
	}

	/**
	 * Blanks out the Canvas (all drawn entities will be lost!).
	 */
	void Canvas::clear() {
		for (unsigned short pixel = 0; pixel < (parent_section->get_dimensions()->x * parent_section->get_dimensions()->y); pixel++) {
			pattern[pixel] = false;
		}
	}

	/**
	 * Draws a single character.
	 * @param origin The starting coordinates.
	 * @param font The Font to render the text in.
	 * @param character The character to display.
	 */
	void Canvas::draw_char(Point* origin, Font* font, const char character) {
		/*
		 * Each char in the font corresponds to a column.
		 * Each bit in the char corresponds to an individual pixel.
		 * We use bitmasking to get the bit value, then enable/disable the pixel based on that bit.
		 */
		unsigned char* currentChar = font->get_char(character);
		for (int column = 0; column < font->size->x; column++) {
			for (int row = 0; row < font->size->y; row++) {
				if (in_bounds(origin)) {
					pattern[parent_section->get_pixel_index(origin->x + column, origin->y + row)] = (currentChar[column] >> row) & 1;
				}
				else {
					break;
				}
			}
		}
	}

	/**
	 * Draws a circle.
	 * @param origin The center of the circle.
	 * @param radius The circle's radius.
	 * @param fill Whether to fill the circle or leave it empty.
	 */
	void Canvas::draw_circle(Point* origin, unsigned short radius, bool fill) {
		// (x – h)2 + (y – k)2 = r2
		// r = radius, h = origin->x, k = origin->y

		/*
		 * First, get the min and max x-values, then the min and max y-values.
		 * Then, create a hypothetical square using these points and iterate over each pixel in the square.
		 * If the pixel satisfies the equation, activate it:
		 *		(cursor.x – origin.x)^2 + (cursor.y – origin.y)^2 = radius^2
		 */
		Point cursor = { 0, 0 };
		unsigned int test_point; // Placeholder for calculating points along the circle line
		unsigned int radius_squared = Utility::square(radius);
		for (cursor.x = origin->x - radius; cursor.x <= origin->x + radius; cursor.x++) {
			for (cursor.y = origin->y - radius; cursor.y <= origin->y + radius; cursor.y++) {
				if (in_bounds(&cursor)) {
					// Check that cursor_x and cursor_y satisfy the equation
					test_point = Utility::square(cursor.x - origin->x) + Utility::square(cursor.y - origin->y);
					/*
					 * Check if the test point lies along the line.
					 * We use radius as a sort of tolerance, otherwise only a few pixels would activate.
					 * Or, if fill is enabled, check to see if the point lies inside the circle
					 */
					if ((test_point >= radius_squared - radius && test_point <= radius_squared + radius) ||
						(fill && test_point < Utility::square(radius))) {
						this->pattern[parent_section->get_pixel_index(&cursor)] = 1;
					}
				}
			}
		}
	}

	/**
	 * Draws a line.
	 * @param origin The starting point.
	 * @param target The target point.
	 */
	void Canvas::draw_line(Point* origin, Point* target) {
		// Calculate slope
		float slope;
		if (target->x == origin->x) {
			slope = 1;
		}
		else if (target->y == origin->y) {
			slope = 0;
		}
		else {
			slope = (target->y - origin->y) / (float)(target->x - origin->x);
		}

		Point cursor = { origin->x, origin->y };

		// Handle vertical lines
		if (target->x == origin->x) {
			while (cursor.y != target->y) {
				if (in_bounds(&cursor)) {
					this->pattern[parent_section->get_pixel_index(&cursor)] = 1;
				}

				if (target->y >= cursor.y) {
					cursor.y++;
				}
				else {
					cursor.y--;
				}
			}
		}
		else {
			float y_intercept = (slope * origin->x) - origin->y;
			/*
			 * Move the cursor along the x-axis.
			 * For each x-coordinate, apply the slope and round the y-value to the nearest integer.
			 */
			while (cursor.x != target->x) {
				if (in_bounds(&cursor)) {
					this->pattern[parent_section->get_pixel_index(&cursor)] = 1;
				}

				if (target->x >= origin->x) {
					cursor.x++;
				}
				else {
					cursor.x--;
				}
				cursor.y = (slope * (float)cursor.x) - y_intercept;
			}
		}
	}

	/**
	 * Enables the pixel at the specified coordinates.
	 * @param cursor Location of the pixel to toggle.
	 */
	void Canvas::draw_point(Point* cursor) {
		pattern[parent_section->get_pixel_index(cursor)] = 1;
	}

	/**
	 * Draws a rectangle.
	 * @param origin The starting coordinates.
	 * @param size The size of the rectangle.
	 * @param fill Whether to fill the rectangle or leave it empty.
	 */
	void Canvas::draw_rect(Point* origin, Point* size, bool fill) {
		Point cursor = { origin->x, origin->y };
		for (unsigned short column = 0; column < size->x; column++) {
			// (Re-)Initialize cursor coordinates.
			cursor.x = origin->x + column;
			cursor.y = origin->y;
			for (unsigned short row = 0; row < size->y; row++) {
				cursor.y = origin->y + row;
				if (in_bounds(&cursor)) {
					// Check whether to fill
					if (fill) {
						this->pattern[parent_section->get_pixel_index(&cursor)] = 1;
					}
					else {
						/*
						 * Only draw if the cursor is at the border of the rectangle.
						 * We do this by checking to see if the cursor is either horizontally or vertically aligned with the starting or end point.
						 */
						if ((cursor.x == origin->x || cursor.y == origin->y) ||
							(column == size->x - 1 || row == size->y - 1)) {
							this->pattern[parent_section->get_pixel_index(&cursor)] = 1;
						}
						else {
							// Don't fill.
							continue;
						}
					}
				}
			}
		}
	}

	/**
	 * Draws a string of characters.
	 * @param origin The starting point for the string.
	 * @param font The Font to render the text in.
	 * @param text The string to render.
	 * @param num_chars The number of characters in the string.
	 */
	void Canvas::draw_text(Point* origin, Font* font, const char* text, unsigned short num_chars) {
		Point cursor = {origin->x, origin->y};

		// Iterate over each letter and draw using drawChar().
		for (unsigned short letter = 0; letter < num_chars; letter++) {
			this->draw_char(&cursor, font, text[letter]);

			// Move cursor to the location of the next letter based on the font size.
			cursor.x += font->size->x;
		}
	}

	/**
	 * Draws a triangle. Points are drawn in a clockwise manner.
	 * @param point_a The first point of the triangle.
	 * @param point_b The next point clockwise from point a.
	 * @param point_c The third point of the triangle.
	 * @param fill Whether to fill the triangle or leave it empty.
	 */
	void Canvas::draw_triangle(Point* point_a, Point* point_b, Point* point_c, bool fill) {
		this->draw_line(point_a, point_b);
		this->draw_line(point_b, point_c);
		this->draw_line(point_c, point_a);

		if (fill) {
			/*
			 * This uses barycentric coordinates to check whether the cursor is inside the triangle.
			 *		https://en.wikipedia.org/wiki/Barycentric_coordinate_system_(mathematics)
			 *		https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
			 */
			Point cursor = { 0, 0 };
			float area, s, t;
			area = 0.5 *(-point_b->y*point_c->x + point_a->y*(-point_b->x + point_c->x) + point_a->x*(point_b->y - point_c->y) + point_b->x*point_c->y);

			// Until I find a more efficient way to do this, we're just gonna iterate through each pixel in the grid.
			for (cursor.x = 0; cursor.x < parent_section->get_dimensions()->x; cursor.x++) {
				for (cursor.y = 0; cursor.y < parent_section->get_dimensions()->y; cursor.y++) {
					s = 1/(2*area)*(point_a->y*point_c->x - point_a->x*point_c->y + (point_c->y - point_a->y)*cursor.x + (point_a->x - point_c->x)*cursor.y);
					t = 1/(2*area)*(point_a->x*point_b->y - point_a->y*point_b->x + (point_a->y - point_b->y)*cursor.x + (point_b->x - point_a->x)*cursor.y);

					if (s > 0 && t > 0 && 1-s-t > 0) {
						this->pattern[parent_section->get_pixel_index(&cursor)] = 1;
					}
				}
			}
		}
	}

	/**
	 * Disables the pixel at the specified coordinate.
	 * @param cursor The location of the pixel to disable.
	 */
	void Canvas::erase(Point* cursor) {
		pattern[parent_section->get_pixel_index(cursor)] = 0;
	}

	/**
	 * Returns whether the given Point is in the bounds of the Canvas.
	 * @param point The Point to check.
	 * @return Whether the Point is in bounds.
	 */
	bool Canvas::in_bounds(Point* point) {
		return (point->x < parent_section->get_dimensions()->x) && (point->y < parent_section->get_dimensions()->y);
	}

	/**
	 * Scrolls the Canvas by 1 increment.
	 * @param current_time The program's current runtime).
	 */
	void Canvas::scroll(const unsigned long& current_time) {
		/*
		 * If Canvas::scroll_interval is set, scroll the Canvas.
		 * scroll_interval dictates how many refreshes will occur before the Canvas is scrolled.
		 * For each axis, determine the impact of scroll_interval-><axis> and make the change.
		 * If the axis exceeds the bounds of the Pixel grid, wrap back to the opposite side.
		 */
		if (scroll_interval) {
			unsigned long target_time = current_time - last_scroll_x;
			if (scroll_interval->x != 0 && (Utility::abs_int(scroll_interval->x) * parent_section->get_refresh_interval()) <= target_time) {

				// Increment or decrement the offset depending on the scroll direction.
				if (scroll_interval->x > 0) {
					offset->x++;
				}
				else {
					offset->x--;
				}

				// Check the bounds of the parent Section.
				if (offset->x >= parent_section->get_dimensions()->x) {
					offset->x = 0;
				}
				else if (offset->x - 1 < 0) {
					offset->x = parent_section->get_dimensions()->x;
				}

				last_scroll_x = current_time;
			}

			target_time = current_time - last_scroll_y;
			if (scroll_interval->y != 0 && (Utility::abs_int(scroll_interval->y) * parent_section->get_refresh_interval()) <= target_time) {

				// Increment or decrement the offset depending on the scroll direction.
				if (scroll_interval->y > 0) {
					offset->y++;
				}
				else {
					offset->y--;
				}

				// Check the bounds of the parent Section.
				if (offset->y >= parent_section->get_dimensions()->y) {
					offset->y = 0;
				}
				else if (offset->y - 1 < 0) {
					offset->y = parent_section->get_dimensions()->y;
				}

				last_scroll_y = current_time;
			}
		}
	}

	/**
	 * Redraw the Canvas.
	 * @param current_time The program's current runtime (passed in by a Section).
	 */
	void Canvas::update(const unsigned long& current_time) {
		// Temporarily store the current color being applied.
		Colors::RGB* tmp_color;

		/*
		 * Iterate over each bool in the Canvas.
		 * If the bool is false, deactivate the corresponding Pixel in the Pixel grid.
		 * If repeat is enabled, wrap the out-of-bounds part of the Canvas to the opposite end.
		 * If Canvas::offset is set, calculate the true index of the Pixel by adding the offset.
		 */
		for (unsigned short row = 0; row < parent_section->get_dimensions()->y; row++) {
			for (unsigned short column = 0; column < parent_section->get_dimensions()->x; column++) {

				/*
				 * Iterate through all Pixels.
				 * If the Pixel is enabled, assign it the foreground color, otherwise assign the background color.
				 * If the foregound color isn't set, skip over the Pixel and allow the ColorAnimation's color to pass through.
				 * If the background color isn't set, just show black.
				 */
				if (pattern[parent_section->get_pixel_index(column, row)]) {
					if (fg_color) {
						tmp_color = fg_color;
					}
					else {
						// Skip this Pixel.
						continue;
					}

				}
				else {
					if (bg_color) {
						tmp_color = bg_color;
					}
					else {
						tmp_color = &Colors::BLACK;
					}
				}

				/*
				 * Set the Pixel's color.
				 * First, check one more time to make sure the Pixel is still in bounds.
				 * If it's out of bounds, check to make sure repeat is enabled. If it is, move the Pixel to the other side of the Canvas.
				 */
				if (row + offset->y < parent_section->get_dimensions()->y &&
					column + offset->x < parent_section->get_dimensions()->x) {
					parent_section->set_one(row + offset->y,
						column + offset->x,
						tmp_color);
				}
				else if (repeat) {
					parent_section->set_one((row + offset->y) % parent_section->get_dimensions()->y,
						(column + offset->x) % parent_section->get_dimensions()->x,
						tmp_color);
				}
			}
		}

		scroll(current_time);
	}

	Canvas::~Canvas() {
		delete this->offset;
	}
}
