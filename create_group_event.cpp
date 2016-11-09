#include "create_group_event.hpp"

create_group_event::create_group_event(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::create_group_event)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

	m_p_ui->user_to_add->setPlaceholderText(tr("Username, Email, or Phone Number"));
	
	connect(m_p_ui->cancel, &QPushButton::released,
			this, &create_group_event::on_cancel);    
}

create_group_event::~create_group_event()
{
    delete m_p_ui;
}

void create_group_event::on_cancel()
{
	m_p_ui->user_to_add->setText("");
	m_p_ui->title_input->setText("");
	m_p_ui->location_input->setText("");
	
	Q_EMIT(return_to_home_screen());
}


