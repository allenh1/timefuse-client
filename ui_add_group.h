/********************************************************************************
** Form generated from reading UI file 'add_group.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_GROUP_H
#define UI_ADD_GROUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_add_group
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;
    QScrollArea *participants;
    QWidget *scrollAreaWidgetContents;
    QScrollBar *verticalScrollBar;

    void setupUi(QWidget *add_group)
    {
        if (add_group->objectName().isEmpty())
            add_group->setObjectName(QStringLiteral("add_group"));
        add_group->resize(400, 300);
        gridLayoutWidget = new QWidget(add_group);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(90, 50, 231, 151));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        participants = new QScrollArea(gridLayoutWidget);
        participants->setObjectName(QStringLiteral("participants"));
        participants->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 113, 116));
        verticalScrollBar = new QScrollBar(scrollAreaWidgetContents);
        verticalScrollBar->setObjectName(QStringLiteral("verticalScrollBar"));
        verticalScrollBar->setGeometry(QRect(100, 0, 16, 160));
        verticalScrollBar->setOrientation(Qt::Vertical);
        participants->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(participants, 2, 1, 1, 1);


        retranslateUi(add_group);

        QMetaObject::connectSlotsByName(add_group);
    } // setupUi

    void retranslateUi(QWidget *add_group)
    {
        add_group->setWindowTitle(QApplication::translate("add_group", "Add Group", 0));
        label->setText(QApplication::translate("add_group", "Group Subject:", 0));
        label_2->setText(QApplication::translate("add_group", "Add participants:", 0));
    } // retranslateUi

};

namespace Ui {
    class add_group: public Ui_add_group {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_GROUP_H
