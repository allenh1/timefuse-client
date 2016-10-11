#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QApplication>
#include <QObject>

namespace Ui {
    class MainWindow;


}

class MainWindow : public QMainWindow
{


    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

private:
    QPushButton *m_p_create_button; //create account
    QPushButton *m_p_login_button; //login

    Q_SLOT void handleButton();

};


#endif // MAINWINDOW_H
