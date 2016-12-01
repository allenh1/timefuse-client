#ifndef __CREATEEVENT_H__
#define __CREATEEVENT_H__
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <QDialog>
#include <QString>

#include "suggest_user_event.hpp"
#include "tcp_connection.hpp"
#include "ui_createevent.h"

namespace Ui {
	class createevent;
}

class createevent : public QWidget
{
    Q_OBJECT
public:
    explicit createevent(QWidget *parent = 0);
    virtual ~createevent();
	
	QString * m_p_username;
	QString * m_p_password;

	Q_SIGNAL void return_to_schedule();
private:
	Ui::createevent * ui;
	suggest_user_event * m_p_suggest_event;

	Q_SLOT void get_time(QString);
	Q_SLOT void from_suggest_time();
	Q_SLOT void suggest_a_time();
	Q_SLOT void create_the_event();
	Q_SLOT void cancel_event();
};
#endif
