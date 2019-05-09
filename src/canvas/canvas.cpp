/*
 * Canvas.cpp - Base class for drawing patterns on a Section.
 */

#include <math.h>
#include "../utility.h"
#include "canvas.h"
#include "colorpresets.h"

namespace PixelMaestro {
	/**
	 * Constructor. This sets the parent Section and the specified number of frames.
	 * @param section The Canvas' parent Section.
	 * @param num_frames The number of frames to draw.
	 */
	Canvas::Canvas(Section& section, uint16_t num_frames) : section_(section) {
		this->num_frames_ = num_frames;
		initialize();
	}

	/**
	 * Blanks out the Canvas (anything drawn will be lost!).
	 */
	void Canvas::clear() {
		for (uint16_t frame = 0; frame < num_frames_; frame++) {
			for (uint16_t y = 0; y < section_.get_dimensions().y; y++) {
				for (uint16_t x = 0; x < section_.get_dimensions().x; x++) {
					erase_point(frame, x, y);
				}
			}
		}
	}

	/**
	 * Deletes the current frame set.
	 */
	void Canvas::delete_frames() {
		if (frames_ != nullptr) {
			for (uint16_t i = 0; i < num_frames_; i++) {
				delete[] frames_[i];
			}
		}
		delete[] frames_;
		frames_ = nullptr;
	}

	/**
	 * Draws a circle.
	 * @param origin_x Center x coordinate.
	 * @param origin_y Center y coordinate.
	 * @param radius The circle's radius.
	 * @param fill Whether to fill the circle or leave it empty.
	 */
	void Canvas::draw_circle(uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t radius, bool fill) {
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
		uint32_t radius_squared = pow(radius, 2);
		for (cursor.x = origin_x - radius; cursor.x <= origin_x + radius; cursor.x++) {
			for (cursor.y = origin_y - radius; cursor.y <= origin_y + radius; cursor.y++) {
				if (section_.get_dimensions().in_bounds(cursor.x, cursor.y)) {
					// Check that cursor_x and cursor_y satisfy the equation
					test_point = pow(cursor.x - origin_x, 2) + pow(cursor.y - origin_y, 2);
					/*
					 * Check if the test point lies along the line.
					 * We use radius as a sort of tolerance, otherwise only a few pixels would activate.
					 * Or, if fill is enabled, check to see if the point lies inside the circle
					 */
					if ((test_point >= radius_squared - radius && test_point <= radius_squared + radius) ||
						(fill && test_point < pow(radius, 2))) {
						draw_point(frame_index, color_index, cursor.x, cursor.y);
					}
				}
			}
		}
	}

