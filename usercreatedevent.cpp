#include "schedulinggrid.h"
#include "ui_schedulinggrid.h"
#include "createevent.h"
#include "usercreatedevent.h"


userCreatedEvent::userCreatedEvent()
{

//

}

void userCreatedEvent::toFile()
{

    //nvm this is actually impossible you can't return a QFile LMAO
}

QString userCreatedEvent::toString()
{
    QString newString;

    newString += name;
    newString += location;
    //newString += beginTime.toString("hhmmss");
    //newString += endTime.toString("hhmmss");
    newString += timeNegotiable;

    return newString;
}
