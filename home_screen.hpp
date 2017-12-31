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

#ifndef HOME_SCREEN_HPP
#define HOME_SCREEN_HPP
#include <QStringList>
#include <QDateTime>
#include <QWidget>
#include <QtGui>

#include "create_group_event.hpp"
#include "account_settings.hpp"
#include "schedulinggrid.hpp"
#include "friends_thread.hpp"
#include "manage_groups.hpp"
#include "ui_home_screen.h"
#include "friends_list.hpp"

namespace Ui
{
class home_screen;
}

class home_screen : public QWidget
{
  Q_OBJECT

public:
  explicit home_screen(QWidget * _p_parent = NULL);
  virtual ~home_screen();

  QString * m_p_username;
  QString * m_p_password;

  friends_thread * m_p_friends_thread;
  friends_list * m_p_friends_list;

  void kick_off_threads();

  Q_SLOT void to_account_settings();
  Q_SLOT void to_see_schedule();
  Q_SLOT void to_manage_groups();
  Q_SLOT void to_create_event();
  Q_SLOT void to_friends_list();

  Q_SLOT void from_create_event();
  Q_SLOT void from_see_schedule();
  Q_SLOT void from_manage_groups();
  Q_SLOT void from_account_settings();
  Q_SLOT void from_friends_list();

  Q_SLOT void on_logout();

  Q_SIGNAL void return_to_login();

private:
  Ui::home_screen * m_p_ui;

  schedulingGrid * m_p_schedule;
  account_settings * m_p_account_settings;
  manage_groups * m_p_manage_groups;
  create_group_event * m_p_create_event;
};
#endif
