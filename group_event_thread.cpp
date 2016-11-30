#include "group_event_thread.hpp"

group_event_thread::group_event_thread(QObject * _p_parent) {
	m_p_thread = new QThread();
	
	m_p_occupied_mutex = new QMutex();
	m_p_username_mutex = new QMutex();
	m_p_password_mutex = new QMutex();
	m_p_month_mutex = new QMutex();
	m_p_year_mutex = new QMutex();

	m_p_username = new QString();
	m_p_password = new QString();
	m_p_month = new QString();
	m_p_year = new QString();
}

group_event_thread::~group_event_thread() {
	delete m_p_occupied_mutex; delete m_p_username_mutex;
	delete m_p_username; delete m_p_password_mutex;
	delete m_p_password; delete m_p_month_mutex;
	delete m_p_month; delete m_p_year_mutex;
	delete m_p_year; m_p_thread->requestInterruption();
	m_p_thread->quit();
}

bool group_event_thread::init() {
	this->moveToThread(m_p_thread);
	connect(m_p_thread, &QThread::started, this, &group_event_thread::run);
	m_p_thread->start();
	return m_p_thread->isRunning();
}

int group_event_thread::run() {
	QString * get_groups = new QString("REQUEST_GROUPS ");
	*get_groups += *m_p_username + ":::" + *m_p_password + "\r\n\0";

	/* split along the '\n' character */
	QString * get_group_response = setup_connection(get_groups);
	QStringList list = get_group_response->split("\n");
	
	/* prepare these values to be colored */	
	uint group_occupied_days = 0;

	/* ask for (every) group in the selected month */
	for (size_t x = 0; x < list.size(); ++x) {
		/* send the current group's select query */
		QString * group_request = new QString("REQUEST_GROUP_MONTH_EVENTS ");
		(*group_request)+=*m_p_username;  (*group_request)+=":::";
		(*group_request)+=*m_p_password;  (*group_request)+=":::";
		(*group_request)+=*m_p_month;	(*group_request)+=":::";
		(*group_request)+=*m_p_year + ":::" + list[x] + "\r\n\0";
		QString * group_response = setup_connection(group_request);
		group_occupied_days = group_occupied_days |
			((uint) group_response->split("\n")[0].toInt());
		delete group_request, delete group_response;
	} m_occupied_days = group_occupied_days;
	return 1;
}
