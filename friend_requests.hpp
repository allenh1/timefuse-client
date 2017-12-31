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

#ifndef FRIEND_REQUESTS_HPP
#define FRIEND_REQUESTS_HPP

#include <QMessageBox>
#include <QStringList>
#include <iostream>
#include <QWidget>
#include <QTest>
#include "ui_friend_requests.h"
#include "tcp_connection.hpp"

namespace Ui
{
class friend_requests;
}

class friend_requests : public QWidget
{
  Q_OBJECT

public:
  explicit friend_requests(QWidget * _p_parent = NULL);
  virtual ~friend_requests();

  QString * m_p_username;
  QString * m_p_password;

  Q_SIGNAL void return_to_friends();
  void fill_fields();

private:
  Ui::friend_requests * m_p_ui;

  Q_SLOT void on_delete_friend();
  Q_SLOT void on_add_friend();
  Q_SLOT void on_back_button();
};

#endif
