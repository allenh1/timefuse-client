#ifndef __USERCREATEDEVENT_HPP__
#define __USERCREATEDEVENT_HPP__
#include <QMainWindow>
#include <QDialog>
#include <QDebug>
#include <QTime>
#include <QFile>

#include "schedulinggrid.hpp"
#include "ui_schedulinggrid.h"
#include "createevent.hpp"

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
