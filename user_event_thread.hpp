#ifndef __USER_EVENT_THREAD_HPP__
#define __USER_EVENT_THREAD_HPP__
#include <iostream>
#include <QThread>
#include <QString>
#include <QMutex>

#include "tcp_connection.hpp"

class user_event_thread : public QObject
{
	Q_OBJECT
public:
	explicit user_event_thread(QObject * _p_parent = NULL);
	virtual ~user_event_thread();

	bool init();
	
	Q_SLOT void run();
	Q_SLOT void run_once();

	const bool & isRunning() { return m_p_thread->isRunning(); };
	void quit() { m_p_thread->quit(); };
	void requestInterruption() { m_p_thread->requestInterruption(); };
	
	QString get_response() {
		QString temp;
		m_p_response_mutex->lock();
		temp = *m_p_response;
		m_p_response_mutex->unlock();
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
	
	Q_SLOT void set_year(QString year) {
		m_p_year_mutex->lock();
		(*m_p_year)=year;
		m_p_year_mutex->unlock();
	};

	Q_SIGNAL void value_changed(QString, int);
private:
	QThread * m_p_thread;
	QMutex * m_p_response_mutex;
	QString * m_p_response;

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
