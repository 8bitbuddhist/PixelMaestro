#ifndef PLASMAANIMATION_H
#define PLASMAANIMATION_H

#include "mappedanimation.h"

namespace  PixelMaestro {
	class PlasmaAnimation : public MappedAnimation {
		public:
			explicit PlasmaAnimation(Section* section);
			~PlasmaAnimation();
			float get_resolution() const;
			float get_size() const;
			void map();
			void set_resolution(float resolution);
			void set_size(float size);
			void update();

		private:
			/// The resolution of each plasma (i.e. the number of bands).
			float resolution_ = 32.0;

			/// The size of each plasma.
			float size_ = 4.0;
	};
}

#endif // PLASMAANIMATION_H
