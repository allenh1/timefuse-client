#include "reset_password_window.hpp"
//#include "ui_reset_password_window.hpp"

reset_password_window::reset_password_window(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::reset_password_window)
{
    m_p_ui->setupUi(this);
    
    
    /* connect signals */
    connect(m_p_ui->cancel_button, &QPushButton::released,
            this, &reset_password_window::cancel_pressed);
    connect(m_p_ui->reset_button, &QPushButton::released,
            this, &reset_password_window::reset_pressed);

}

reset_password_window::~reset_password_window()
{
    delete m_p_ui;
}

void reset_password_window::reset_pressed()
{
    Q_EMIT(return_to_user_page());
}


void reset_password_window::cancel_pressed()
{
    Q_EMIT(return_to_user_page());
}
