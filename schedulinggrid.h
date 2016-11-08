#ifndef SCHEDULINGGRID_H
#define SCHEDULINGGRID_H

#include <QWidget>
#include <QString>
#include <QDebug>

#include "ui_schedulinggrid.h"
#include "createevent.h"
#include "usercreatedevent.h"

namespace Ui {
class schedulingGrid;
}

class schedulingGrid : public QWidget
{
    Q_OBJECT

public:
    explicit schedulingGrid(QWidget *parent = 0);
    ~schedulingGrid();

	QString * m_p_username;
	QString * m_p_password;

	Q_SLOT void on_back_button();
	Q_SIGNAL void return_to_home_screen();
private:
    Q_SLOT void on_pushCalendar_clicked();
    Q_SLOT void on_pushLeft_clicked();
    Q_SLOT void on_pushRight_clicked();
    Q_SLOT void on_pushGetDay_clicked();
    Q_SLOT void on_pushWeek_clicked();
    Q_SLOT void on_pushCreateEvent_clicked();
	
private:
    Ui::schedulingGrid *ui;
};

#endif // SCHEDULINGGRID_H
