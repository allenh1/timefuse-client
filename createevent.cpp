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

#include "createevent.hpp"

createevent::createevent(QWidget * parent)
: QWidget(parent),
  ui(new Ui::createevent)
{
  QFont font(QString("Courier"), 12, QFont::Thin, false);
  this->setFont(font);

  ui->setupUi(this);

  m_p_username = new QString("");
  m_p_password = new QString("");

  m_p_suggest_event = new suggest_user_event();

  connect(ui->pushButton, &QPushButton::released,
    this, &createevent::create_the_event);
  connect(ui->pushCancel, &QPushButton::released,
    this, &createevent::cancel_event);
  connect(ui->suggest_time, &QPushButton::released,
    this, &createevent::suggest_a_time);

  // return to create event
  connect(m_p_suggest_event, &suggest_user_event::return_time,
    this, &createevent::get_time);
  connect(m_p_suggest_event, &suggest_user_event::return_to_event,
    this, &createevent::from_suggest_time);

  ui->dateEdit->setDate(QDate::currentDate());
}

createevent::~createevent() {}

void createevent::suggest_a_time()
{
  m_p_suggest_event->m_p_username = m_p_username;
  m_p_suggest_event->m_p_password = m_p_password;
  this->hide();
  m_p_suggest_event->show();
}

void createevent::get_time(QString suggested)
{
  QStringList list = suggested.split(":::");

  QStringList date = list[0].split("-");
  ui->dateEdit->setDate(QDate(date[0].toInt(), date[1].toInt(),
    date[2].toInt()));

  QStringList time = list[1].split(":");
  ui->begin_time_edit_2->setTime(QTime(time[0].toInt(), time[1].toInt()));

  m_p_suggest_event->hide();
  this->show();
}

void createevent::from_suggest_time()
{
  m_p_suggest_event->hide();
  this->show();
}

void createevent::create_the_event()
{
  QString * request = new QString("CREATE_USER_EVENT ");
  int year = ui->dateEdit->date().year();
  int day = ui->dateEdit->date().day();
  int month = ui->dateEdit->date().month();
  int hour = ui->begin_time_edit_2->time().hour();
  int minute = ui->begin_time_edit_2->time().minute();

  int fixed = 1;
  if (ui->radioNegotiable->isChecked()) {
    fixed = 0;
  }

  /* create the request */
  (*request) += *m_p_username + ":::" + *m_p_password + ":::" +
    QString::number(year) + "-" + QString::number(month) +
    "-" + QString::number(day) + ":::" + QString::number(hour) +
    ":" + QString::number(minute).rightJustified(2, '0') +
    ":::" + ui->duration_input_2->displayText() + ":::" +
    ui->location_input_2->displayText() + ":::" +
    QString::number(ui->timezoneOffset->value()) +
    ":::" + ui->title_input_2->displayText() +
    ":::" + QString::number(fixed);
  (*request) += QString::number(fixed);

  QString * response = setup_connection(request);
  std::cerr << "response: " << response->toStdString() << std::endl;

  if (response->contains("ERROR")) {
    QMessageBox::critical(this, tr("Error"), *response);
  } else {
    ui->title_input_2->setText("");
    ui->location_input_2->setText("");
    ui->dateEdit->setDate(QDate::currentDate());
    ui->begin_time_edit_2->setTime(QTime(0, 0));
    ui->duration_input_2->setText("");

    Q_EMIT (return_to_schedule());
  }
}

void createevent::cancel_event()
{
  ui->title_input_2->setText("");
  ui->location_input_2->setText("");
  ui->dateEdit->setDate(QDate::currentDate());
  ui->begin_time_edit_2->setTime(QTime(0, 0));
  ui->duration_input_2->setText("");

  Q_EMIT (return_to_schedule());
}
