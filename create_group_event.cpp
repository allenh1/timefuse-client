#include "create_group_event.hpp"

create_group_event::create_group_event(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::create_group_event)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

	connect(m_p_ui->cancel, &QPushButton::released,
			this, &create_group_event::on_cancel);
    
}

create_group_event::~create_group_event()
{
    delete m_p_ui;
}

void create_group_event::on_cancel()
{
	Q_EMIT(return_to_home_screen());
}


