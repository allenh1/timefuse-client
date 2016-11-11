#ifndef RESET_PASSWORD_WINDOW_HPP
#define RESET_PASSWORD_WINDOW_HPP
#include <QMessageBox>
#include <QWidget>
#include <QtGui>

#include "ui_reset_password_window.h"
#include "tcp_connection.hpp"
#include "encrypt_string.hpp"
#include "user.hpp"

class user;

namespace Ui {
class reset_password_window;
}

class reset_password_window : public QWidget
{
    Q_OBJECT

public:
    explicit reset_password_window(QWidget * _p_parent = NULL);
    virtual ~reset_password_window();
    
    
    Q_SLOT void reset_pressed();
    Q_SLOT void cancel_pressed();
    
    Q_SIGNAL void send_create_account(user * u);
    Q_SIGNAL void return_to_user_page();

private:
    Ui::reset_password_window * m_p_ui;
};
#endif // RESET_PASSWORD_WINDOW_H
