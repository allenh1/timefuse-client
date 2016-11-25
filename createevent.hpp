#ifndef __CREATEEVENT_H__
#define __CREATEEVENT_H__
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <QDialog>
#include <QString>

#include "usercreatedevent.hpp"
#include "tcp_connection.hpp"
#include "ui_createevent.h"

namespace Ui {
	class createevent;
}

class createevent : public QDialog
{
    Q_OBJECT
public:
    explicit createevent(QWidget *parent = 0);
    virtual ~createevent();

	QString * m_p_username;
	QString * m_p_password;

	Q_SIGNAL void return_to_schedule();
private:
	Q_SLOT void on_pushButton_clicked();
	
    Ui::createevent * ui;
};
#endif
