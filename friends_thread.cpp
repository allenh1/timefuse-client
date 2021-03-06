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

#include "friends_thread.hpp"

friends_thread::friends_thread(QObject * _p_parent)
{
  m_p_thread = new QThread();

  m_p_response_mutex = new QMutex();
  m_p_username_mutex = new QMutex();
  m_p_password_mutex = new QMutex();

  m_p_response = new QString();
  m_p_username = new QString();
  m_p_password = new QString();
}

friends_thread::~friends_thread()
{
  delete m_p_response_mutex; delete m_p_username_mutex;
  delete m_p_username; delete m_p_password_mutex;
  delete m_p_password; delete m_p_response;
  m_p_thread->requestInterruption(); m_p_thread->quit();
  delete m_p_thread;
}

bool friends_thread::init()
{
  this->moveToThread(m_p_thread);
  connect(m_p_thread, &QThread::started, this, &friends_thread::run);
  m_p_thread->start();
  return m_p_thread->isRunning();
}

int friends_thread::run()
{
  for (;; m_p_thread->msleep(10000)) {
    QString * request = new QString("REQUEST_FRIENDS ");

    (*request) += m_p_username; (*request) += ":::";
    (*request) += m_p_password; (*request) += "\r\n\0";

    m_p_response = setup_connection(request); delete request;
  }
  return 1;
}

void friends_thread::run_once()
{
  QString * request = new QString("REQUEST_FRIENDS ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += "\r\n\0";

  m_p_response = setup_connection(request); delete request;
}
