#ifndef __REFRESH_THREAD_HPP__
#define __REFRESH_THREAD_HPP__
#include <QTcpSocket>
#include <QString>
#include <QMutex>
#include <iostream>

typedef unsigned int uint;

class refresh_thread : public QObject
{
	Q_OBJECT
public:
	explicit refresh_thread(QObject * _p_parent = NULL);
	virtual ~refresh_thread();

	virtual bool init() {};

	virtual Q_SLOT void run() {};
	virtual Q_SLOT void run_once(QString, QString) {};
	virtual Q_SLOT void run_method() {};

	QString* setup_connection(QString*);
};

#endif
