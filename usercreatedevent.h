#ifndef USERCREATEDEVENT_H
#define USERCREATEDEVENT_H

#include <QMainWindow>
#include <QTime>
#include <QDialog>
#include <QDebug>
#include <QFile>

class userCreatedEvent
{
public:
    userCreatedEvent();
    QString name, location;
    QTime beginTime, endTime;
    bool timeNegotiable;

    void toFile();
    QString toString();
};

#endif // USERCREATEDEVENT_H
