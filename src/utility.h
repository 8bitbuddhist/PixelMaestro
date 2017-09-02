#ifndef UTILITY_H
#define UTILITY_H

namespace PixelMaestro {
	class Utility {
		public:
			static unsigned int abs_int(short val);
			static int rand();
			static unsigned int square(short val);

		private:
			/// Initial RNG seed.
			static int seed_;
	};
}

#endif // UTILITY_H
