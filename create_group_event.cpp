#include "create_group_event.hpp"

create_group_event::create_group_event(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::create_group_event)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

    m_p_ui->user_to_add->setPlaceholderText(tr("Enter a group name"));
	m_p_ui->duration_input->setPlaceholderText(tr("in minutes"));
	m_p_ui->title_input->setPlaceholderText(tr("Group event name"));
	m_p_ui->location_input->setPlaceholderText(tr("Group event location"));
	
	connect(m_p_ui->cancel, &QPushButton::released,
			this, &create_group_event::on_cancel);    
}

create_group_event::~create_group_event()
{
    delete m_p_ui;
	delete m_p_username;
	delete m_p_password;
}

void create_group_event::on_cancel()
{
	m_p_ui->user_to_add->setText("");
	m_p_ui->title_input->setText("");
	m_p_ui->location_input->setText("");
	m_p_ui->duration_input->setText("");

	QTime def(0,0);
	m_p_ui->begin_time_edit->setTime(def);

	Q_EMIT(return_to_home_screen());
}


