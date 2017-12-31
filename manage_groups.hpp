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

#ifndef MANAGE_GROUPS_HPP
#define MANAGE_GROUPS_HPP

#include <QStringList>
#include <QWidget>
#include <QTest>
#include "ui_manage_groups.h"
#include "add_group.h"
#include "edit_group.hpp"

namespace Ui
{
class manage_groups;
}

class manage_groups : public QWidget
{
  Q_OBJECT

public:
  explicit manage_groups(QWidget * _p_parent = NULL);
  virtual ~manage_groups();

  QString * m_p_username;
  QString * m_p_password;

  Q_SIGNAL void return_to_home_screen();
  void fill_fields();

private:
  Ui::manage_groups * m_p_ui;

  Q_SLOT void on_leave_group();
  Q_SLOT void on_delete_group();

  Q_SLOT void goto_edit_group();
  Q_SLOT void on_back_button();
  Q_SLOT void on_new_group();

  Q_SLOT void hide_edit_group();
  Q_SLOT void hide_add_group();

  add_group * m_p_add_group;
  edit_group * m_p_edit_group;
};

#endif
