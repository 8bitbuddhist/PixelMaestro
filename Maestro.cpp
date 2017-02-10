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
	Maestro::Maestro(Grid *grids, unsigned char numGrids) {
		setGrids(grids, numGrids);
	}

	Maestro::Maestro(Line *lines, unsigned char numLines) {
		setLines(lines, numLines);
	}

	Maestro::Maestro(Line *lines, unsigned char numLines, Grid *grids, unsigned char numGrids) {
		setGrids(grids, numGrids);
		setLines(lines, numLines);
	}

	Grid *Maestro::getGrid(unsigned char grid) {
		return &grids_[grid];
	}

	Line *Maestro::getLine(unsigned char line) {
		return &lines_[line];
	}

	unsigned char Maestro::getNumGrids() {
		return num_grids_;
	}

	unsigned char Maestro::getNumLines() {
		return num_lines_;
	}

	bool Maestro::getRunning() {
		return running_;
	}

	unsigned char Maestro::getSpeed() {
		// Default to the slowest possible speed
		unsigned char minSpeed = 255;

		// The Maestro must be at least as fast as the fastest animation.
		// Loop through each Grid and Line until we find it.
		if (num_grids_ > 0) {
			for (unsigned char grid = 0; grid < num_grids_; grid++) {
				for (unsigned char line = 0; line < grids_[grid].getNumLines(); line++) {
					if (grids_[grid].getLine(line)->getSpeed() < minSpeed) {
						minSpeed = grids_[grid].getLine(line)->getSpeed();
					}
				}
			}
		}

		if (num_lines_ > 0) {
			for (unsigned char line = 0; line < num_lines_; line++) {
				if (lines_[line].getSpeed() < minSpeed) {
					minSpeed = lines_[line].getSpeed();
				}
			}
		}

		return minSpeed;
	}

	void Maestro::setGrids(Grid *grids, unsigned char numGrids) {
		grids_ = grids;
		num_grids_ = numGrids;
	}

	void Maestro::setLines(Line *lines, unsigned char numLines) {
		lines_ = lines;
		num_lines_ = numLines;
	}

	void Maestro::toggleRunning() {
		running_ = !running_;
	}

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
