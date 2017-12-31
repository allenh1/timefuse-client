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

#include "home_screen.hpp"

home_screen::home_screen(QWidget * parent)
: QWidget(parent),
  m_p_ui(new Ui::home_screen)
{
  QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
  this->setPalette(qpalette);
  QFont font(QString("Courier"), 10.5, QFont::Thin, false);
  this->setFont(font);

  m_p_ui->setupUi(this);

  m_p_username = new QString("");
  m_p_password = new QString("");

  m_p_schedule = new schedulingGrid();
  m_p_create_event = new create_group_event();
  m_p_account_settings = new account_settings();
  m_p_manage_groups = new manage_groups();

  m_p_friends_list = new friends_list();
  m_p_friends_thread = new friends_thread();

  // connections to different windows
  connect(m_p_ui->create_event, &QPushButton::released,
    this, &home_screen::to_create_event);
  connect(m_p_ui->see_schedule, &QPushButton::released,
    this, &home_screen::to_see_schedule);
  connect(m_p_ui->account_settings, &QPushButton::released,
    this, &home_screen::to_account_settings);
  connect(m_p_ui->manage_groups, &QPushButton::released,
    this, &home_screen::to_manage_groups);
  connect(m_p_ui->friend_list, &QPushButton::released,
    this, &home_screen::to_friends_list);

  // connections from different windows
  connect(m_p_account_settings, &account_settings::return_to_home_screen,
    this, &home_screen::from_account_settings);
  connect(m_p_schedule, &schedulingGrid::return_to_home_screen,
    this, &home_screen::from_see_schedule);
  connect(m_p_manage_groups, &manage_groups::return_to_home_screen,
    this, &home_screen::from_manage_groups);
  connect(m_p_create_event, &create_group_event::return_to_home_screen,
    this, &home_screen::from_create_event);
  connect(m_p_friends_list, &friends_list::return_to_home_screen,
    this, &home_screen::from_friends_list);

  // logout connection
  connect(m_p_ui->logout_button, &QPushButton::released,
    this, &home_screen::on_logout);
}

home_screen::~home_screen() {}

void home_screen::kick_off_threads()
{
  QDate d = QDate::currentDate();

  std::cerr << "today: " << d.month() << " " << d.year() << std::endl;

  m_p_schedule->m_month = d.month();
  m_p_schedule->m_year = d.year();

  m_p_schedule->generateCalendar();

  // user event thread
  m_p_schedule->m_p_user_thread->set_username(*m_p_username);
  m_p_schedule->m_p_user_thread->
  set_password(*m_p_password);
  m_p_schedule->m_p_user_thread->set_month(
    QString::number(d.month()));
  m_p_schedule->m_p_user_thread->set_year(
    QString::number(d.year()));

  if (!m_p_schedule->m_p_user_thread->init()) {
    std::cerr << "user event thread did not start" << std::endl;
  }

  // group event thread
  m_p_schedule->m_p_group_thread->set_username(*m_p_username);
  m_p_schedule->m_p_group_thread->
  set_password(*m_p_password);
  m_p_schedule->m_p_group_thread->set_month(
    QString::number(d.month()));
  m_p_schedule->m_p_group_thread->set_year(
    QString::number(d.year()));

  if (!m_p_schedule->m_p_group_thread->init()) {
    std::cerr << "user event thread did not start" << std::endl;
  }
}

void home_screen::to_account_settings()
{
  /**
   * @TODO add request for account info
   */
  m_p_account_settings->m_p_username = m_p_username;
  m_p_account_settings->m_p_password = m_p_password;

  m_p_account_settings->fill_fields();

  m_p_account_settings->show();
  this->hide();
}

void home_screen::to_see_schedule()
{
  /**
   * @TODO add request for user's schedule
   */
  m_p_schedule->m_p_username = m_p_username;
  m_p_schedule->m_p_password = m_p_password;

  m_p_schedule->fromHome();
  m_p_schedule->show();

  this->hide();
}

void home_screen::to_friends_list()
{
  /**
   * @TODO add request for user's schedule
   */
  m_p_friends_list->m_p_username = m_p_username;
  m_p_friends_list->m_p_password = m_p_password;

  m_p_friends_list->fill_fields();

  this->hide();
  m_p_friends_list->show();
}

void home_screen::to_manage_groups()
{
  m_p_manage_groups->m_p_username = m_p_username;
  m_p_manage_groups->m_p_password = m_p_password;

  m_p_manage_groups->fill_fields();

  this->hide();
  m_p_manage_groups->show();
}

void home_screen::to_create_event()
{
  /**
   * @TODO add request to add event
   */
  m_p_create_event->m_p_username = m_p_username;
  m_p_create_event->m_p_password = m_p_password;

  m_p_create_event->show();
  this->hide();
}

void home_screen::from_create_event()
{
  m_p_create_event->hide();
  this->show();
}

void home_screen::from_see_schedule()
{
  m_p_schedule->hide();
  this->show();
}

void home_screen::from_friends_list()
{
  m_p_friends_list->hide();
  this->show();
}

void home_screen::from_manage_groups()
{
  m_p_manage_groups->hide();
  this->show();
}

void home_screen::from_account_settings()
{
  m_p_username = m_p_account_settings->m_p_username;
  m_p_password = m_p_account_settings->m_p_password;
  this->show();
  m_p_account_settings->hide();
}


void home_screen::on_logout()
{
  m_p_schedule->m_p_user_thread->set_username(QString(""));
  m_p_schedule->m_p_user_thread->set_password(QString(""));
  m_p_schedule->m_p_group_thread->set_username(QString(""));
  m_p_schedule->m_p_group_thread->set_password(QString(""));
  m_p_schedule->reset_maps();
  Q_EMIT (return_to_login());
}
