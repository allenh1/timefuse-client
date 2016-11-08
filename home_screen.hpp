#ifndef HOME_SCREEN_HPP
#define HOME_SCREEN_HPP
#pragma once
#include <QWidget>
#include <QtGui>

#include "ui_home_screen.h"
#include "schedulinggrid.h"
#include "createevent.h"

namespace Ui {
class home_screen;
}

class home_screen : public QWidget
{
    Q_OBJECT

public:
    explicit home_screen(QWidget *_p_parent = NULL);
    virtual ~home_screen();

	QString * m_p_username;
	QString * m_p_password;

	Q_SLOT void to_account_settings();
	Q_SLOT void to_see_schedule();
	Q_SLOT void to_manage_groups();
	Q_SLOT void to_create_event();

	Q_SLOT void from_create_event();
	Q_SLOT void from_see_schedule();
	Q_SLOT void from_manage_groups();
	Q_SLOT void from_account_settings();
private:
    Ui::home_screen *m_p_ui;

	schedulingGrid * m_p_schedule;
	createevent * m_p_create_event;
};
#endif
