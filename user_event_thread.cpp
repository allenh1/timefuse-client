#include "user_event_thread.hpp"

user_event_thread::user_event_thread(QObject * _p_parent = NULL) {
	m_p_thread = new QThread();
	
	m_p_occupied_mutex = new QMutex();
	m_p_username_mutex = new QMutex();
	m_p_password_mutex = new QMutex();
	m_p_month_mutex = new QMutex();
	m_p_year_mutex = new QMutex();

	m_p_response = new QString();
	m_p_username = new QString();
	m_p_password = new QString();
	m_p_month = new QString();
	m_p_year = new QString();
}

user_event_thread::~user_event_thread() {
	delete m_p_occupied_mutex; delete m_p_username_mutex;
	delete m_p_username; delete m_p_password_mutex;
	delete m_p_password; delete m_p_month_mutex;
	delete m_p_month; delete m_p_year_mutex;
	delete m_p_year;
}

bool user_event::init() {
	this->moveToThread(m_p_thread);
	connect(m_p_thread, &QThread::started, this, &user_event_thread::run);
	m_p_thread->start();
	return m_p_thread->isRunning();
}

user_event_thread::run() {
	QString * user_request = new QString("REQUEST_PERSONAL_MONTH_EVENTS ");
    (*user_request)+=m_p_username; (*user_request)+=":::";
    (*user_request)+=m_p_password; (*user_request)+=":::";
    (*user_request)+=ui->lineMonth->displayText(); (*user_request)+=":::";
    (*user_request)+=ui->lineYear->displayText(); 
    m_p_response = setup_connection(user_request);
}
