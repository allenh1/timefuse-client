#include "create_group_event.hpp"

create_group_event::create_group_event(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::create_group_event)
{
    m_p_ui->setupUi(this);
}

create_group_event::~create_group_event()
{
    delete m_p_ui;
}
