/*
 * Canvas.cpp - Utilities for drawing patterns on a Section.
 */

#include "../utility.h"
#include "canvas.h"

namespace PixelMaestro {
	/**
	 * Constructor. This also initializes the Canvas' offset to 0.
	 * @param section The Canvas' parent Section.
	 */
	Canvas::Canvas(Section* section) {
		this->section_ = section;
		initialize_pattern();
	}

	/**
	 * Blanks out the Canvas (anything drawn will be lost!).
	 */
	void Canvas::clear() {
		for (unsigned int pixel = 0; pixel < (unsigned int)(section_->get_dimensions()->size()); pixel++) {
			pattern_[pixel] = false;
		}
	}

	/**
	 * Draws a circle.
	 * @param origin_x Center x coordinate.
	 * @param origin_y Center y coordinate.
	 * @param radius The circle's radius.
	 * @param fill Whether to fill the circle or leave it empty.
	 */
	void Canvas::draw_circle(unsigned short origin_x, unsigned short origin_y, unsigned short radius, bool fill) {
		// (x – h)^2 + (y – k)^2 = r^2
		// r = radius, h = origin_x, k = origin_y

		/*
		 * First, get the min and max x-values, then the min and max y-values.
		 * Then, create a hypothetical square using these points and iterate over each pixel in the square.
		 * If the pixel satisfies the equation, activate it:
		 *		(cursor.x – origin_x)^2 + (cursor.y – origin_y)^2 = radius^2
		 */
		Point cursor = { 0, 0 };
		unsigned int test_point; // Placeholder for calculating points along the circle line
		unsigned int radius_squared = Utility::square(radius);
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
						this->pattern_[section_->get_pixel_index(&cursor)] = 1;
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
	void Canvas::draw_line(unsigned short origin_x, unsigned short origin_y, unsigned short target_x, unsigned short target_y) {
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
					this->pattern_[section_->get_pixel_index(&cursor)] = 1;
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
					this->pattern_[section_->get_pixel_index(&cursor)] = 1;
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
	void Canvas::draw_point(unsigned short x, unsigned short y) {
		if (in_bounds(x, y)) {
			pattern_[section_->get_pixel_index(x, y)] = 1;
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
	void Canvas::draw_rect(unsigned short origin_x, unsigned short origin_y, unsigned short size_x, unsigned short size_y, bool fill) {
		Point cursor = { origin_x, origin_y };
		for (unsigned short column = 0; column < size_x; column++) {
			// (Re-)Initialize cursor coordinates.
			cursor.x = origin_x + column;
			cursor.y = origin_y;
			for (unsigned short row = 0; row < size_y; row++) {
				cursor.y = origin_y + row;
				if (in_bounds(&cursor)) {
					// Check whether to fill
					if (fill) {
						this->pattern_[section_->get_pixel_index(&cursor)] = 1;
					}
					else {
						/*
						 * Only draw if the cursor is at the border of the rectangle.
						 * We do this by checking to see if the cursor is either horizontally or vertically aligned with the starting or end point.
						 */
						if ((cursor.x == origin_x || cursor.y == origin_y) ||
							(column == size_x - 1 || row == size_y - 1)) {
							this->pattern_[section_->get_pixel_index(&cursor)] = 1;
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
	 * @param origin_x Top-left x coordinate.
	 * @param origin_y Top-left y coordinate.
	 * @param font The Font to render the text in.
	 * @param text The string to render.
	 */
	void Canvas::draw_text(unsigned short origin_x, unsigned short origin_y, Font* font, const char* text) {
		Point cursor = {origin_x, origin_y};

		unsigned char* current_char;

		// Iterate over each letter and draw using draw_char().
		for (unsigned short letter = 0; *(letter + text) != 0; letter++) {

			/*
			 * Each char in the font corresponds to a column.
			 * Each bit in the char corresponds to an individual pixel.
			 * We use bitmasking to get the bit value, then enable/disable the pixel based on that bit.
			 */
			current_char = font->get_char(text[letter]);
			for (int column = 0; column < font->size.x; column++) {
				for (int row = 0; row < font->size.y; row++) {
					if (in_bounds(&cursor)) {
						pattern_[section_->get_pixel_index(cursor.x + column, cursor.y + row)] = (current_char[column] >> row) & 1;
					}
					else {
						break;
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
	void Canvas::draw_triangle(unsigned short point_a_x, unsigned short point_a_y, unsigned short point_b_x, unsigned short point_b_y, unsigned short point_c_x, unsigned short point_c_y, bool fill) {
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

			// TODO: Until I find a more efficient way to do this, we're just gonna iterate through each pixel in the grid.
			for (cursor.x = 0; cursor.x < section_->get_dimensions()->x; cursor.x++) {
				for (cursor.y = 0; cursor.y < section_->get_dimensions()->y; cursor.y++) {
					s = 1/(2*area)*(point_a_y*point_c_x - point_a_x*point_c_y + (point_c_y - point_a_y)*cursor.x + (point_a_x - point_c_x)*cursor.y);
					t = 1/(2*area)*(point_a_x*point_b_y - point_a_y*point_b_x + (point_a_y - point_b_y)*cursor.x + (point_b_x - point_a_x)*cursor.y);

					if (s > 0 && t > 0 && 1-s-t > 0) {
						this->pattern_[section_->get_pixel_index(&cursor)] = 1;
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
	void Canvas::erase(unsigned short x, unsigned short y) {
		pattern_[section_->get_pixel_index(x, y)] = 0;
	}

	/**
	 * Returns the boolean value at the specified index.
	 * @param index Index to retrieve.
	 * @return True if drawn, false if not.
	 */
	bool Canvas::get_pattern_index(unsigned int index) {
		return pattern_[index];
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
	bool Canvas::in_bounds(unsigned short x, unsigned short y) {
		return (x < section_->get_dimensions()->x) && (y < section_->get_dimensions()->y);
	}

	/**
	 * Reinitializes the pattern array.
	 */
	void Canvas::initialize_pattern() {
		// Initialize the pattern
		if (pattern_ != nullptr) {
			delete pattern_;
		}
		pattern_ = new bool[section_->get_dimensions()->size()] {0};
	}

	/**
	 * Deletes this Canvas' scrolling behavior.
	 */
	void Canvas::remove_scroll() {
		if (scroll_ != nullptr) {
			delete scroll_;
		}
	}

	/**
	 * Sets the distance that the Canvas is offset from the Pixel grid origin.
	 * Note: This can't be used in combination with set_scroll_interval().
	 * @param x Offset along the x-axis.
	 * @param y Offset along the y-axis.
	 */
	void Canvas::set_offset(signed short x, signed short y) {
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
	void Canvas::set_scroll(signed short x, signed short y, bool repeat) {
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
	void Canvas::update(const unsigned long& current_time) {
		if (scroll_ != nullptr) {
			update_scroll(current_time);
		}
	}

	/**
	 * Scrolls the Canvas by 1 increment.
	 * @param current_time The program's current runtime).
	 */
	void Canvas::update_scroll(const unsigned long& current_time) {
		/*
		 * If Canvas::scroll_interval is set, scroll the Canvas.
		 * scroll_interval dictates how many refreshes will occur before the Canvas is scrolled.
		 * For each axis, determine the impact of scroll_interval-><axis> and make the change.
		 * If the axis exceeds the bounds of the Pixel grid, wrap back to the opposite side.
		 */
		if (scroll_ != nullptr) {
			unsigned long target_time = current_time - scroll_->last_scroll_x;
			if (scroll_->interval_x != 0 && (Utility::abs_int(scroll_->interval_x) * section_->get_refresh_interval()) <= target_time) {

				// Increment or decrement the offset depending on the scroll direction.
				if (scroll_->interval_x > 0) {
					offset_x_++;
				}
				else if (scroll_->interval_x < 0) {
					offset_x_--;
				}

				// Check the bounds of the parent Section.
				if (offset_x_ >= section_->get_dimensions()->x) {
					offset_x_ = 0;
				}
				else if (offset_x_ + 1 == 0) {	// Buffer overflow
					offset_x_ = section_->get_dimensions()->x;
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
				if (offset_y_ >= section_->get_dimensions()->y) {
					offset_y_ = 0;
				}
				else if (offset_y_ + 1 == 0) {	// Buffer overflow
					offset_y_ = section_->get_dimensions()->y;
				}

				scroll_->last_scroll_y = current_time;
			}
		}
	}

	Canvas::~Canvas() {
		delete[] pattern_;
		delete scroll_;
	}
}
