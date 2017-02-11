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

#ifndef SHOW_H
#define SHOW_H

#include "Maestro.h"

using namespace std;
using namespace PixelMaestro;

namespace PixelMaestro {
	class Show {
		public:
			enum Actions {
				// CHANGE_COLOR,			// {Actions action, byte index, byte r, byte g, byte b}
				// GENERATE_COLOR_ARRAY,	// {Actions action, byte size, byte r, byte g, byte b}
				// GENERATE_SCALING_COLOR_ARRAY,	// {Actions action, byte array size, byte color1.r, byte color1.g, byte color1.b, byte color2.r, byte color2.g, byte color2.b, bool reverse}
				SET_COLOR_ANIMATION,
				SET_SPEED,
				TOGGLE_FADE
				// SET_PATTERN				// {Actions action, byte pattern_index}
			};

			struct Opts {
				bool grid;			// Does this action modify a Grid?
				unsigned char gridNum;		// Index of the Grid to modify. Leave null if you're modifying a line.
				bool line;			// Does this action modify a Line?
				unsigned char lineNum;		// Index of the Line to modify. Leave null if you're modifying a Grid, or combine with gridNum to modify a Line within a Grid.
				int val1;					// Generic stored value
				Line::ColorAnimations lineAnimation;	// Line animation to change to.
				Grid::ColorAnimations gridAnimation;	// Grid animation to change to.
				/*unsigned char index;		// Index of the color or pattern to change
				unsigned char array_size;	// Size of the color or scaling array
				unsigned char update_speed;		// Animation interval period
				unsigned char mode;			// Mode to set
				unsigned char mode_opts;	// Options to append to the mode
				unsigned char threshold;	// Threshold when generating a color array
				unsigned char r;			// r-value for the first color
				unsigned char g;			// g-value for the first color
				unsigned char b;			// b-value for the first color
				unsigned char r2;			// r-value for the second color
				unsigned char g2;			// g-value for the second color
				unsigned char b2;			// b-value for the second color
				bool reverse;				// Whether to generate a color scheme that scales in reverse
				*/
			};

			struct Transition {
				unsigned long time;
				Actions action;
				Opts opts;
				bool ran = false;
			};

			/** Default constructor */
			Show(Maestro *maestro, Transition *transitions, unsigned char numTransitions);

			void nextTransition();
			int getCurrentIndex();
			Transition *getCurrentTransition();
			void update(unsigned long currentTime);

			/** Default destructor */
			virtual ~Show();

		private:
			unsigned char current_index_ = 0;
			Maestro *maestro_;
			Transition *transitions_;
			unsigned char num_transitions_;

			unsigned char getNextIndex();
			void runTransition(Transition *transition);
	};
}

#endif // SHOW_H
