// Copyright 2017 Hunter L. Allen, Angie Wang
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __GROUP_EVENT_THREAD_HPP__
#define __GROUP_EVENT_THREAD_HPP__
#include <iostream>
#include <QThread>
#include <QString>
#include <QMutex>

#include "refresh_thread.hpp"

class group_event_thread : public refresh_thread
{
  Q_OBJECT

public:
  explicit group_event_thread(QObject * _p_parent = NULL);
  virtual ~group_event_thread();

  bool init();

  Q_SIGNAL void value_changed(QString, uint);

  Q_SLOT void run();
  Q_SLOT void run_once(QString, QString);
  Q_SLOT void run_method();

  bool isRunning() {return m_p_thread->isRunning();}
  void quit() {m_p_thread->quit();}
  void requestInterruption() {m_p_thread->requestInterruption();}

  uint get_occupied_days()
  {
    register uint temp = 0;
    m_p_occupied_mutex->lock();
    temp = m_occupied_days;
    m_p_occupied_mutex->unlock();
    return temp;
  }

  void set_username(const QString & username)
  {
    m_p_username_mutex->lock();
    (*m_p_username) = username;
    m_p_username_mutex->unlock();
  }

  void set_password(const QString & password)
  {
    m_p_password_mutex->lock();
    (*m_p_password) = password;
    m_p_password_mutex->unlock();
  }

  void set_month(const QString & month)
  {
    m_p_month_mutex->lock();
    (*m_p_month) = month;
    m_p_month_mutex->unlock();
  }

  void set_year(const QString & year)
  {
    m_p_year_mutex->lock();
    (*m_p_year) = year;
    m_p_year_mutex->unlock();
  }

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
