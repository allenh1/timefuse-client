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

#ifndef SUGGEST_USER_EVENT_HPP
#define SUGGEST_USER_EVENT_HPP

#include <QWidget>
#include <QTimeEdit>
#include <iostream>
#include <QTime>
#include <QMessageBox>

#include "ui_suggest_user_event.h"
#include "tcp_connection.hpp"

namespace Ui
{
class suggest_user_event;
}

class suggest_user_event : public QWidget
{
  Q_OBJECT

public:
  explicit suggest_user_event(QWidget * _p_parent = NULL);
  virtual ~suggest_user_event();

  QString * m_p_username;
  QString * m_p_password;

  Q_SIGNAL void return_to_event();
  Q_SIGNAL void return_time(QString);

private:
  Ui::suggest_user_event * m_p_ui;

  Q_SLOT void on_cancel();
  Q_SLOT void on_select_time();
  Q_SLOT void suggest_a_time();
};

#endif
