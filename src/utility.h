#ifndef UTILITY_H
#define UTILITY_H

namespace PixelMaestro {
	class Utility {
		public:
			static unsigned char abs_char(char val);
			static int rand();

		private:
			/// Initial RNG seed.
			static int seed_;
	};
}

#endif // UTILITY_H
