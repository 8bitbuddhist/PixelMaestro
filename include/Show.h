/*
	Show.cpp - Library for managing PixelMaestro transitions.
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
					sectionNum: The index of the Section to update.
			*/
			enum Actions {
				/**
					Sets the color animation of a Section.

					gridAnimation/lineAnimation: The animation to set.
					val1: Whether to reverse the animation.

				*/
				SET_COLOR_ANIMATION,
				/**
					Sets the update speed of a Section.

					val1: Whether to reverse the animation.
				*/
				SET_UPDATE_SPEED,
				/**
					Toggles fading of a Section.
				*/
				TOGGLE_FADE
			};

			/**
				Options applied on a Transition to the Maestro.
			*/
			struct Opts {
				/// Index of the Section to update.
				unsigned short sectionNum;
				/// Multi-purpose variable.
				int val1;
				/// Animation to set.
				Section::ColorAnimations animation;
			};

			/** Defines an action that a Maestro will perform at a specific time. */
			struct Transition {
				/// The program time when the action will be performed.
				unsigned long time;
				/// The action to perform.
				Actions action;
				/// Options associated with the action.
				Opts opts;
				/// Whether the Transition has already executed.
				bool ran = false;
			};

			/** Default constructor */
			Show(Maestro *maestro, Transition *transitions, unsigned char numTransitions);

			unsigned short getCurrentIndex();
			Transition *getCurrentTransition();
			void update(unsigned long currentTime);

			/** Default destructor */
			virtual ~Show();

		private:
			unsigned short current_index_ = 0;	/// The index of the current Transition.
			Maestro *maestro_;					/// The Maestro that the Transitions apply to.
			Transition *transitions_;			/// Array of Transitions.
			unsigned char num_transitions_;		/// The number of Transitions in the array.

			unsigned short getNextIndex();
			void runTransition(Transition *transition);
	};
}

#endif // SHOW_H
