#include "palette.h"

namespace PixelMaestro {
	/**
	 * Constructor. Sets the Palette's source colors.
	 * @param colors Source color array.
	 * @param size Number of colors in the array.
	 * @param delete_colors_on_destruction If true, delete the array when the Palette is no longer used.
	 */
	Palette::Palette(Colors::RGB *colors, uint8_t size, bool delete_colors_on_destruction) {
		set_colors(colors, size);
		this->delete_colors_on_destruction_ = delete_colors_on_destruction;
	}

	/**
	 * Copy constructor.
	 * @param other Other Palette to copy.
	 */
	Palette::Palette(const Palette &other) {
		set_colors(other.get_colors(), other.get_size());
		this->delete_colors_on_destruction_ = other.get_delete_colors_on_destruction();
	}

	/**
	 * Copy assignment operator.
	 * @param other Other Palette to copy.
	 * @return New Palette.
	 */
	Palette& Palette::operator=(const Palette& other) {
		set_colors(other.get_colors(), other.get_size());
		this->delete_colors_on_destruction_ = other.get_delete_colors_on_destruction();
		return *this;
	}

	/**
		Returns the color at the specified index.
		If the index exceeds the size of the color palette, the index wraps around to the start of the array and counts the remainder.
		For example, if the Section has 10 Pixels and 5 Colors, the Pixel at index 7 will use the color at index 2 (7 % 5 == 2).
		Used mainly to determine which color a Pixel should use during an animation based on where it is in the array.

		@param index Desired index.
		@return Color at the specified index.
	*/
	Colors::RGB* Palette::get_color_at_index(uint8_t index) const {
		if (colors_ == nullptr) return nullptr;

		if (index >= size_) {
			return &colors_[index % size_];
		}
		else {
			return &colors_[index];
		}
	}

	/**
	 * Returns the colors used in the Palette.
	 * @return Palette colors.
	 */
	Colors::RGB* Palette::get_colors() const {
		return colors_;
	}

	/**
	 * Returns whether the Palette deletes its color array on destruction.
	 * @return If true, color array gets deleted.
	 */
	bool Palette::get_delete_colors_on_destruction() const {
		return delete_colors_on_destruction_;
	}

	/**
	 * Returns the number of colors in the Palette.
	 * @return Palette size.
	 */
	uint8_t Palette::get_size() const {
		return size_;
	}

	/**
	 * Swaps the palette's color scheme.
	 * @param colors New colors.
	 * @param size New size.
	 */
	void Palette::set_colors(Colors::RGB *colors, uint8_t size) {
		this->colors_ = colors;
		this->size_ = size;
	}

	Palette::~Palette() {
		if (delete_colors_on_destruction_) {
			delete [] colors_;
		}
	}
}