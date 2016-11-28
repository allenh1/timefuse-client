#ifndef FRIENDS_LIST_HPP
#define FRIENDS_LIST_HPP

#include <QStringList>
#include <QWidget>
#include <QTest>
#include "ui_friends_list.h"
#include "add_group.h"
#include "edit_group.hpp"

namespace Ui {
class friends_list;
}

class friends_list : public QWidget
{
    Q_OBJECT

public:
    explicit friends_list(QWidget * _p_parent = NULL);
    virtual ~friends_list();

	QString * m_p_username;
	QString * m_p_password;

	Q_SIGNAL void return_to_home_screen();
    void fill_fields();
private:
    Ui::friends_list * m_p_ui;
	
    Q_SLOT void on_delete_friend();

    Q_SLOT void on_add_friend();
    Q_SLOT void on_back_button();
	Q_SLOT void goto_friend_requests();
};

#endif
