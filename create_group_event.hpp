#ifndef CREATE_GROUP_EVENT_HPP
#define CREATE_GROUP_EVENT_HPP

#include <QWidget>
#include <QTimeEdit>
#include <QTime>

#include "ui_create_group_event.h"

namespace Ui {
class create_group_event;
}

class create_group_event : public QWidget
{
    Q_OBJECT

public:
    explicit create_group_event(QWidget * _p_parent = NULL);
    virtual ~create_group_event();

	QString * m_p_username;
	QString * m_p_password;

	Q_SIGNAL void return_to_home_screen();

	Q_SLOT void on_cancel();
private:
    Ui::create_group_event * m_p_ui;
};

#endif 
