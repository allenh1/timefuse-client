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

#ifndef SUGGESTED_TIME_HPP
#define SUGGESTED_TIME_HPP

#include <QMessageBox>
#include <QStringList>
#include <iostream>
#include <QWidget>
#include "ui_suggested_time.h"
#include "tcp_connection.hpp"

namespace Ui
{
class suggested_time;
}

class suggested_time : public QWidget
{
  Q_OBJECT

public:
  explicit suggested_time(QWidget * _p_parent = NULL);
  virtual ~suggested_time();

  QString * m_p_username;
  QString * m_p_password;

  QString * m_p_start_date;
  QString * m_p_duration;
  QString * m_p_group_name;
  QString * m_p_finish_time;

  QString * m_p_selected_time;

  Q_SIGNAL void return_to_group_event();
  void fill_fields();

private:
  Ui::suggested_time * m_p_ui;

  Q_SLOT void on_selected_time();
  Q_SLOT void on_back_button();
};

#endif
