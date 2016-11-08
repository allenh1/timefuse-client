#include "manage_groups.hpp"


manage_groups::manage_groups(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::manage_groups)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

	m_p_add_group = new add_group();

	connect(m_p_ui->back_button, &QPushButton::released,
			this, &manage_groups::on_back_button);
	connect(m_p_ui->create_new_group, &QPushButton::released,
			this, &manage_groups::on_new_group);
	connect(m_p_add_group, &add_group::return_to_manage_groups,
			this, &manage_groups::show_manage_groups);
}

manage_groups::~manage_groups()
{
    delete m_p_ui;
}

void manage_groups::on_back_button()
{
	Q_EMIT(return_to_home_screen());
}

void manage_groups::on_new_group()
{
	m_p_add_group->m_p_username = m_p_username;
	m_p_add_group->m_p_password = m_p_password;
	
	this->hide();
	m_p_add_group->show();
}

void manage_groups::show_manage_groups() {
	m_p_add_group->hide();
	this->show();
}
