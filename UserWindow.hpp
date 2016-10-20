

#ifndef UserWindow_hpp
#define UserWindow_hpp

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

#include "create_account_window.hpp"
#include "mainwindow.hpp"

class UserWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit UserWindow (QWidget *parent = 0);
    virtual ~UserWindow ();
    
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
    Q_SLOT void handleButton();
};

#endif /* UserWindow_hpp */
