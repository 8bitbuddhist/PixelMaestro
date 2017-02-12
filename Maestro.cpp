/*
	Maestro.cpp - Library for controlling multiple RGB LEDs

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Maestro.h"
#include "Grid.h"
#include "Line.h"

namespace PixelMaestro {
	/**
		Grid Constructor. Initializes the Pixel array using Grids.

		@param grids Initial Grid array.
		@param numGrids Number of Grids.
	*/
	Maestro::Maestro(Grid *grids, unsigned char numGrids) {
		setGrids(grids, numGrids);
	}

	/**
		Line Constructor. Initializes the Pixel array using Lines.

		@param lines Initial Line array.
		@param numLines Number of Lines.
	*/
	Maestro::Maestro(Line *lines, unsigned char numLines) {
		setLines(lines, numLines);
	}

	/**
		Constructor. Initializes the Pixel array using Grids and Lines.

		@param grids Initial Grid array.
		@param numGrids Number of Grids.
		@param lines Initial Line array.
		@param numLines Number of Lines.
	*/
	Maestro::Maestro(Line *lines, unsigned char numLines, Grid *grids, unsigned char numGrids) {
		setGrids(grids, numGrids);
		setLines(lines, numLines);
	}

	/**
		Returns the Grid at the specified index.

		@param grid Index of the Grid to return.
		@return Grid at the specified index.
	*/
	Grid *Maestro::getGrid(unsigned char grid) {
		return &grids_[grid];
	}

	/**
		Returns the Line at the specified index.

		@param line Index of the Line to return.
		@return Line at the specified index.
	*/
	Line *Maestro::getLine(unsigned char line) {
		return &lines_[line];
	}

	/**
		Returns the number of Grids.

		@return Number of Grids.
	*/
	unsigned char Maestro::getNumGrids() {
		return num_grids_;
	}

	/**
		Returns the number of Lines.

		@return number of Lines.
	*/
	unsigned char Maestro::getNumLines() {
		return num_lines_;
	}

	/**
		Returns whether the Maestro is conducting (running).

		@return Whether the Maestro is running.
	*/
	bool Maestro::getRunning() {
		return running_;
	}

	/**
		Returns the update speed based on the fastest running Grid or Line.

		@return Update speed of the fastest Grid or Line.
	*/
	unsigned char Maestro::getUpdateSpeed() {
		// Start off at the slowest possible speed
		unsigned char minSpeed = 255;

		// The Maestro must be at least as fast as the fastest animation.
		// Loop through each Grid and Line until we find it.
		if (num_grids_ > 0) {
			for (unsigned char grid = 0; grid < num_grids_; grid++) {
				for (unsigned char line = 0; line < grids_[grid].getNumLines(); line++) {
					if (grids_[grid].getLine(line)->getUpdateSpeed() < minSpeed) {
						minSpeed = grids_[grid].getLine(line)->getUpdateSpeed();
					}
				}
			}
		}

		if (num_lines_ > 0) {
			for (unsigned char line = 0; line < num_lines_; line++) {
				if (lines_[line].getUpdateSpeed() < minSpeed) {
					minSpeed = lines_[line].getUpdateSpeed();
				}
			}
		}

		return minSpeed;
	}

	/**
		Sets the Grids used in the Maestro.

		@param grids Array of Grids.
		@param numGrids Number of Grids in the array.
	*/
	void Maestro::setGrids(Grid *grids, unsigned char numGrids) {
		grids_ = grids;
		num_grids_ = numGrids;
	}

	/**
		Sets the Lines used in the Maestro.

		@param lines Array of Lines.
		@param numLines Number of Lines in the array.
	*/
	void Maestro::setLines(Line *lines, unsigned char numLines) {
		lines_ = lines;
		num_lines_ = numLines;
	}

	/**
		Toggles whether the Maestro is conducting (running).
	*/
	void Maestro::toggleRunning() {
		running_ = !running_;
	}

	/**
		Main update routine.

		@param currentTime Program runtime.
	*/
	void Maestro::update(unsigned long currentTime) {
		// Call each Grid and Line's update method.
		if (running_) {
			for (unsigned char grid = 0; grid < num_grids_; grid++) {
				grids_[grid].update(currentTime);
			}

			for (unsigned char line = 0; line < num_lines_; line++) {
				lines_[line].update(currentTime);
			}
		}
	}
}
