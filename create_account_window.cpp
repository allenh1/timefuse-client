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

#include "create_account_window.hpp"

create_account_window::create_account_window(QWidget * parent)
: QWidget(parent),
  m_p_ui(new Ui::create_account_window)
{
  QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
  this->setPalette(qpalette);
  QFont font(QString("Courier"), 10.5, QFont::Thin, false);
  this->setFont(font);

  m_p_ui->setupUi(this);

  /* set the password edit to not show text */
  m_p_ui->password_input->setEchoMode(QLineEdit::Password);
  m_p_ui->password_input->setInputMethodHints(Qt::ImhHiddenText |
    Qt::ImhNoPredictiveText |
    Qt::ImhNoAutoUppercase);
  m_p_ui->phone_input->setPlaceholderText(tr("0000000000"));
  m_p_ui->name_input->setPlaceholderText(tr("Create a username"));
  m_p_ui->email_input->setPlaceholderText(tr("email@domain.com"));

  /* connect signals */
  connect(m_p_ui->cancel_button, &QPushButton::released,
    this, &create_account_window::cancel_pressed);
  connect(m_p_ui->create_button, &QPushButton::released,
    this, &create_account_window::create_pressed);
}

create_account_window::~create_account_window() {}

void create_account_window::create_pressed()
{
  QString name = m_p_ui->name_input->text();
  if (!name.size()) {
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
  QString phone = m_p_ui->phone_input->text();
  phone = phone.trimmed();
  if ((phone.size() != 10 && phone.size() != 0) ||
    (phone.size() == 10 && phone.toLong() == 0))
  {
    QMessageBox::critical(this, tr("Error"),
      tr("That's not a phone number!"));
    return;
  }
  QString password = m_p_ui->password_input->text();
  if (!password.size()) {
    QMessageBox::critical(this, tr("Error"),
      tr("No password was entered!"));
    return;
  }
  password = encrypt_string(password);

  QString * request = new QString("CREATE_ACCOUNT ");

  (*request) += name; (*request) += ":::"; (*request) += password;
  (*request) += ":::"; (*request) += email; (*request) += ":::";
  (*request) += phone; (*request) += "\r\n\0";

  QString * response = setup_connection(request);

  if (response->indexOf(tr("ERROR:")) != -1) {
    QMessageBox::critical(this, tr("Error"), *response);
  }

  delete response;
  delete request;

  m_p_ui->password_input->setText("");
  m_p_ui->phone_input->setText("");
  m_p_ui->name_input->setText("");
  m_p_ui->email_input->setText("");

  Q_EMIT (return_to_user_page());
}

void create_account_window::cancel_pressed()
{
  m_p_ui->password_input->setText("");
  m_p_ui->phone_input->setText("");
  m_p_ui->name_input->setText("");
  m_p_ui->email_input->setText("");
  Q_EMIT (return_to_user_page());
}
