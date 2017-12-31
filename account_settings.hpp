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

#ifndef __ACCOUNT_SETTINGS_HPP__
#define __ACCOUNT_SETTINGS_HPP__

#include <QMessageBox>
#include <QStringList>
#include <QtWidgets>
#include <QString>
#include <QtGui>

#include "ui_account_settings.h"
#include "tcp_connection.hpp"
#include "encrypt_string.hpp"

namespace Ui
{
class account_settings;
}

class account_settings : public QWidget
{
  Q_OBJECT

public:
  explicit account_settings(QWidget * _p_parent = NULL);
  virtual ~account_settings();

  QString * m_p_secret;
  QString * m_p_username;
  QString * m_p_password;

  Q_SIGNAL void return_to_home_screen();

  void fill_fields();

private:
  Ui::account_settings * m_p_ui;

  Q_SLOT void save_changes_pressed();
  Q_SLOT void cancel_pressed();
  Q_SLOT void leave_of_absence_pressed();
  Q_SLOT void present_pressed();
};

#endif
