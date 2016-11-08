#include "manage_groups.hpp"
#include "ui_manage_groups.h"

manage_groups::manage_groups(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::manage_groups)
{
    m_p_ui->setupUi(this);
}

manage_groups::~manage_groups()
{
    delete m_p_ui;
}
