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

#ifndef __CREATEEVENT_H__
#define __CREATEEVENT_H__
#include <QMessageBox>
#include <QFileDialog>
#include <iostream>
#include <QDialog>
#include <QString>
#include <QDate>

#include "suggest_user_event.hpp"
#include "tcp_connection.hpp"
#include "ui_createevent.h"

namespace Ui
{
class createevent;
}

class createevent : public QWidget
{
  Q_OBJECT

public:
  explicit createevent(QWidget * parent = 0);
  virtual ~createevent();

  QString * m_p_username;
  QString * m_p_password;

  Q_SIGNAL void return_to_schedule();

private:
  Ui::createevent * ui;
  suggest_user_event * m_p_suggest_event;

  Q_SLOT void get_time(QString);
  Q_SLOT void from_suggest_time();
  Q_SLOT void suggest_a_time();
  Q_SLOT void create_the_event();
  Q_SLOT void cancel_event();
};
#endif
