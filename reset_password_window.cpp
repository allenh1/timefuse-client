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

#include "reset_password_window.hpp"
//#include "ui_reset_password_window.hpp"

reset_password_window::reset_password_window(QWidget * parent)
: QWidget(parent),
  m_p_ui(new Ui::reset_password_window)
{
  QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
  this->setPalette(qpalette);
  QFont font(QString("Courier"), 10.5, QFont::Thin, false);
  this->setFont(font);

  m_p_ui->setupUi(this);

  m_p_ui->email_input->setPlaceholderText(tr("email@domain.com"));
  m_p_ui->username_input->setPlaceholderText(tr("Enter your username"));
  m_p_ui->new_password_input->setPlaceholderText(tr("Enter new password"));

  /* set the password edit to not show text */
  m_p_ui->new_password_input->setEchoMode(QLineEdit::Password);
  m_p_ui->new_password_input->setInputMethodHints(Qt::ImhHiddenText |
    Qt::ImhNoPredictiveText |
    Qt::ImhNoAutoUppercase);

  /* connect signals */
  connect(m_p_ui->cancel_button, &QPushButton::released,
    this, &reset_password_window::cancel_pressed);
  connect(m_p_ui->reset_button, &QPushButton::released,
    this, &reset_password_window::reset_pressed);

}

reset_password_window::~reset_password_window() {}

void reset_password_window::reset_pressed()
{
  QString username = m_p_ui->username_input->text();
  if (!username.size()) {
    QMessageBox::critical(this, tr("Error"),
      tr("No username was entered!"));
    return;
  }
  QString email = m_p_ui->email_input->text();
  if (!email.contains("@") || !(email.lastIndexOf(".") > email.indexOf("@"))) {
    QMessageBox::critical(this, tr("Error"),
      tr("That's not an email!"));
    return;
  }
  QString password = m_p_ui->new_password_input->text();
  if (!password.size()) {
    QMessageBox::critical(this, tr("Error"),
      tr("No password was entered!"));
    return;
  }
  QString * request = new QString("REQUEST_RESET ");

  (*request) += username; (*request) += ":::";
  (*request) += email; (*request) += ":::";
  (*request) += encrypt_string(password);
  (*request) += "\r\n\0";

  QString * response = setup_connection(request);

  if (response->contains("ERROR")) {
    QMessageBox::critical(this, tr("Error"), *response);
    delete response; delete request;
    return;
  }
  delete response; delete request;

  m_p_ui->email_input->setText("");
  m_p_ui->username_input->setText("");
  m_p_ui->new_password_input->setText("");
  Q_EMIT (return_to_user_page());
}


void reset_password_window::cancel_pressed()
{
  m_p_ui->email_input->setText("");
  m_p_ui->username_input->setText("");
  m_p_ui->new_password_input->setText("");
  Q_EMIT (return_to_user_page());
}
