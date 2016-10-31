/********************************************************************************
** Form generated from reading UI file 'reset_password_window.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESET_PASSWORD_WINDOW_H
#define UI_RESET_PASSWORD_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_reset_password_window
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QPushButton *reset_button;
    QPushButton *cancel_button;

    void setupUi(QWidget *reset_password_window)
    {
        if (reset_password_window->objectName().isEmpty())
            reset_password_window->setObjectName(QStringLiteral("reset_password_window"));
        reset_password_window->resize(510, 374);
        gridLayoutWidget = new QWidget(reset_password_window);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(80, 50, 341, 181));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_2 = new QLineEdit(gridLayoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        reset_button = new QPushButton(reset_password_window);
        reset_button->setObjectName(QStringLiteral("reset_button"));
        reset_button->setGeometry(QRect(100, 270, 113, 32));
        cancel_button = new QPushButton(reset_password_window);
        cancel_button->setObjectName(QStringLiteral("cancel_button"));
        cancel_button->setGeometry(QRect(300, 270, 113, 32));
        gridLayoutWidget->raise();
        lineEdit->raise();
        reset_button->raise();
        cancel_button->raise();

        retranslateUi(reset_password_window);

        QMetaObject::connectSlotsByName(reset_password_window);
    } // setupUi

    void retranslateUi(QWidget *reset_password_window)
    {
        reset_password_window->setWindowTitle(QApplication::translate("reset_password_window", "Reset Password", 0));
        label_2->setText(QApplication::translate("reset_password_window", "Username:", 0));
        label_3->setText(QApplication::translate("reset_password_window", "Email:", 0));
        reset_button->setText(QApplication::translate("reset_password_window", "Reset", 0));
        cancel_button->setText(QApplication::translate("reset_password_window", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class reset_password_window: public Ui_reset_password_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESET_PASSWORD_WINDOW_H
