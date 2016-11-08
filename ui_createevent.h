/********************************************************************************
** Form generated from reading UI file 'createevent.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CREATEEVENT_H
#define UI_CREATEEVENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTimeEdit>

QT_BEGIN_NAMESPACE

class Ui_createevent
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *lineTitle;
    QLineEdit *lineLocation;
    QPushButton *pushButton;
    QGroupBox *groupBox;
    QRadioButton *radioFixed;
    QRadioButton *radioButton_2;
    QLabel *labelText;
    QTimeEdit *timeBegin;
    QTimeEdit *timeEnd;

    void setupUi(QDialog *createevent)
    {
        if (createevent->objectName().isEmpty())
            createevent->setObjectName(QStringLiteral("createevent"));
        createevent->resize(400, 300);
        label = new QLabel(createevent);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 381, 16));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(createevent);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 50, 71, 16));
        label_3 = new QLabel(createevent);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 90, 71, 16));
        label_4 = new QLabel(createevent);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 130, 71, 16));
        label_5 = new QLabel(createevent);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 170, 71, 16));
        lineTitle = new QLineEdit(createevent);
        lineTitle->setObjectName(QStringLiteral("lineTitle"));
        lineTitle->setGeometry(QRect(90, 50, 113, 20));
        lineLocation = new QLineEdit(createevent);
        lineLocation->setObjectName(QStringLiteral("lineLocation"));
        lineLocation->setGeometry(QRect(90, 90, 113, 20));
        pushButton = new QPushButton(createevent);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 242, 381, 51));
        groupBox = new QGroupBox(createevent);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(250, 60, 120, 80));
        radioFixed = new QRadioButton(groupBox);
        radioFixed->setObjectName(QStringLiteral("radioFixed"));
        radioFixed->setGeometry(QRect(10, 20, 82, 17));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 50, 82, 17));
        labelText = new QLabel(createevent);
        labelText->setObjectName(QStringLiteral("labelText"));
        labelText->setGeometry(QRect(260, 170, 121, 61));
        labelText->setScaledContents(false);
        labelText->setWordWrap(true);
        timeBegin = new QTimeEdit(createevent);
        timeBegin->setObjectName(QStringLiteral("timeBegin"));
        timeBegin->setGeometry(QRect(90, 130, 111, 22));
        timeEnd = new QTimeEdit(createevent);
        timeEnd->setObjectName(QStringLiteral("timeEnd"));
        timeEnd->setGeometry(QRect(90, 170, 111, 22));

        retranslateUi(createevent);

        QMetaObject::connectSlotsByName(createevent);
    } // setupUi

    void retranslateUi(QDialog *createevent)
    {
        createevent->setWindowTitle(QApplication::translate("createevent", "Dialog", 0));
        label->setText(QApplication::translate("createevent", "Creating a Personal Event", 0));
        label_2->setText(QApplication::translate("createevent", "Title:", 0));
        label_3->setText(QApplication::translate("createevent", "Location:", 0));
        label_4->setText(QApplication::translate("createevent", "Begin Time:", 0));
        label_5->setText(QApplication::translate("createevent", "End Time:", 0));
        pushButton->setText(QApplication::translate("createevent", "Create Event", 0));
        groupBox->setTitle(QApplication::translate("createevent", "This event time is...", 0));
        radioFixed->setText(QApplication::translate("createevent", "Fixed", 0));
        radioButton_2->setText(QApplication::translate("createevent", "Negotiable", 0));
        labelText->setText(QApplication::translate("createevent", "huh", 0));
    } // retranslateUi

};

namespace Ui {
    class createevent: public Ui_createevent {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CREATEEVENT_H
