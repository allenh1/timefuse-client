#include "create_account_window.hpp"

create_account_window::create_account_window(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::create_account_window)
{
    m_p_ui->setupUi(this);

	/* connect signals */
	connect(m_p_ui->cancel_button, &QPushButton::released,
			this, &create_account_window::cancel_pressed);
	connect(m_p_ui->create_button, &QPushButton::released,
			this, &create_account_window::create_pressed);
}

create_account_window::~create_account_window()
{
    delete m_p_ui;
}

void create_account_window::create_pressed()
{
	Q_EMIT(return_to_user_page());
}

void create_account_window::cancel_pressed()
{
	Q_EMIT(return_to_user_page());
}
