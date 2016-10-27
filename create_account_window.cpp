#include "create_account_window.hpp"

create_account_window::create_account_window(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::create_account_window)
{
    m_p_ui->setupUi(this);
}

create_account_window::~create_account_window()
{
    delete m_p_ui;
}
