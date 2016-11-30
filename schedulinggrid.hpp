#ifndef __SCHEDULINGGRID_HPP__
#define __SCHEDULINGGRID_HPP__
#include <QWidget>
#include <QString>
#include <QDebug>
#include <cmath>
#include <map>

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

	int m_month;
	int m_year;
	
	QString * m_p_username;
	QString * m_p_password;

	group_event_thread * m_p_group_thread;
	user_event_thread * m_p_user_thread;

    void fromHome();
	uint get_year();
	void reset_maps();
	
	Q_SIGNAL void return_to_home_screen();

	Q_SLOT void colorCalendar();
	Q_SLOT void generateCalendar();

	Q_SLOT void to_create_event();
    Q_SLOT void from_create_event();
private:
	Ui::schedulingGrid *ui;

	Q_SLOT void set_user_occupied_days(QString, uint);
	Q_SLOT void set_group_occupied_days(QString, uint);

	Q_SLOT void on_back_button();
    Q_SLOT void on_PushSwitchViews_clicked();
    Q_SLOT void on_pushRightW_clicked();
    Q_SLOT void on_pushLeftW_clicked();
    Q_SLOT void on_pushLeft_clicked();
    Q_SLOT void on_pushRight_clicked();

	Q_SLOT void generateWeek();

	QMutex * m_p_user_occupied_days;
	QMutex * m_p_group_occupied_days;
	std::map<QString,uint> * user_occupied_days;
	std::map<QString,uint> * group_occupied_days;
    createevent * m_p_createevent;
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
