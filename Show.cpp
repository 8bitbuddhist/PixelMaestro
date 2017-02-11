/*
	Show.cpp - Library for managing PixelMaestro transitions
	Requires PixelMaestro library

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

#include "Show.h"

namespace PixelMaestro {

	Show::Show(Maestro *maestro, Transition *transitions, unsigned char numTransitions) {
		maestro_ = maestro;
		transitions_ = transitions;
		num_transitions_ = numTransitions;
	}

	int Show::getCurrentIndex() {
		return current_index_;
	}

	Show::Transition *Show::getCurrentTransition() {
		return &transitions_[current_index_];
	}

	unsigned char Show::getNextIndex() {
		// Get the next index. If we've exceeded the size of the array, start over from 0
		if (current_index_ + 1 >= num_transitions_) {
			return 0;
		}
		else {
			return current_index_ + 1;
		}
	}

	void Show::nextTransition() {
		current_index_++;
	}

	void Show::update(unsigned long currentTime) {
		if (currentTime >= transitions_[current_index_].time && !transitions_[current_index_].ran) {
			runTransition(&transitions_[current_index_]);
		}
		maestro_->update(currentTime);
	}

	void Show::runTransition(Transition *transition) {
		Opts opts = transition->opts;
		// Run the current transition
		switch (transition->action) {
			case Actions::SET_SPEED:
				if (opts.line && opts.grid) {
					maestro_->getGrid(opts.gridNum)->getLine(opts.lineNum)->setUpdateSpeed(transition->opts.val1);
				}
				else if (opts.grid) {
					maestro_->getGrid(opts.gridNum)->setUpdateSpeed(transition->opts.val1);
				}
				else if (opts.line) {
					maestro_->getLine(opts.lineNum)->setUpdateSpeed(transition->opts.val1);
				}
				break;
			case Actions::SET_COLOR_ANIMATION:
				if (opts.line && opts.grid) {
					maestro_->getGrid(opts.gridNum)->getLine(opts.lineNum)->setColorAnimation(opts.lineAnimation, opts.val1);
				}
				else if (opts.grid) {
					maestro_->getGrid(opts.gridNum)->setColorAnimation(opts.gridAnimation, opts.val1);
				}
				else if (opts.line) {
					maestro_->getLine(opts.lineNum)->setColorAnimation(opts.lineAnimation, opts.val1);
				}
				break;
			case Actions::TOGGLE_FADE:
				if (opts.line && opts.grid) {
					maestro_->getGrid(opts.gridNum)->getLine(opts.lineNum)->toggleFade();
				}
				else if (opts.grid) {
					maestro_->getGrid(opts.gridNum)->toggleFade();
				}
				else if (opts.line) {
					maestro_->getLine(opts.lineNum)->toggleFade();
				}
				break;
			default:
				break;
		}

		transition->ran = true;
		current_index_ = getNextIndex();
	}

	Show::~Show() {}
}
