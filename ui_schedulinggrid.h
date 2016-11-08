/********************************************************************************
** Form generated from reading UI file 'schedulinggrid.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULINGGRID_H
#define UI_SCHEDULINGGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_schedulingGrid
{
public:
    QWidget *centralWidget;
    QTableWidget *tableCalendar;
    QLabel *label_3;
    QPushButton *pushCalendar;
    QLineEdit *lineMonth;
    QLineEdit *lineYear;
    QLabel *label_4;
    QLabel *label;
    QPushButton *pushLeft;
    QPushButton *pushRight;
    QLabel *labelCurrentDay;
    QPushButton *pushGetDay;
    QTableWidget *tableWeek;
    QPushButton *pushWeek;
    QPushButton *pushCreateEvent;
    QListView *listView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *schedulingGrid)
    {
        if (schedulingGrid->objectName().isEmpty())
            schedulingGrid->setObjectName(QStringLiteral("schedulingGrid"));
        schedulingGrid->resize(836, 506);
        schedulingGrid->setAutoFillBackground(false);
        centralWidget = new QWidget(schedulingGrid);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableCalendar = new QTableWidget(centralWidget);
        if (tableCalendar->columnCount() < 7)
            tableCalendar->setColumnCount(7);
        if (tableCalendar->rowCount() < 6)
            tableCalendar->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableCalendar->setItem(1, 0, __qtablewidgetitem);
        tableCalendar->setObjectName(QStringLiteral("tableCalendar"));
        tableCalendar->setGeometry(QRect(450, 40, 350, 240));
        tableCalendar->setFrameShape(QFrame::NoFrame);
        tableCalendar->setLineWidth(1);
        tableCalendar->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableCalendar->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableCalendar->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableCalendar->setAutoScroll(true);
        tableCalendar->setAutoScrollMargin(16);
        tableCalendar->setDragDropMode(QAbstractItemView::NoDragDrop);
        tableCalendar->setAlternatingRowColors(false);
        tableCalendar->setSelectionMode(QAbstractItemView::SingleSelection);
        tableCalendar->setTextElideMode(Qt::ElideLeft);
        tableCalendar->setShowGrid(true);
        tableCalendar->setGridStyle(Qt::SolidLine);
        tableCalendar->setCornerButtonEnabled(true);
        tableCalendar->setRowCount(6);
        tableCalendar->setColumnCount(7);
        tableCalendar->horizontalHeader()->setVisible(false);
        tableCalendar->horizontalHeader()->setCascadingSectionResizes(true);
        tableCalendar->horizontalHeader()->setDefaultSectionSize(50);
        tableCalendar->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableCalendar->horizontalHeader()->setStretchLastSection(true);
        tableCalendar->verticalHeader()->setVisible(false);
        tableCalendar->verticalHeader()->setDefaultSectionSize(40);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 40, 47, 21));
        label_3->setAlignment(Qt::AlignCenter);
        pushCalendar = new QPushButton(centralWidget);
        pushCalendar->setObjectName(QStringLiteral("pushCalendar"));
        pushCalendar->setGeometry(QRect(180, 10, 101, 51));
        lineMonth = new QLineEdit(centralWidget);
        lineMonth->setObjectName(QStringLiteral("lineMonth"));
        lineMonth->setGeometry(QRect(60, 10, 113, 20));
        lineYear = new QLineEdit(centralWidget);
        lineYear->setObjectName(QStringLiteral("lineYear"));
        lineYear->setGeometry(QRect(60, 40, 113, 20));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 10, 47, 21));
        label_4->setAlignment(Qt::AlignCenter);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(500, 10, 251, 20));
        label->setAlignment(Qt::AlignCenter);
        pushLeft = new QPushButton(centralWidget);
        pushLeft->setObjectName(QStringLiteral("pushLeft"));
        pushLeft->setGeometry(QRect(450, 10, 51, 23));
        pushRight = new QPushButton(centralWidget);
        pushRight->setObjectName(QStringLiteral("pushRight"));
        pushRight->setGeometry(QRect(750, 10, 51, 23));
        labelCurrentDay = new QLabel(centralWidget);
        labelCurrentDay->setObjectName(QStringLiteral("labelCurrentDay"));
        labelCurrentDay->setGeometry(QRect(90, 80, 221, 21));
        pushGetDay = new QPushButton(centralWidget);
        pushGetDay->setObjectName(QStringLiteral("pushGetDay"));
        pushGetDay->setGeometry(QRect(10, 80, 75, 23));
        tableWeek = new QTableWidget(centralWidget);
        if (tableWeek->columnCount() < 7)
            tableWeek->setColumnCount(7);
        if (tableWeek->rowCount() < 24)
            tableWeek->setRowCount(24);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWeek->setItem(1, 0, __qtablewidgetitem1);
        tableWeek->setObjectName(QStringLiteral("tableWeek"));
        tableWeek->setGeometry(QRect(10, 110, 371, 311));
        tableWeek->setFrameShape(QFrame::NoFrame);
        tableWeek->setFrameShadow(QFrame::Plain);
        tableWeek->setLineWidth(1);
        tableWeek->setMidLineWidth(1);
        tableWeek->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        tableWeek->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableWeek->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        tableWeek->setAutoScroll(true);
        tableWeek->setAutoScrollMargin(16);
        tableWeek->setDragDropMode(QAbstractItemView::NoDragDrop);
        tableWeek->setAlternatingRowColors(true);
        tableWeek->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWeek->setTextElideMode(Qt::ElideLeft);
        tableWeek->setShowGrid(true);
        tableWeek->setGridStyle(Qt::SolidLine);
        tableWeek->setCornerButtonEnabled(true);
        tableWeek->setRowCount(24);
        tableWeek->setColumnCount(7);
        tableWeek->horizontalHeader()->setVisible(true);
        tableWeek->horizontalHeader()->setCascadingSectionResizes(true);
        tableWeek->horizontalHeader()->setDefaultSectionSize(50);
        tableWeek->horizontalHeader()->setHighlightSections(true);
        tableWeek->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableWeek->horizontalHeader()->setStretchLastSection(true);
        tableWeek->verticalHeader()->setVisible(true);
        tableWeek->verticalHeader()->setCascadingSectionResizes(false);
        tableWeek->verticalHeader()->setDefaultSectionSize(40);
        pushWeek = new QPushButton(centralWidget);
        pushWeek->setObjectName(QStringLiteral("pushWeek"));
        pushWeek->setGeometry(QRect(314, 80, 91, 23));
        pushCreateEvent = new QPushButton(centralWidget);
        pushCreateEvent->setObjectName(QStringLiteral("pushCreateEvent"));
        pushCreateEvent->setGeometry(QRect(450, 290, 351, 23));
        listView = new QListView(centralWidget);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(450, 320, 351, 131));
        schedulingGrid->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(schedulingGrid);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 836, 21));
        schedulingGrid->setMenuBar(menuBar);
        mainToolBar = new QToolBar(schedulingGrid);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        schedulingGrid->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(schedulingGrid);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        schedulingGrid->setStatusBar(statusBar);

        retranslateUi(schedulingGrid);

        QMetaObject::connectSlotsByName(schedulingGrid);
    } // setupUi

    void retranslateUi(QMainWindow *schedulingGrid)
    {
        schedulingGrid->setWindowTitle(QApplication::translate("schedulingGrid", "schedulingGrid", 0));

        const bool __sortingEnabled = tableCalendar->isSortingEnabled();
        tableCalendar->setSortingEnabled(false);
        tableCalendar->setSortingEnabled(__sortingEnabled);

        label_3->setText(QApplication::translate("schedulingGrid", "Year:", 0));
        pushCalendar->setText(QApplication::translate("schedulingGrid", "Display Calendar", 0));
        lineMonth->setText(QApplication::translate("schedulingGrid", "11", 0));
        lineYear->setText(QApplication::translate("schedulingGrid", "2016", 0));
        label_4->setText(QApplication::translate("schedulingGrid", "Month:", 0));
        label->setText(QApplication::translate("schedulingGrid", "TextLabel", 0));
        pushLeft->setText(QApplication::translate("schedulingGrid", "<", 0));
        pushRight->setText(QApplication::translate("schedulingGrid", ">", 0));
        labelCurrentDay->setText(QApplication::translate("schedulingGrid", "//", 0));
        pushGetDay->setText(QApplication::translate("schedulingGrid", "Get Time", 0));

        const bool __sortingEnabled1 = tableWeek->isSortingEnabled();
        tableWeek->setSortingEnabled(false);
        tableWeek->setSortingEnabled(__sortingEnabled1);

#ifndef QT_NO_WHATSTHIS
        tableWeek->setWhatsThis(QApplication::translate("schedulingGrid", "0w0", 0));
#endif // QT_NO_WHATSTHIS
        pushWeek->setText(QApplication::translate("schedulingGrid", "Generate Week", 0));
        pushCreateEvent->setText(QApplication::translate("schedulingGrid", "Create Event", 0));
    } // retranslateUi

};

namespace Ui {
    class schedulingGrid: public Ui_schedulingGrid {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULINGGRID_H
