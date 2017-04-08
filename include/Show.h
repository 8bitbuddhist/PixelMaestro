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
				TOGGLE_FADE					/// Toggles fading of a Section.
			};

			/**
				Options applied on a Transition to the Maestro.
			*/
			struct Opts {
				unsigned char sectionNum;	/// Index of the Section to update.
				int val1;				/// Multi-purpose storage.
				Section::ColorAnimations animation;	/// Animation to set.
			};

			/** Defines an action that a Maestro will perform at a specific time. */
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
