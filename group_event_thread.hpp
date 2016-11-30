#ifndef __GROUP_EVENT_THREAD_HPP__
#define __GROUP_EVENT_THREAD_HPP__
#include <iostream>
#include <QThread>
#include <QString>
#include <QMutex>

#include "tcp_connection.hpp"

typedef unsigned int uint;

class group_event_thread : public QObject
{
	Q_OBJECT
public:
	explicit group_event_thread(QObject * _p_parent = NULL);
	virtual ~group_event_thread();

	bool init();

	Q_SLOT int run();

	uint get_occupied_days() {
		register uint temp = 0;
		m_p_occupied_mutex->lock();
		temp = m_occupied_days;
		m_p_occupied_mutex->unlock();
		return temp;
	};

	void set_username(const QString & username) {
		m_p_username_mutex->lock();
		(*m_p_username)=username;
		m_p_username_mutex->unlock();
	};
	
	void set_password(const QString & password) {
		m_p_password_mutex->lock();
		(*m_p_password)=password;
		m_p_password_mutex->unlock();
	};
	
	void set_month(const QString & month) {
		m_p_month_mutex->lock();
		(*m_p_month)=month;
		m_p_month_mutex->unlock();
	};
	
	void set_year(const QString & year) {
		m_p_year_mutex->lock();
		(*m_p_year)=year;
		m_p_year_mutex->unlock();
	};
	
private:
	QThread * m_p_thread;
	QMutex * m_p_occupied_mutex;
	uint m_occupied_days;

	QMutex * m_p_username_mutex;
	QString * m_p_username;

	QMutex * m_p_password_mutex;
	QString * m_p_password;

	QMutex * m_p_month_mutex;
	QString * m_p_month;

	QMutex * m_p_year_mutex;
	QString * m_p_year;
};

#endif
