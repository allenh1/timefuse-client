#ifndef SCHEDULINGGRID_H
#define SCHEDULINGGRID_H

#include <QMainWindow>
#include <QString>
#include <QDebug>

#include "ui_schedulinggrid.h"
#include "createevent.h"
#include "usercreatedevent.h"

namespace Ui {
class schedulingGrid;
}

class schedulingGrid : public QMainWindow
{
    Q_OBJECT

public:
    explicit schedulingGrid(QWidget *parent = 0);
    ~schedulingGrid();

	QString * m_p_username;
	QString * m_p_password;

private slots:


    void on_pushCalendar_clicked();

    void on_pushLeft_clicked();

    void on_pushRight_clicked();

    void on_pushGetDay_clicked();

    void on_pushWeek_clicked();

    void on_pushCreateEvent_clicked();

private:
    Ui::schedulingGrid *ui;
};

#endif // SCHEDULINGGRID_H
