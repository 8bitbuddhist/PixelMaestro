/*
	Show.cpp - Library for managing PixelMaestro transitions.

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
			/**
				Set of actions that can be performed by a Transition.

				Standard options:
					grid/line: Whether the change applies to a Grid or Line.
					gridNum/lineNum: The index of the Grid or Line to change.
			*/
			enum Actions {
				/**
					Sets the color animation of a Grid or Line.

					gridAnimation/lineAnimation: The animation to set.
					val1: Whether to reverse the animation.

				*/
				SET_COLOR_ANIMATION,
				/**
					Sets the update speed of a Grid or Line.

					val1: Whether to reverse the animation.
				*/
				SET_UPDATE_SPEED,
				/**
					Toggles fading of a Grid or Line.
				*/
				TOGGLE_FADE					/// Toggles fading of a Grid or Line.
			};

			/**
				Options applied on a Transition to the Maestro.
			*/
			struct Opts {
				bool grid;				/// Whether the action modifies a Grid. Leave false if modifying a Line that does *not* belong to a Grid.
				unsigned char gridNum;	/// Index of the Grid to modify.
				bool line;				/// Whether the action modifies a Line. Set grid and line to true if modifying a Line within a Grid.
				unsigned char lineNum;	/// Index of the Line to modify.
				int val1;				/// Multi-purpose storage.
				Line::ColorAnimations lineAnimation;	/// Line animation to set.
				Grid::ColorAnimations gridAnimation;	/// Grid animation to set.
			};

			/**
				Defines an action that a Maestro will perform at a specific time.
			*/
			struct Transition {
				unsigned long time;	/// The program time when the action will be performed.
				Actions action;		/// The action to perform.
				Opts opts;			/// Options associated with the action.
				bool ran = false;	/// Whether the Transition has already executed.
			};

			/** Default constructor */
			Show(Maestro *maestro, Transition *transitions, unsigned char numTransitions);

			int getCurrentIndex();
			Transition *getCurrentTransition();
			void update(unsigned long currentTime);

			/** Default destructor */
			virtual ~Show();

		private:
			unsigned char current_index_ = 0;	/// The index of the current Transition.
			Maestro *maestro_;					/// The Maestro that the Transitions apply to.
			Transition *transitions_;			/// Array of Transitions.
			unsigned char num_transitions_;		/// The number of Transitions in the array.

			unsigned char getNextIndex();
			void runTransition(Transition *transition);
	};
}

#endif // SHOW_H
