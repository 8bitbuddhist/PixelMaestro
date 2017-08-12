#ifndef TRANSITION_H
#define TRANSITION_H

namespace PixelMaestro {
	class Transition {

		public:
			Transition(unsigned long time);
			unsigned long getTime();
			virtual void run() = 0;
			void setTime(unsigned long time);

		protected:
			unsigned long time_;

	};
}

#endif // TRANSITION_H
