#include "home_screen.hpp"
#include "ui_home_screen.h"

home_screen::home_screen(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::home_screen)
{
    m_p_ui->setupUi(this);
}

home_screen::~home_screen()
{
    delete m_p_ui;
}
