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

#ifndef __CREATE_ACCOUNT_WINDOW_HPP__
#define __CREATE_ACCOUNT_WINDOW_HPP__
#include <QMessageBox>
#include <QtWidgets>
#include <QString>
#include <QtGui>

#include "ui_create_account_window.h"
#include "tcp_connection.hpp"
#include "encrypt_string.hpp"
#include "user.hpp"

class user;

namespace Ui
{
class create_account_window;
}

class create_account_window : public QWidget
{
  Q_OBJECT

public:
  explicit create_account_window(QWidget * _p_parent = NULL);
  virtual ~create_account_window();

  Q_SLOT void create_pressed();
  Q_SLOT void cancel_pressed();

  Q_SIGNAL void return_to_user_page();

private:
  Ui::create_account_window * m_p_ui;
};
#endif
