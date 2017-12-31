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

#ifndef FRIENDS_LIST_HPP
#define FRIENDS_LIST_HPP

#include <QMessageBox>
#include <QStringList>
#include <iostream>
#include <QWidget>
#include <QTest>
#include "ui_friends_list.h"
#include "friend_requests.hpp"
#include "tcp_connection.hpp"

namespace Ui
{
class friends_list;
}

class friends_list : public QWidget
{
  Q_OBJECT

public:
  explicit friends_list(QWidget * _p_parent = NULL);
  virtual ~friends_list();

  QString * m_p_username;
  QString * m_p_password;

  Q_SIGNAL void return_to_home_screen();
  void fill_fields();

private:
  Ui::friends_list * m_p_ui;
  friend_requests * m_p_friend_requests;

  Q_SLOT void on_delete_friend();
  Q_SLOT void on_add_friend();
  Q_SLOT void on_back_button();
  Q_SLOT void goto_friend_requests();
  Q_SLOT void from_requests();
};

#endif
