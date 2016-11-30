#ifndef __CREATEEVENT_H__
#define __CREATEEVENT_H__
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <QDialog>
#include <QString>

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

	Ui::createevent * ui;
	
	QString * m_p_username;
	QString * m_p_password;

	Q_SIGNAL void return_to_schedule();
private:
	Q_SLOT void create_the_event();
	Q_SLOT void cancel_event();
};
#endif
