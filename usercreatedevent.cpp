#include "usercreatedevent.hpp"


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
    newString += timeNegotiable;

    return newString;
}