	/**
	 * Draws an existing frame over the current frame.
	 * @param frame Frame to draw.
	 * @param size_x Frame width.
	 * @param size_y Frame height.
	 */
	void Canvas::draw_frame(uint16_t frame_index, uint8_t* frame, uint16_t size_x, uint16_t size_y) {
		clear();
		Point frame_bounds = Point(size_x, size_y);
		for (uint16_t y = 0; y < size_y; y++) {
			for (uint16_t x = 0; x < size_x; x++) {
				if (section_.get_dimensions().in_bounds(x, y)) {
					draw_point(frame_index, frame[frame_bounds.get_inline_index(x, y)], x, y);
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
	void Canvas::draw_line(uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t target_x, uint16_t target_y) {
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
				if (section_.get_dimensions().in_bounds(cursor.x, cursor.y)) {
					draw_point(frame_index, color_index, cursor.x, cursor.y);
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
				if (section_.get_dimensions().in_bounds(cursor.x, cursor.y)) {
					draw_point(frame_index, color_index, cursor.x, cursor.y);
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
	void Canvas::draw_point(uint16_t frame_index, uint8_t color_index, uint16_t x, uint16_t y) {
		if (section_.get_dimensions().in_bounds(x, y)) {
			frames_[frame_index][section_.get_dimensions().get_inline_index(x, y)] = color_index;
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
	void Canvas::draw_rect(uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, uint16_t size_x, uint16_t size_y, bool fill) {
		Point cursor = { origin_x, origin_y };
		for (uint16_t column = 0; column < size_x; column++) {
			// (Re-)Initialize cursor coordinates.
			cursor.x = origin_x + column;
			cursor.y = origin_y;
			for (uint16_t row = 0; row < size_y; row++) {
				cursor.y = origin_y + row;
				if (section_.get_dimensions().in_bounds(cursor.x, cursor.y)) {
					// Check whether to fill
					if (fill) {
						draw_point(frame_index, color_index, cursor.x, cursor.y);
					}
					else {
						/*
						 * Only draw if the cursor is at the border of the rectangle.
						 * We do this by checking to see if the cursor is either horizontally or vertically aligned with the starting or end point.
						 */
						if ((cursor.x == origin_x || cursor.y == origin_y) ||
							(column == size_x - 1 || row == size_y - 1)) {
							draw_point(frame_index, color_index, cursor.x, cursor.y);
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
	void Canvas::draw_text(uint16_t frame_index, uint8_t color_index, uint16_t origin_x, uint16_t origin_y, Font& font, const char* text, uint8_t num_chars) {
		Point cursor = {origin_x, origin_y};

		for (uint16_t letter = 0; letter < num_chars; letter++) {

			/*
			 * Each char in the font corresponds to a column.
			 * Each bit in the char corresponds to an individual pixel.
			 * We use bitmasking to get the bit value, then enable the pixel based on that bit.
			 */
			const uint8_t* current_char = font.get_char(text[letter]);
			for (uint16_t column = 0; column < font.size.x; column++) {
				for (uint16_t row = 0; row < font.size.y; row++) {
					if (section_.get_dimensions().in_bounds(cursor.x, cursor.y)) {
						if ((current_char[column] >> row) & 1) {
							draw_point(frame_index, color_index, cursor.x + column, cursor.y + row);
						}
					}
				}
			}

			// Move cursor to the location of the next letter based on the font size.
			cursor.x += font.size.x;
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
	void Canvas::draw_triangle(uint16_t frame_index, uint8_t color_index, uint16_t point_a_x, uint16_t point_a_y, uint16_t point_b_x, uint16_t point_b_y, uint16_t point_c_x, uint16_t point_c_y, bool fill) {
		this->draw_line(frame_index, color_index, point_a_x, point_a_y, point_b_x, point_b_y);
		this->draw_line(frame_index, color_index, point_b_x, point_b_y, point_c_x, point_c_y);
		this->draw_line(frame_index, color_index, point_c_x, point_c_y, point_a_x, point_a_y);

		if (fill) {
			/*
			 * This uses barycentric coordinates to check whether the cursor is inside the triangle.
			 * https://en.wikipedia.org/wiki/Barycentric_coordinate_system_(mathematics)
			 * https://stackoverflow.com/questions/2049582/how-to-determine-if-a-point-is-in-a-2d-triangle
			 */
			Point cursor = { 0, 0 };
			float area, s, t;
			area = 0.5 *(-point_b_y*point_c_x + point_a_y*(-point_b_x + point_c_x) + point_a_x*(point_b_y - point_c_y) + point_b_x*point_c_y);

			/*
			 * Instead of checking every single point in the frame, check only the area containing the triangle.
			 * We calculate a small rectangle based on the triangle's vertices and check each Pixel in that area.
			 *
			 * Is point a < point b?
			 *	Yes: Is point a < point c?
			 *		Yes: Return point a
			 *		No: Return point c
			 *	No: Is point b < point c?
			 *		Yes: Return point b
			 *		No: Return point c
			 */
			uint16_t min_x = (point_a_x < point_b_x ? (point_c_x < point_a_x ? point_c_x : point_a_x) : (point_b_x < point_c_x ? point_b_x : point_c_x));
			uint16_t max_x = (point_a_x > point_b_x ? (point_c_x > point_a_x ? point_c_x : point_a_x) : (point_b_x > point_c_x ? point_b_x : point_c_x));
			uint16_t min_y = (point_a_y < point_b_y ? (point_c_y < point_a_y ? point_c_y : point_a_y) : (point_b_y < point_c_y ? point_b_y : point_c_y));
			uint16_t max_y = (point_a_y > point_b_y ? (point_c_y > point_a_y ? point_c_y : point_a_y) : (point_b_y > point_c_y ? point_b_y : point_c_y));

			// For each Pixel in the rectangle, determine whether it lies inside the triangle. If so, fill it in.
			for (cursor.x = min_x; cursor.x < max_x; cursor.x++) {
				for (cursor.y = min_y; cursor.y < max_y; cursor.y++) {
					s = 1 / (2 * area) * (point_a_y * point_c_x - point_a_x * point_c_y + (point_c_y - point_a_y) * cursor.x + (point_a_x - point_c_x) * cursor.y);
					t = 1 / (2 * area) * (point_a_x * point_b_y - point_a_y * point_b_x + (point_a_y - point_b_y) * cursor.x + (point_b_x - point_a_x) * cursor.y);

					if (s > 0 && t > 0 && 1 - s - t > 0) {
						draw_point(frame_index, color_index, cursor.x, cursor.y);
					}
				}
			}
		}
	}


	/**
	 * Sets the color of the pixel at the specified index to transparent.
	 * @param x X coordinate.
	 * @param y Y coordinate.
	 */
	void Canvas::erase_point(uint16_t frame_index, uint16_t x, uint16_t y) {
		frames_[frame_index][section_.get_dimensions().get_inline_index(x, y)] = 255;
	}

	/**
	 * Returns the index of the current frame.
	 * @return Current frame index.
	 */
	uint16_t Canvas::get_current_frame_index() const {
		return current_frame_index_;
	}

	/**
	 * Returns the frame at the specified index.
	 * @param frame Index of the frame.
	 * @return Frame at index.
	 */
	uint8_t* Canvas::get_frame(uint16_t frame) const {
		return frames_[frame];
	}

	/**
	 * Returns the frame timer.
	 * Used in PixelMaestro Studio.
	 * @return Frame timer.
	 */
	Timer* Canvas::get_frame_timer() const {
		return frame_timer_;
	}

	/**
	 * Returns the number of frames.
	 * @return Number of frames.
	 */
	uint16_t Canvas::get_num_frames() const {
		return num_frames_;
	}

	/**
	 * Returns the color palette.
	 *
	 * @return Color palette.
	 */
	Palette* Canvas::get_palette() const {
		return palette_;
	}

	/**
	 * Returns the color at the specified Pixel.
	 *
	 * @param x Pixel X coordinate.
	 * @param y Pixel Y coordinate.
	 * @return Color if found. If the Pixel is transparent, return nullptr.
	 */
	Colors::RGB* Canvas::get_pixel_color(uint16_t x, uint16_t y) {
		uint8_t index = frames_[current_frame_index_][section_.get_dimensions().get_inline_index(x, y)];
		if (index != 255) {
			return &palette_->get_color_at_index(index);
		}
		else {
			return nullptr;
		}
	}

	/**
	 * Returns the Canvas' parent Section.
	 * @return Parent Section.
	 */
	Section& Canvas::get_section() const {
		return section_;
	}

	/// Builds the Canvas.
	void Canvas::initialize() {
		delete_frames();
		frames_ = new uint8_t*[num_frames_];
		for (uint16_t frame = 0; frame < num_frames_; frame++) {
			frames_[frame] = new uint8_t[section_.get_dimensions().size()];
			for (uint32_t pixel = 0; pixel < section_.get_dimensions().size(); pixel++) {
				frames_[frame][pixel] = 255;
			}
		}
	}

	/**
	 * Advances the animation to the next frame.
	 * If we've hit the total number of frames, wrap back to the first frame.
	 */
	void Canvas::next_frame() {
		if (current_frame_index_ < num_frames_ - 1) {
			current_frame_index_++;
		}
		else {
			current_frame_index_ = 0;
		}
	}

	/**
	 * Moves the animation back a frame.
	 * If we've hit the first frame, jump to the last frame.
	 */
	void Canvas::previous_frame() {
		if (current_frame_index_ > 0) {
			current_frame_index_--;
		}
		else {
			current_frame_index_ = num_frames_ - 1;
		}
	}

	/**
	 * Removes the frame timer, disabling frame animations.
	 */
	void Canvas::remove_frame_timer() {
		delete frame_timer_;
		frame_timer_ = nullptr;
	}

	/**
	 * Changes the active frame.
	 * @param index Index of the new frame.
	 */
	void Canvas::set_current_frame_index(uint16_t index) {
		if (index >= num_frames_) {
			current_frame_index_ = num_frames_ - 1;
		}
		else {
			current_frame_index_ = index;
		}
	}

	/**
	 * Sets the amount of time between frames.
	 * @param speed Amount of time between frames.
	 */
	void Canvas::set_frame_timer(uint16_t speed) {
		if (!frame_timer_) {
			frame_timer_ = new Timer(speed);
		}
		else {
			frame_timer_->set_interval(speed);
		}
	}

	/**
	 * Changes the number of frames, then rebuilds the Canvas.
	 * Existing frames will be deleted.
	 * @param num_frames New number of frames.
	 */
	void Canvas::set_num_frames(uint16_t num_frames) {
		delete_frames();

		this->num_frames_ = num_frames;
		this->current_frame_index_ = 0;

		initialize();
	}

	/**
	 * Sets the Canvas' Palette.
	 * @param palette New Palette.
	 */
	void Canvas::set_palette(Palette& palette) {
		this->palette_ = &palette;
	}

	/**
	 * Update the Canvas. If the Canvas is animated, switch to the next frame.
	 * @param current_time The program's current runtime.
	 */
	void Canvas::update(const uint32_t& current_time) {
		if (frame_timer_ && frame_timer_->update(current_time)) {
			next_frame();
		}
	}

	Canvas::~Canvas() {
		delete_frames();
		remove_frame_timer();
	}
}
