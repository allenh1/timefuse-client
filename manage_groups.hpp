#ifndef MANAGE_GROUPS_HPP
#define MANAGE_GROUPS_HPP

#include <QWidget>
#include "ui_manage_groups.h"

namespace Ui {
class manage_groups;
}

class manage_groups : public QWidget
{
    Q_OBJECT

public:
    explicit manage_groups(QWidget * _p_parent = NULL);
    virtual ~manage_groups();

	QString * m_p_username;
	QString * m_p_password;

	Q_SIGNAL void return_to_home_screen();
private:
    Ui::manage_groups * m_p_ui;

	Q_SLOT void on_back_button();
};

#endif
