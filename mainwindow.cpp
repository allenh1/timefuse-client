#include "mainwindow.h"

#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the button, make "this" the parent
    m_button = new QPushButton("Create Account", this);
    l_button = new QPushButton("Login", this);

    //  to set size and location of the button
    m_button->setGeometry(QRect(QPoint(650, 500), QSize(200, 50)));
    l_button->setGeometry(QRect(QPoint(650, 550), QSize(200, 50)));


    // Connect button signal to appropriate slot
    connect(m_button, SIGNAL (released()), this, SLOT (handleButton()));
    connect(l_button, SIGNAL (released()), this, SLOT (handleButton()));

}

void MainWindow::handleButton()
{
    // to change the text of the buttons
    m_button->setText("Create Account");
    l_button->setText("Login");
    // to resize buttons on clicking
    m_button->resize(200,50);
    l_button->resize(200,50);

}

void LineEdit::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu *menu = createStandardContextMenu();
    menu->addAction(tr("My Menu Item"));
    //...
    menu->exec(event->globalPos());
    delete menu;
}
