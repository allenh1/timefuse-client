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

#ifndef RESET_PASSWORD_WINDOW_HPP
#define RESET_PASSWORD_WINDOW_HPP
#include <QMessageBox>
#include <QWidget>
#include <QtGui>

#include "ui_reset_password_window.h"
#include "tcp_connection.hpp"
#include "encrypt_string.hpp"
#include "user.hpp"

class user;

namespace Ui
{
class reset_password_window;
}

class reset_password_window : public QWidget
{
  Q_OBJECT

public:
  explicit reset_password_window(QWidget * _p_parent = NULL);
  virtual ~reset_password_window();


  Q_SLOT void reset_pressed();
  Q_SLOT void cancel_pressed();

  Q_SIGNAL void send_create_account(user * u);
  Q_SIGNAL void return_to_user_page();

private:
  Ui::reset_password_window * m_p_ui;
};
#endif // RESET_PASSWORD_WINDOW_H
