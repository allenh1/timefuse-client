#ifndef CREATE_GROUP_EVENT_HPP
#define CREATE_GROUP_EVENT_HPP

#include <QWidget>

#include "ui_create_group_event.h"

namespace Ui {
class create_group_event;
}

class create_group_event : public QWidget
{
    Q_OBJECT

public:
    explicit create_group_event(QWidget * _p_parent = NULL);
    virtual ~create_group_event();

private:
    Ui::create_group_event * m_p_ui;
};

#endif 
