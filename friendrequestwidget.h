#ifndef __ACCEPTDENYFRIENDREQUESTS_HPP__
#define __ACCEPTDENYFRIENDREQUESTS_HPP__

#include <QWidget>

class QFrame;
 class QLabel;
 class ElideLabel;
 class QPushButton;
 class QToolButton;
 class QMenu;
 class QPropertyAnimation;

 class FriendRequestWidget : public QWidget
 {
     Q_OBJECT

 private slots:
     void acceptUser();
     void rejectUser();
     void showDetails(bool show);
     void nextRequest();

 private:
    QToolButton *button;
    QMenu       *menu;
    QWidget     *actionDefaultWidget;
    //QPushButton *button;
    QFrame      *detailsWidget;
    ElideLabel  *clientId;
    QLabel      *message;
    QPushButton *accaptButton;
    QPushButton *acceptButton;
     QPushButton *rejectButton;
    QPushButton *nextButton;

    QPropertyAnimation *animation;

     QHash<QString, QString> requests;
     QMutableHashIterator<QString, QString> it;

     void updateGui();
    void goFirst();
 };

 #endif
