/*
 * Canvas.cpp -Base class for drawing patterns on a Section.
 */

#include "../utility.h"
#include "canvas.h"

namespace PixelMaestro {
	/**
	 * Constructor. This sets the parent Section.
	 * @param section The Canvas' parent Section.
	 */
	Canvas::Canvas(Section* section) {
		this->section_ = section;
	}

	/**
	 * Blanks out the Canvas (anything drawn will be lost!).
	 */
	void Canvas::clear() {
		for (uint32_t pixel = 0; pixel < (uint32_t)(section_->get_dimensions()->size()); pixel++) {
			deactivate(pixel);
		}
	}

	/**
	 * Draws a circle.
	 * @param origin_x Center x coordinate.
	 * @param origin_y Center y coordinate.
	 * @param radius The circle's radius.
	 * @param fill Whether to fill the circle or leave it empty.
	 */
	void Canvas::draw_circle(uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
		// (x – h)^2 + (y – k)^2 = r^2
		// r = radius, h = origin_x, k = origin_y

		/*
		 * First, get the min and max x-values, then the min and max y-values.
		 * Then, create a hypothetical square using these points and iterate over each pixel in the square.
		 * If the pixel satisfies the equation, activate it:
		 *		(cursor.x – origin_x)^2 + (cursor.y – origin_y)^2 = radius^2
		 */
		Point cursor = { 0, 0 };
		uint32_t test_point; // Placeholder for calculating points along the circle line
		uint32_t radius_squared = Utility::square(radius);
		for (cursor.x = origin_x - radius; cursor.x <= origin_x + radius; cursor.x++) {
			for (cursor.y = origin_y - radius; cursor.y <= origin_y + radius; cursor.y++) {
				if (in_bounds(&cursor)) {
					// Check that cursor_x and cursor_y satisfy the equation
					test_point = Utility::square(cursor.x - origin_x) + Utility::square(cursor.y - origin_y);
					/*
					 * Check if the test point lies along the line.
					 * We use radius as a sort of tolerance, otherwise only a few pixels would activate.
					 * Or, if fill is enabled, check to see if the point lies inside the circle
					 */
					if ((test_point >= radius_squared - radius && test_point <= radius_squared + radius) ||
						(fill && test_point < Utility::square(radius))) {
						activate(section_->get_pixel_index(&cursor));
					}
				}
			}
		}
	}

