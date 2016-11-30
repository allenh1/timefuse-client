#ifndef __FRIEND_REQUEST_THREAD_HPP__
#define __FRIEND_REQUEST_THREAD_HPP__
#include <iostream>
#include <QThread>
#include <QString>
#include <QMutex>

#include "tcp_connection.hpp"

class friends_thread : public QObject
{
	Q_OBJECT
public:
	explicit friend_request_thread(QObject * _p_parent = NULL);
	virtual ~friend_request_thread();

	bool init();
	
	Q_SLOT int run();
	Q_SLOT void run_once();

	bool isRunning() {return m_p_thread->isRunning();};
	void quit() {m_p_thread->quit();};
	void requestInterruption() {m_p_thread->requestInterruption();};
	
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
private:
	QThread * m_p_thread;
	QMutex * m_p_response_mutex;
	QString * m_p_response;

	QMutex * m_p_username_mutex;
	QString * m_p_username;

	QMutex * m_p_password_mutex;
	QString * m_p_password;
};

#endif
