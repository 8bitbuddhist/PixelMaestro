/*
 * SimpleDrawingArea - Implementation of a MaestroDrawingArea as a simple 2D grid.
 */

#ifndef SIMPLEDRAWINGAREA_H
#define SIMPLEDRAWINGAREA_H

#include "controller/maestrocontroller.h"
#include "maestrodrawingarea.h"
#include <QSettings>

class SimpleDrawingArea : public MaestroDrawingArea {
	public:
		SimpleDrawingArea(QWidget* parent, MaestroController* maestro_controller);
		void resize_pixels();

	protected:
		void draw_section(QPainter* painter, uint8_t section_index, QRect start);
		void paintEvent(QPaintEvent *event) override;
		void resizeEvent(QResizeEvent *event) override;

		/// The size of each rendered Pixel.
		uint8_t radius_ = 20;
		/// The amount of space between each Pixel. Gets initialized in resizeEvent().
		uint8_t pad_;

		/// Used to determine whether the Maestro's size has changed.
		std::vector<uint32_t> last_pixel_count_;

	private:
		QSettings settings_;
};

#endif // SIMPLEDRAWINGAREA_H
