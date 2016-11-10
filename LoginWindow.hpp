#ifndef __LOGIN_WINDOW_HPP__
#define __LOGIN_WINDOW_HPP__
#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QtCore>
#include <QtGui>
#include <QTextEdit>
#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <iostream>
#include <QCryptographicHash>

#include "create_account_window.hpp"
#include "reset_password_window.hpp"
#include "tcp_connection.hpp"
#include "encrypt_string.hpp"
#include "home_screen.hpp"

class reset_password_window;

class LoginWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit LoginWindow (QWidget *parent = 0);
    virtual ~LoginWindow ();

    Q_SLOT void open_create_window();
    Q_SLOT void open_reset_password_window();
    Q_SLOT void hide_create();
    Q_SLOT void hide_reset();
    Q_SIGNAL void do_login(QString, QString);

	Q_SLOT void hide_home_screen();
private:
    QPushButton *m_p_create_button; //create account
    QPushButton *m_p_login_button; //login
    QPushButton *m_p_reset_button;
    
    QVBoxLayout * m_p_main_layout;
    QHBoxLayout * m_p_name_layout;
    QHBoxLayout * m_p_password_layout;
    QHBoxLayout * m_p_button_layout;
    
    QLabel * m_p_user_label;
    QLabel * m_p_password_label;
    
    QLineEdit * m_p_user_edit;
    QLineEdit * m_p_password_edit;
    
    QString m_name;
    QString m_password;
    
    create_account_window * m_p_create_account_window;
    reset_password_window * m_p_reset_password_window;
	home_screen * m_p_home_screen;
    
    Q_SLOT void handleButton();
    Q_SLOT void login(QString username, QString password);
};

#endif /* LoginWindow_hpp */
