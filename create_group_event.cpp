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

#include "create_group_event.hpp"

create_group_event::create_group_event(QWidget * parent)
: QWidget(parent),
  m_p_ui(new Ui::create_group_event)
{
  QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
  this->setPalette(qpalette);
  QFont font(QString("Courier"), 10.5, QFont::Thin, false);
  this->setFont(font);

  m_p_ui->setupUi(this);

  m_p_username = new QString("");
  m_p_password = new QString("");

  m_p_time_suggested = new QString("");

  m_p_suggested_time = new suggested_time();

  m_p_ui->group_to_add->setPlaceholderText(tr("Enter a group name"));
  m_p_ui->duration_input->setPlaceholderText(tr("in minutes"));
  m_p_ui->title_input->setPlaceholderText(tr("Group event name"));
  m_p_ui->location_input->setPlaceholderText(tr("Group event location"));

  // connect buttons
  connect(m_p_ui->cancel, &QPushButton::released,
    this, &create_group_event::on_cancel);
  connect(m_p_ui->add_member, &QPushButton::released,
    this, &create_group_event::add_group_members);
  connect(m_p_ui->create_event, &QPushButton::released,
    this, &create_group_event::on_create_group_event);
  connect(m_p_ui->get_a_time, &QPushButton::released,
    this, &create_group_event::suggest_a_time);
  connect(m_p_suggested_time, &suggested_time::return_to_group_event,
    this, &create_group_event::from_suggested_time);

  m_p_ui->dateEdit->setDate(QDate::currentDate());
}

create_group_event::~create_group_event() {}

void create_group_event::on_cancel()
{
  m_p_ui->group_to_add->setText("");
  m_p_ui->title_input->setText("");
  m_p_ui->location_input->setText("");
  m_p_ui->duration_input->setText("");

  m_p_ui->begin_time_edit->setTime(QTime(0, 0));
  m_p_ui->dateEdit->setDate(QDate::currentDate());
  m_p_ui->attendees_list->clear();
  Q_EMIT (return_to_home_screen());
}

void create_group_event::suggest_a_time()
{
  m_p_suggested_time->m_p_username = m_p_username;
  m_p_suggested_time->m_p_password = m_p_password;

  (*m_p_suggested_time->m_p_group_name) = m_p_ui->group_to_add->text();
  (*m_p_suggested_time->m_p_duration) = m_p_ui->duration_input->text();

  int year = m_p_ui->dateEdit->date().year();
  int day = m_p_ui->dateEdit->date().day();
  int month = m_p_ui->dateEdit->date().month();

  (*m_p_suggested_time->m_p_start_date) += QString::number(year) + "-";
  (*m_p_suggested_time->m_p_start_date) += QString::number(month) + "-";
  (*m_p_suggested_time->m_p_start_date) += QString::number(day);
  (*m_p_suggested_time->m_p_finish_time) =
    m_p_ui->begin_time_edit->time().toString("hh:mm");
  this->hide();
  m_p_suggested_time->show();
  m_p_suggested_time->fill_fields();
}

void create_group_event::from_suggested_time()
{
  m_p_suggested_time->m_p_duration->clear();
  m_p_suggested_time->m_p_start_date->clear();
  m_p_suggested_time->m_p_group_name->clear();
  m_p_suggested_time->m_p_finish_time->clear();

  m_p_time_suggested->clear();
  (*m_p_time_suggested) += m_p_suggested_time->m_p_selected_time;

  QStringList selected = m_p_time_suggested->split(":::");

  if (selected.size() == 2) {
    QDate selected_date = QDate::fromString(selected[0], "yyyy-M-d");
    QTime selected_time = QTime::fromString(selected[1], "hh:mm");

    m_p_ui->dateEdit->setDate(selected_date);
    m_p_ui->begin_time_edit->setTime(selected_time);
  }

  m_p_suggested_time->hide();
  this->show();
}

void create_group_event::add_group_members()
{
  if (m_p_ui->group_to_add->text().size() == 0) {return;}

  QString * request = new QString("REQUEST_USERS ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += ":::";
  (*request) += m_p_ui->group_to_add->text();
  (*request) += "\r\n\0";

  QString * response = setup_connection(request);

  if (response->contains("ERROR")) {
    QMessageBox::critical(this, tr("Error"), *response);
  } else {
    response->replace("\r\n", "");
    QStringList list = response->split('\n');
    m_p_ui->attendees_list->clear();
    for (int i = 0; i < list.size(); i++) {
      if (list.at(i).size() == 0) {continue;}
      m_p_ui->attendees_list->addItem(list.at(i));
    }
  } delete request; delete response;
}

void create_group_event::on_create_group_event()
{
  QString * request = new QString("CREATE_GROUP_EVENT ");

  int year = m_p_ui->dateEdit->date().year();
  int day = m_p_ui->dateEdit->date().day();
  int month = m_p_ui->dateEdit->date().month();
  int hour = m_p_ui->begin_time_edit->time().hour();
  int minute = m_p_ui->begin_time_edit->time().minute();

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += ":::";
  (*request) += m_p_ui->group_to_add->displayText(); (*request) += ":::";
  (*request) += QString::number(year); (*request) += '-';
  (*request) += QString::number(month); (*request) += '-';
  (*request) += QString::number(day); (*request) += ":::";
  (*request) += QString::number(hour); (*request) += ':';
  (*request) += QString::number(minute).rightJustified(2, '0'); (*request) += ":::";
  (*request) += m_p_ui->duration_input->displayText(); (*request) += ":::";
  (*request) += m_p_ui->location_input->displayText(); (*request) += ":::";
  (*request) += "-5"; (*request) += ":::";
  (*request) += m_p_ui->title_input->displayText(); (*request) += "\r\n\0";

  std::cerr << "request: " << request->toStdString() << std::endl;
  QString * response = setup_connection(request);
  std::cerr << "response: " << response->toStdString() << std::endl;

  if (response->contains("ERROR")) {
    QMessageBox::critical(this, tr("Error"), *response);
  } else {
    m_p_ui->group_to_add->setText("");
    m_p_ui->title_input->setText("");
    m_p_ui->location_input->setText("");
    m_p_ui->duration_input->setText("");

    m_p_ui->begin_time_edit->setTime(QTime(0, 0));
    m_p_ui->dateEdit->setDate(QDate::currentDate());
    m_p_ui->attendees_list->clear();
    Q_EMIT (return_to_home_screen());
  } delete response; delete request;
}
