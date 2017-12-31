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

#include "account_settings.hpp"

account_settings::account_settings(QWidget * parent)
: QWidget(parent),
  m_p_ui(new Ui::account_settings)
{
  //QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
  //this->setPalette(qpalette);
  QFont font(QString("Courier"), 12, QFont::Thin, false);
  this->setFont(font);

  m_p_ui->setupUi(this);

  m_p_username = new QString("");
  m_p_password = new QString("");

  m_p_ui->username_input->setReadOnly(true);

  /* set the password edit to not show text */
  m_p_ui->old_password_input->setEchoMode(QLineEdit::Password);
  m_p_ui->old_password_input->setInputMethodHints(Qt::ImhHiddenText |
    Qt::ImhNoPredictiveText |
    Qt::ImhNoAutoUppercase);
  m_p_ui->new_password_input->setEchoMode(QLineEdit::Password);
  m_p_ui->new_password_input->setInputMethodHints(Qt::ImhHiddenText |
    Qt::ImhNoPredictiveText |
    Qt::ImhNoAutoUppercase);

  /* connect signals */
  connect(m_p_ui->cancel_button, &QPushButton::released,
    this, &account_settings::cancel_pressed);
  connect(m_p_ui->save_changes, &QPushButton::released,
    this, &account_settings::save_changes_pressed);
  connect(m_p_ui->leave_of_absence, &QPushButton::released,
    this, &account_settings::leave_of_absence_pressed);
  connect(m_p_ui->present, &QPushButton::released,
    this, &account_settings::present_pressed);
}

account_settings::~account_settings() {}

void account_settings::leave_of_absence_pressed()
{
  QString * request = new QString("ABSENT ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += "\r\n\0";

  QString * response = setup_connection(request);

  if (response->contains(tr("ERROR"))) {
    QMessageBox::critical(this, tr("Error"), *response);
  } else {
    QMessageBox::information(this, tr("OK"),
      "You are now absent from all group events.");
  } delete response; delete request;
}

void account_settings::present_pressed()
{
  QString * request = new QString("PRESENT ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += "\r\n\0";

  QString * response = setup_connection(request);

  if (response->contains(tr("ERROR"))) {
    QMessageBox::critical(this, tr("Error"), *response);
  } else {
    QMessageBox::information(this, tr("OK"),
      "You are now present for all group events.");
  } delete response; delete request;
}

void account_settings::save_changes_pressed()
{
  QString new_name = m_p_ui->new_username_input->text();
  *m_p_username = new_name;
  QString old_password = encrypt_string(m_p_ui->old_password_input->text());
  QString new_password = encrypt_string(m_p_ui->new_password_input->text());
  *m_p_password = new_password;
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

  QString * request = new QString("UPDATE_ACCOUNT ");

  (*request) += m_p_username; (*request) += ":::"; (*request) += old_password;
  (*request) += ":::"; (*request) += new_password;
  (*request) += ":::"; (*request) += new_name;
  (*request) += ":::"; (*request) += email;
  (*request) += ":::"; (*request) += phone; (*request) += "\r\n\0";

  QString * response = setup_connection(request);

  if (response->contains(tr("ERROR:"))) {
    QMessageBox::critical(this, tr("Error"), *response);
  }

  delete response;
  delete request;

  Q_EMIT (return_to_home_screen());
}

void account_settings::cancel_pressed()
{
  m_p_ui->old_password_input->setText("");
  m_p_ui->new_password_input->setText("");
  m_p_ui->phone_input->setText("");
  m_p_ui->email_input->setText("");
  Q_EMIT (return_to_home_screen());
}

void account_settings::fill_fields()
{
  m_p_ui->username_input->setText(*m_p_username);
  m_p_ui->new_username_input->setText(*m_p_username);

  m_p_ui->old_password_input->setText("");
  m_p_ui->new_password_input->setText("");

  QString * request = new QString("REQUEST_ACCOUNT ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += "\r\n\0";

  QString * response = setup_connection(request);

  if (!response->contains("ERROR")) {
    QStringList list = response->split(":::");
    m_p_ui->email_input->setText(list.at(0));
    if (list.at(1)[0] == '0') {
      m_p_ui->phone_input->setText("");
      m_p_ui->phone_input->setPlaceholderText("0000000000");
    } else {m_p_ui->phone_input->setText(list.at(1));}
  }
  delete request; delete response;
}
