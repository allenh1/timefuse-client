#include "user_event_thread.hpp"

user_event_thread::user_event_thread(QObject * _p_parent)
{
	m_p_thread = new QThread();
	
	m_p_response_mutex = new QMutex();
	m_p_username_mutex = new QMutex();
	m_p_password_mutex = new QMutex();
	m_p_month_mutex = new QMutex();
	m_p_year_mutex = new QMutex();

	m_p_response = new QString();
	m_p_username = new QString();
	m_p_password = new QString();
	m_p_month = new QString();
	m_p_year = new QString("2016");
}

user_event_thread::~user_event_thread()
{
	delete m_p_response_mutex; delete m_p_username_mutex;
	delete m_p_username; delete m_p_password_mutex;
	delete m_p_password; delete m_p_month_mutex;
	delete m_p_month; delete m_p_year_mutex;
	delete m_p_year; delete m_p_response;
	m_p_thread->requestInterruption(); m_p_thread->quit();
	delete m_p_thread;
}

bool user_event_thread::init()
{
	this->moveToThread(m_p_thread);
	connect(m_p_thread, &QThread::started, this, &user_event_thread::run);
	m_p_thread->start();
	return m_p_thread->isRunning();
}

void user_event_thread::run()
{
	for(;;m_p_thread->msleep(10000)) {
		*m_p_year = "2016";
		for (int x = 1; x <= 12; ++x) {
			QString * user_request = new QString("REQUEST_PERSONAL_MONTH_EVENTS ");

			(*user_request)+=*m_p_username; (*user_request)+=":::";
			(*user_request)+=*m_p_password; (*user_request)+=":::";
			(*user_request)+=QString::number(x); (*user_request)+=":::";
			(*user_request)+=*m_p_year; 

			delete m_p_response;
			m_p_response = setup_connection(user_request); delete user_request;
			QString temp = *m_p_response;
			Q_EMIT (value_changed(temp, x));
		}
	}
}

void user_event_thread::run_once()
{
	QString * user_request = new QString("REQUEST_PERSONAL_MONTH_EVENTS ");

	(*user_request)+=*m_p_username; (*user_request)+=":::";
	(*user_request)+=*m_p_password; (*user_request)+=":::";
	(*user_request)+=*m_p_month; (*user_request)+=":::";
	(*user_request)+=*m_p_year; 
	
	m_p_response = setup_connection(user_request); delete user_request;
}
