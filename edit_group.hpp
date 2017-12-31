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

#ifndef EDIT_GROUP_HPP
#define EDIT_GROUP_HPP

#include <QWidget>
#include <QListWidget>
#include <QMessageBox>
#include <iostream>

#include "tcp_connection.hpp"
#include "encrypt_string.hpp"
#include "ui_edit_group.h"

namespace Ui
{
class edit_group;
}

class edit_group : public QWidget
{
  Q_OBJECT

public:
  explicit edit_group(QWidget * parent = 0);
  ~edit_group();

  QString * m_p_username;
  QString * m_p_password;
  QString * m_p_group;

  Q_SIGNAL void return_to_manage_groups();
  void fill_fields();

private:
  Ui::edit_group * ui;


  Q_SLOT void on_back_button();
  Q_SLOT void add_a_member();
};

#endif // ADD_GROUP_H
