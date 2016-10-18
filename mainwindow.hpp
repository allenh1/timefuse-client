#ifndef __MAINWINDOW_HPP__
#define __MAINWINDOW_HPP__
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

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    QPushButton *m_p_create_button; //create account
    QPushButton *m_p_login_button; //login
    QPushButton *m_p_reset_button;

    QVBoxLayout *mainLayout;
    QHBoxLayout *layout;
    QHBoxLayout *layout2;

    QLabel * m_p_user_label;
    QLabel * m_p_password_label;

    QLineEdit * m_p_user_edit;
    QLineEdit * m_p_password_edit;
  
    Q_SLOT void handleButton();
	void openNewWindow();
};
#endif // MAINWINDOW_H
