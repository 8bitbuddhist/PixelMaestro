#ifndef UTILITY_H
#define UTILITY_H

namespace PixelMaestro {
	class Utility {
		public:
			static unsigned char abs_char(int val);
			static int rand();

		private:
			static int seed_;
	};
}

#endif // UTILITY_H
