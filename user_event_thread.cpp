// Copyright 2017 Hunter L. Allen, Anqi Wang
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
  m_p_year = new QString();
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
  if (m_p_thread != (QThread *)NULL) {delete m_p_thread;}
  m_p_thread = new QThread();
  this->moveToThread(m_p_thread);
  connect(m_p_thread, &QThread::started, this, &user_event_thread::run);
  m_p_thread->start();
  return m_p_thread->isRunning();
}

void user_event_thread::run()
{
  for (; m_p_username->size() && m_p_password->size(); m_p_thread->msleep(5000)) {
    run_method();
  }
}

void user_event_thread::run_once(QString month, QString year)
{
  if (!m_p_username->size() || !m_p_password->size()) {return;}
  QString * user_request = new QString("REQUEST_PERSONAL_MONTH_EVENTS ");

  (*user_request) += *m_p_username; (*user_request) += ":::";
  (*user_request) += *m_p_password; (*user_request) += ":::";
  (*user_request) += month; (*user_request) += ":::";
  (*user_request) += year;

  delete m_p_response;
  m_p_response = setup_connection(user_request); delete user_request;
  if (m_p_response->contains("ERROR")) {return;}
  uint t = m_p_response->split("\n")[0].toInt();
  std::cerr << "user event: " << t << "month: " << month.toInt() <<
    "\tyear: " << year.toInt() << std::endl;
  QString date = month + ":" + year;
  Q_EMIT (value_changed(date, t));
}

void user_event_thread::run_method()
{
  int m = m_p_month->toInt();
  int y = m_p_year->toInt();
  run_once(QString::number(m), QString::number(y));
  for (int i = 1; (i < 12) && (m_p_username->size() && m_p_password->size()); ++i) {
    if (i < m) {
      run_once(QString::number(m - i), QString::number(y));
    } else if ((m - i) <= 0) {
      run_once(QString::number(12 + (m - i)), QString::number(y - 1));
    }
    if ((m + i) > 12) {
      run_once(QString::number((m + i) % 12), QString::number(y + 1));
    } else if ((m + i) <= 12) {
      run_once(QString::number(m + i), QString::number(y));
    }
  }
}
