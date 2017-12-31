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

#ifndef CREATE_GROUP_EVENT_HPP
#define CREATE_GROUP_EVENT_HPP

#include <QWidget>
#include <QTimeEdit>
#include <iostream>
#include <QTime>
#include <QMessageBox>

#include "ui_create_group_event.h"
#include "suggested_time.hpp"
#include "tcp_connection.hpp"

namespace Ui
{
class create_group_event;
}

class create_group_event : public QWidget
{
  Q_OBJECT

public:
  explicit create_group_event(QWidget * _p_parent = NULL);
  virtual ~create_group_event();

  QString * m_p_username;
  QString * m_p_password;

  QString * m_p_time_suggested;

  Q_SIGNAL void return_to_home_screen();

private:
  Ui::create_group_event * m_p_ui;
  suggested_time * m_p_suggested_time;

  Q_SLOT void on_cancel();
  Q_SLOT void add_group_members();
  Q_SLOT void on_create_group_event();
  Q_SLOT void suggest_a_time();
  Q_SLOT void from_suggested_time();
};

#endif
