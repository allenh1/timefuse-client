#include "home_screen.hpp"

home_screen::home_screen(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::home_screen)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

	m_p_schedule = new schedulingGrid();
	m_p_create_event = new createevent();
	m_p_account_settings = new account_settings();

	// connections to different windows
	connect(m_p_ui->create_event, &QPushButton::released,
			this, &home_screen::to_create_event);
	connect(m_p_ui->see_schedule, &QPushButton::released,
			this, &home_screen::to_see_schedule);
	connect(m_p_ui->account_settings, &QPushButton::released,
			this, &home_screen::to_account_settings);

	// connections from different windows
	connect(m_p_account_settings, &account_settings::return_to_home_screen,
			this, &home_screen::from_account_settings);
}

home_screen::~home_screen()
{
    delete m_p_ui;
}


void home_screen::to_account_settings()
{
	/**
	 * @TODO add request for account info
	 */
	m_p_account_settings->m_p_username = m_p_username;
	m_p_account_settings->m_p_password = m_p_password;
	
	m_p_account_settings->show();
	this->hide();
}

void home_screen::to_see_schedule()
{
	/**
	 * @TODO add request for user's schedule
	 */
	m_p_schedule->m_p_username = m_p_username;
	m_p_schedule->m_p_password = m_p_password;
	
	m_p_schedule->show();
	this->hide();
}

void home_screen::to_manage_groups()
{
	/**
	 * @TODO add request for user's schedule
	 */
}

void home_screen::to_create_event()
{
	/**
	 * @TODO add request to add event
	 */
	m_p_create_event->m_p_username = m_p_username;
	m_p_create_event->m_p_password = m_p_password;
	
	m_p_create_event->show();
	this->hide();
}

void home_screen::from_create_event()
{
	m_p_create_event->hide();
	this->show();
}

void home_screen::from_see_schedule()
{
	m_p_schedule->hide();
	this->show();
}

void home_screen::from_manage_groups()
{
	this->show();
}

void home_screen::from_account_settings()
{
	this->show();
	m_p_account_settings->hide();
}
