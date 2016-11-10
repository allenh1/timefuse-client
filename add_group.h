#ifndef ADD_GROUP_HPP
#define ADD_GROUP_HPP

#include <QWidget>
#include <QListWidget>
#include <QMessageBox>
#include <iostream>
#include <QTest>

#include "tcp_connection.hpp"
#include "encrypt_string.hpp"
#include "ui_add_group.h"

namespace Ui {
class add_group;
}

class add_group : public QWidget
{
    Q_OBJECT

public:
    explicit add_group(QWidget *parent = 0);
    ~add_group();

	QString * m_p_username;
	QString * m_p_password;

	Q_SIGNAL void return_to_manage_groups();
private:
    Ui::add_group *ui;

	Q_SLOT void on_back_button();

	Q_SLOT void create_group();
	Q_SLOT void add_a_member();
	void add_user(QString user);
};

#endif // ADD_GROUP_H
