#ifndef __SCHEDULE_SET_HPP__
#define __SCHEDULE_SET_HPP__/
/* Qt Includes */
#include <QString>
#include <QColor>

/* C Includes */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct schedule_set
{
	QString name = "";	
	bool is_group = false;
	QColor color;

	static QList<QColor> existing_colors;
};

void randomize_color(schedule_set * ss);
QList<QColor> schedule_set::existing_colors;
#endif
