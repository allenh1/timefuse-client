#ifndef __SCHEDULINGGRID_HPP__
#define __SCHEDULINGGRID_HPP__
#include <QWidget>
#include <QString>
#include <QDebug>
#include <cmath>

#include "group_event_thread.hpp"
#include "user_event_thread.hpp"
#include "ui_schedulinggrid.h"
#include "tcp_connection.hpp"
#include "createevent.hpp"

typedef unsigned short ushort;
typedef unsigned int uint;

namespace Ui {
	class schedulingGrid;
}

class schedulingGrid : public QWidget
{
    Q_OBJECT

public:
    explicit schedulingGrid(QWidget *parent = 0);
    virtual ~schedulingGrid();

	QString * m_p_username;
	QString * m_p_password;

    void fromHome();
	
	Q_SLOT void on_back_button();
	Q_SIGNAL void return_to_home_screen();

    Q_SLOT void to_create_event();

    Q_SLOT void from_create_event();

private slots:
    void on_tableCalendar_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_PushSwitchViews_clicked();

    void on_pushRightW_clicked();

    void on_pushLeftW_clicked();

private:
	Ui::schedulingGrid *ui;
	
    Q_SLOT void generateCalendar();
    Q_SLOT void on_pushLeft_clicked();
    Q_SLOT void on_pushRight_clicked();
    Q_SLOT void generateWeek();
    Q_SLOT void on_pushCreateEvent_clicked();

    createevent * m_p_createevent;
    int initial = 0;
    void colorCalendar();
};

const QString months[]=
{
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

const QString daysOfWeek[]=
{
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};
#endif
