#ifndef EDIT_GROUP_HPP
#define EDIT_GROUP_HPP

#include <QWidget>
#include <QListWidget>
#include <QMessageBox>
#include <iostream>

#include "tcp_connection.hpp"
#include "encrypt_string.hpp"
#include "ui_edit_group.h"

namespace Ui {
class edit_group;
}

class edit_group : public QWidget
{
    Q_OBJECT

public:
    explicit edit_group(QWidget *parent = 0);
    ~edit_group();

	QString * m_p_username;
	QString * m_p_password;
    QString * m_p_group;

	Q_SIGNAL void return_to_manage_groups();
    void fill_fields();
private:
    Ui::edit_group *ui;


	Q_SLOT void on_back_button();
	Q_SLOT void add_a_member();
};

#endif // ADD_GROUP_H
