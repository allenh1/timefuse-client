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

void group_event_thread::run() {
	for(;;m_p_thread->msleep(3000)) {
		run_method();
	}
}

void group_event_thread::run_once(QString month, QString year) {
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
		(*group_request)+=month; (*group_request)+=":::";
		(*group_request)+=year + ":::" + list[x] + "\r\n\0";
		QString * group_response = setup_connection(group_request);
		if(group_response->contains("ERROR")) continue;
		group_occupied_days = group_occupied_days |
			((uint) group_response->split("\n")[0].toInt());
		delete group_request, delete group_response;
	} if(m_occupied_days != group_occupied_days) {
		m_occupied_days = group_occupied_days;
	} delete get_group_response; delete get_groups;
	uint temp = m_occupied_days;
	std::cerr<<"group event: "<<temp<<"\tmonth: "<<month.toInt()<<
		"\tyear: "<<year.toInt()<<std::endl;
	QString date = month+":"+year;
	Q_EMIT(value_changed(date, temp));
}

void group_event_thread::run_method()
{
	int m = m_p_month->toInt();
	int y = m_p_year->toInt();
	run_once(QString::number(m), QString::number(y));
	for(int i=1; i < 7; ++i) {
		if(i < m) {
			run_once(QString::number(m-i), QString::number(y));
		} else if((m-i) <= 0){
			run_once(QString::number(12+(m-i)), QString::number(y-1));
		} if((m+i) > 12) {
			run_once(QString::number((m+i)%12), QString::number(y+1));
		} else if((m+i) <= 12) {
			run_once(QString::number(m+i), QString::number(y));
		}
	}
}


