/********************************************************************************
** Form generated from reading UI file 'home_screen.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_SCREEN_H
#define UI_HOME_SCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_home_screen
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *manage_groups;
    QPushButton *create_event;
    QPushButton *see_schedule;
    QPushButton *account_settings;
    QLabel *timefuse;

    void setupUi(QWidget *home_screen)
    {
        if (home_screen->objectName().isEmpty())
            home_screen->setObjectName(QStringLiteral("home_screen"));
        home_screen->resize(400, 300);
        gridLayoutWidget = new QWidget(home_screen);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 113, 311, 171));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        manage_groups = new QPushButton(gridLayoutWidget);
        manage_groups->setObjectName(QStringLiteral("manage_groups"));

        gridLayout->addWidget(manage_groups, 2, 0, 1, 1);

        create_event = new QPushButton(gridLayoutWidget);
        create_event->setObjectName(QStringLiteral("create_event"));

        gridLayout->addWidget(create_event, 1, 0, 1, 1);

        see_schedule = new QPushButton(gridLayoutWidget);
        see_schedule->setObjectName(QStringLiteral("see_schedule"));

        gridLayout->addWidget(see_schedule, 0, 0, 1, 1);

        account_settings = new QPushButton(home_screen);
        account_settings->setObjectName(QStringLiteral("account_settings"));
        account_settings->setGeometry(QRect(262, 60, 131, 41));
        timefuse = new QLabel(home_screen);
        timefuse->setObjectName(QStringLiteral("timefuse"));
        timefuse->setGeometry(QRect(110, 20, 211, 41));

        retranslateUi(home_screen);

        QMetaObject::connectSlotsByName(home_screen);
    } // setupUi

    void retranslateUi(QWidget *home_screen)
    {
        home_screen->setWindowTitle(QApplication::translate("home_screen", "Home", 0));
        manage_groups->setText(QApplication::translate("home_screen", "Manage Groups", 0));
        create_event->setText(QApplication::translate("home_screen", "Create Group Event", 0));
        see_schedule->setText(QApplication::translate("home_screen", "See My Schedule", 0));
        account_settings->setText(QApplication::translate("home_screen", "Account Settings", 0));
        timefuse->setText(QApplication::translate("home_screen", "               TIMEFUSE", 0));
    } // retranslateUi

};

namespace Ui {
    class home_screen: public Ui_home_screen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_SCREEN_H