	/**
	 * Draws a line.
	 * @param cursor_x Starting point x coordinate.
	 * @param cursor_y Starting point y coordinate.
	 * @param target_x Ending point x coordinate.
	 * @param target_y Ending point y coordinate.
	 */
	void Canvas::draw_line(uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
		// Calculate slope
		float slope;
		if (target_x == origin_x) {
			slope = 1;
		}
		else if (target_y == origin_y) {
			slope = 0;
		}
		else {
			slope = (target_y - origin_y) / (float)(target_x - origin_x);
		}

		Point cursor = { origin_x, origin_y };

		// Handle vertical lines
		if (target_x == origin_x) {
			while (cursor.y != target_y) {
				if (in_bounds(&cursor)) {
					activate(section_->get_pixel_index(&cursor));
				}

				if (target_y >= cursor.y) {
					cursor.y++;
				}
				else {
					cursor.y--;
				}
			}
		}
		else {
			float y_intercept = (slope * origin_x) - origin_y;
			/*
			 * Move the cursor along the x-axis.
			 * For each x-coordinate, apply the slope and round the y-value to the nearest integer.
			 */
			while (cursor.x != target_x) {
				if (in_bounds(&cursor)) {
					activate(section_->get_pixel_index(&cursor));
				}

				if (target_x >= origin_x) {
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
	 * @param cursor_x Starting point x coordinate.
	 * @param cursor_y Starting point y coordinate.
	 */
	void Canvas::draw_point(uint16_t x, uint16_t y) {
		if (in_bounds(x, y)) {
			activate(section_->get_pixel_index(x, y));
		}
	}

	/**
	 * Draws a rectangle.
	 * @param origin_x Top-left corner x coordinate.
	 * @param origin_y Top-left corner y coordinate.
	 * @param size_x Width of the rectangle.
	 * @param size_y Height of the rectangle.
	 * @param fill Whether to fill the rectangle or leave it empty.
	 */
	void Canvas::draw_rect(uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		Point cursor = { origin_x, origin_y };
		for (uint16_t column = 0; column < size_x; column++) {
			// (Re-)Initialize cursor coordinates.
			cursor.x = origin_x + column;
			cursor.y = origin_y;
			for (uint16_t row = 0; row < size_y; row++) {
				cursor.y = origin_y + row;
				if (in_bounds(&cursor)) {
					// Check whether to fill
					if (fill) {
						activate(section_->get_pixel_index(&cursor));
					}
					else {
						/*
						 * Only draw if the cursor is at the border of the rectangle.
						 * We do this by checking to see if the cursor is either horizontally or vertically aligned with the starting or end point.
						 */
						if ((cursor.x == origin_x || cursor.y == origin_y) ||
							(column == size_x - 1 || row == size_y - 1)) {
							activate(section_->get_pixel_index(&cursor));
						}
					}
				}
			}
		}
	}

	/**
	 * Draws a string of characters.
	 * @param origin_x Top-left x coordinate.
	 * @param origin_y Top-left y coordinate.
	 * @param font The Font to draw the text in.
	 * @param text The string to draw.
	 */
	void Canvas::draw_text(uint16_t origin_x, uint16_t origin_y, Font* font, const char* text, uint8_t num_chars) {
		Point cursor = {origin_x, origin_y};

		uint8_t* current_char;

		for (uint16_t letter = 0; letter < num_chars; letter++) {

			/*
			 * Each char in the font corresponds to a column.
			 * Each bit in the char corresponds to an individual pixel.
			 * We use bitmasking to get the bit value, then enable the pixel based on that bit.
			 */
			current_char = font->get_char(text[letter]);
			for (uint16_t column = 0; column < font->size.x; column++) {
				for (uint16_t row = 0; row < font->size.y; row++) {
					if (in_bounds(&cursor)) {
						if ((current_char[column] >> row) & 1) {
							activate(section_->get_pixel_index(cursor.x + column, cursor.y + row));
						}
					}
				}
			}


			// Move cursor to the location of the next letter based on the font size.
			cursor.x += font->size.x;
		}
	}

	/**
	 * Draws a triangle. Points are drawn in a clockwise manner.
	 * @param point_a_x First point x-coordinate.
	 * @param point_a_y First point y-coordinate.
	 * @param point_b_x Second point x-coordinate.
	 * @param point_b_y Second point y-coordinate.
	 * @param point_c_x Third point x-coordinate.
	 * @param point_c_y Third point y-coordinate.
	 * @param fill Whether to fill the triangle or leave it empty.
	 */
	void Canvas::draw_triangle(uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		this->draw_line(point_a_x, point_a_y, point_b_x, point_b_y);
		this->draw_line(point_b_x, point_b_y, point_c_x, point_c_y);
		this->draw_line(point_c_x, point_c_y, point_a_x, point_a_y);

		if (fill) {
			/*
			 * This uses barycentric coordinates to check whether the cursor is inside the triangle.
			 * https://en.wikipedia.org/wiki/Barycentric_coordinate_system_(mathematics)
			 * https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
			 */
			Point cursor = { 0, 0 };
			float area, s, t;
			area = 0.5 *(-point_b_y*point_c_x + point_a_y*(-point_b_x + point_c_x) + point_a_x*(point_b_y - point_c_y) + point_b_x*point_c_y);

			// Calculate the rectangular bounds of the triangle. This allows us to iterate over a smaller set of Pixels rather than the entire grid.
			uint16_t min_x = 0;
			uint16_t max_x = section_->get_dimensions()->x - 1;
			uint16_t min_y = 0;
			uint16_t max_y = section_->get_dimensions()->y - 1;

			/*
			 * Is point a < point b?
			 *	Yes: Is point a < point c?
			 *		Yes: Return point a
			 *		No: Return point c
			 *	No: Is point b < point c?
			 *		Yes: Return point b
			 *		No: Return point c
			 */
			min_x = (point_a_x < point_b_x ? (point_c_x < point_a_x ? point_c_x : point_a_x) : (point_b_x < point_c_x ? point_b_x : point_c_x));
			max_x = (point_a_x > point_b_x ? (point_c_x > point_a_x ? point_c_x : point_a_x) : (point_b_x > point_c_x ? point_b_x : point_c_x));
			min_y = (point_a_y < point_b_y ? (point_c_y < point_a_y ? point_c_y : point_a_y) : (point_b_y < point_c_y ? point_b_y : point_c_y));
			max_y = (point_a_y > point_b_y ? (point_c_y > point_a_y ? point_c_y : point_a_y) : (point_b_y > point_c_y ? point_b_y : point_c_y));

			// For each point in the "rectangle", determine whether it lies inside the triangle. If so, fill it in.
			for (cursor.x = min_x; cursor.x < max_x; cursor.x++) {
				for (cursor.y = min_y; cursor.y < max_y; cursor.y++) {
					s = 1 / (2 * area) * (point_a_y * point_c_x - point_a_x * point_c_y + (point_c_y - point_a_y) * cursor.x + (point_a_x - point_c_x) * cursor.y);
					t = 1 / (2 * area) * (point_a_x * point_b_y - point_a_y * point_b_x + (point_a_y - point_b_y) * cursor.x + (point_b_x - point_a_x) * cursor.y);

					if (s > 0 && t > 0 && 1 - s - t > 0) {
						activate(section_->get_pixel_index(&cursor));
					}
				}
			}
		}
	}

	/**
	 * Disables the pixel at the specified coordinate.
	 * @param cursor_x The pixel's x-coordinate.
	 * @param cursor_y The pixel's y-coordinate.
	 */
	void Canvas::erase(uint16_t x, uint16_t y) {
		deactivate(section_->get_pixel_index(x, y));
	}

	/**
	 * Returns the Canvas' parent Section.
	 * @return Parent Section.
	 */
	Section* Canvas::get_section() {
		return section_;
	}

	/**
	 * Returns whether the given Point is in the bounds of the Canvas.
	 * @param point The Point to check.
	 * @return Whether the Point is in bounds.
	 */
	bool Canvas::in_bounds(Point* point) {
		return in_bounds(point->x, point->y);
	}

	/**
	 * Returns whether the given Point is in the bounds of the Canvas.
	 * @param x The x-coordinate to check.
	 * @param y The y-coordinate to check.
	 * @return Whether the Point is in bounds.
	 */
	bool Canvas::in_bounds(uint16_t x, uint16_t y) {
		return (x < section_->get_dimensions()->x) && (y < section_->get_dimensions()->y);
	}

	/**
	 * Deletes this Canvas' scrolling behavior.
	 */
	void Canvas::remove_scroll() {
		delete scroll_;
		scroll_ = nullptr;
	}

	/**
	 * Sets the distance that the Canvas is offset from the Pixel grid origin.
	 * Note: This can't be used in combination with set_scroll_interval().
	 * @param x Offset along the x-axis.
	 * @param y Offset along the y-axis.
	 */
	void Canvas::set_offset(int16_t x, int16_t y) {
		offset_x_ = x;
		offset_y_ = y;
	}

	/**
	 * Sets the direction and rate that the Canvas will scroll in.
	 * Note: This can't be used in combination with set_offset().
	 * Scroll time is determined by the Section refresh rate * the scroll interval, so an interval of '5' means scrolling occurs once on that axis every 5 refreshes.
	 * Setting an axis to 0 (default) disables scrolling on that axis.
	 *
	 * @param x Scrolling interval along the x-axis.
	 * @param y Scrolling interval along the y-axis.
	 */
	void Canvas::set_scroll(int16_t x, int16_t y, bool repeat) {
		if (scroll_ == nullptr) {
			scroll_ = new Scroll(x, y, repeat);
		}
		else {
			scroll_->interval_x = y;
			scroll_->interval_y = y;
			scroll_->repeat = repeat;
		}
	}

	/**
	 * Changes the Canvas' parent Section.
	 * @param section New Section.
	 */
	void Canvas::set_section(Section *section) {
		this->section_ = section;
		initialize_pattern();
	}

	/**
	 * Redraw the Canvas.
	 * @param current_time The program's current runtime.
	 */
	void Canvas::update(const uint32_t& current_time) {
		if (scroll_ != nullptr) {
			update_scroll(current_time);
		}
	}

	/**
	 * Scrolls the Canvas by 1 increment.
	 * @param current_time The program's current runtime).
	 */
	void Canvas::update_scroll(const uint32_t& current_time) {
		/*
		 * If Scroll::interval is set, scroll the Canvas.
		 * The interval dictates how many refreshes will occur before the Canvas is scrolled.
		 * For each axis, determine the impact of interval_<axis> and make the change.
		 * For the part of the Canvas that gets pushed off the grid, wrap back to the opposite side.
		 */
		if (scroll_ != nullptr) {
			uint32_t target_time = current_time - scroll_->last_scroll_x;
			if (scroll_->interval_x != 0 && (Utility::abs_int(scroll_->interval_x) * section_->get_refresh_interval()) <= target_time) {

				// Increment or decrement the offset depending on the scroll direction.
				if (scroll_->interval_x > 0) {
					offset_x_++;
				}
				else if (scroll_->interval_x < 0) {
					offset_x_--;
				}

				// Check the bounds of the parent Section.
				if (offset_x_ >= (int32_t)section_->get_dimensions()->x) {
					offset_x_ = 0;
				}
				else if (offset_x_ < 0) {
					offset_x_ = (int32_t)section_->get_dimensions()->x;
				}

				scroll_->last_scroll_x = current_time;
			}

			target_time = current_time - scroll_->last_scroll_y;
			if (scroll_->interval_y != 0 && (Utility::abs_int(scroll_->interval_y) * section_->get_refresh_interval()) <= target_time) {

				// Increment or decrement the offset depending on the scroll direction.
				if (scroll_->interval_y > 0) {
					offset_y_++;
				}
				else if (scroll_->interval_y < 0) {
					offset_y_--;
				}

				// Check the bounds of the parent Section.
				if (offset_y_ >= (int32_t)section_->get_dimensions()->y) {
					offset_y_ = 0;
				}
				else if (offset_y_ < 0) {
					offset_y_ = section_->get_dimensions()->y;
				}

				scroll_->last_scroll_y = current_time;
			}
		}
	}

	Canvas::~Canvas() {
		remove_scroll();
	}
}
