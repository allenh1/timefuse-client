#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QApplication>
#include <QObject>
#include <QTextFrame>
#include <QtGui>
#include <QtCore>
#include <QGridLayout>
#include <QTextEdit>


namespace Ui {
    class MainWindow;


}

class MainWindow : public QMainWindow
{


    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    QLabel *name;
    QLabel *password;
    QLineEdit *text_name;
    QLineEdit *text_pswd;

private:
    QPushButton *m_p_create_button; //create account
    QPushButton *m_p_login_button; //login



    Q_SLOT void handleButton();

};


#endif // MAINWINDOW_H
