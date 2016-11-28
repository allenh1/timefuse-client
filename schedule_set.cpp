#include "schedule_set.hpp"

void randomize_color(schedule_set * ss)
{
	bool unique = false; srand(time(NULL));
	QColor & color = ss->color;
	for (; !unique; unique = existing_colors.contains(color)) {
		/* create a new color, randomly */
		color.setRgb(rand() % 256, rand() % 256, rand() % 256);
	}
}
