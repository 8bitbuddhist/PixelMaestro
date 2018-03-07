/*
 * MappedAnimation - Abstract Animation class that maps palette colors to pixels.
 * Used for Animations that need to either perform expensive per-pixel calculations, or store temporary grid data to a buffer.
 * Derived classes implement map() and override update().
 * See FireAnimation and MandelbrotAnimation for examples.
 */

#ifndef MAPPEDANIMATION_H
#define MAPPEDANIMATION_H

#include "../core/point.h"
#include "animation.h"

namespace PixelMaestro {
	class MappedAnimation : public Animation {
		public:
			explicit MappedAnimation(Section* section);
			~MappedAnimation();

		protected:
			/// Used to determine whether the grid size has changed.
			Point dimensions_;

			/**
			 * Maps color palette indices to Pixels.
			 * Note: index 255 is reserved for the color black.
			 */
			uint8_t** map_ = nullptr;

			virtual void map() = 0;
			void rebuild_map();
			void update();
	};
}

#endif // MAPPEDANIMATION_H