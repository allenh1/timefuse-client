/********************************************************************************
** Form generated from reading UI file 'acceptdenyfriendrequests.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCEPTDENYFRIENDREQUESTS_H
#define UI_ACCEPTDENYFRIENDREQUESTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_acceptdenyfriendrequests
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *acceptdenyfriendrequests)
    {
        if (acceptdenyfriendrequests->objectName().isEmpty())
            acceptdenyfriendrequests->setObjectName(QStringLiteral("acceptdenyfriendrequests"));
        acceptdenyfriendrequests->resize(400, 300);
        menuBar = new QMenuBar(acceptdenyfriendrequests);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        acceptdenyfriendrequests->setMenuBar(menuBar);
        mainToolBar = new QToolBar(acceptdenyfriendrequests);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        acceptdenyfriendrequests->addToolBar(mainToolBar);
        centralWidget = new QWidget(acceptdenyfriendrequests);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        acceptdenyfriendrequests->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(acceptdenyfriendrequests);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        acceptdenyfriendrequests->setStatusBar(statusBar);

        retranslateUi(acceptdenyfriendrequests);

        QMetaObject::connectSlotsByName(acceptdenyfriendrequests);
    } // setupUi

    void retranslateUi(QMainWindow *acceptdenyfriendrequests)
    {
        acceptdenyfriendrequests->setWindowTitle(QApplication::translate("acceptdenyfriendrequests", "acceptdenyfriendrequests", 0));
    } // retranslateUi

};

namespace Ui {
    class acceptdenyfriendrequests: public Ui_acceptdenyfriendrequests {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCEPTDENYFRIENDREQUESTS_H
