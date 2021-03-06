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

#include "suggest_user_event.hpp"

suggest_user_event::suggest_user_event(QWidget * parent)
: QWidget(parent),
  m_p_ui(new Ui::suggest_user_event)
{
  QFont font(QString("Courier"), 12, QFont::Thin, false);
  this->setFont(font);

  m_p_ui->setupUi(this);

  m_p_username = new QString("");
  m_p_password = new QString("");

  /* TODO(allenh1): add this functionality back in */
  // m_p_ui->->setPlaceholderText(tr("in minutes"));

  // connect buttons
  connect(m_p_ui->cancel, &QPushButton::released,
    this, &suggest_user_event::on_cancel);
  connect(m_p_ui->select_time, &QPushButton::released,
    this, &suggest_user_event::on_select_time);
  connect(m_p_ui->suggest_times, &QPushButton::released,
    this, &suggest_user_event::suggest_a_time);
}

suggest_user_event::~suggest_user_event() {}

void suggest_user_event::on_cancel()
{
  m_p_ui->end_time->setText("");
  m_p_ui->begin_time_edit->setTime(QTime(0, 0));
  m_p_ui->time_list->clear();

  Q_EMIT (return_to_event());
}

void suggest_user_event::suggest_a_time()
{
  m_p_ui->time_list->clear();

  int year = m_p_ui->dateEdit->date().year();
  int day = m_p_ui->dateEdit->date().day();
  int month = m_p_ui->dateEdit->date().month();
  int hour = m_p_ui->begin_time_edit->time().hour();
  int minute = m_p_ui->begin_time_edit->time().minute();

  QString * request = new QString("SUGGEST_TIMES ");
  (*request) += *m_p_username + ":::" + *m_p_password + ":::";
  (*request) += QString::number(year) + "-" + QString::number(month) +
    "-" + QString::number(day) + ":::" + QString::number(hour) +
    ":" + QString::number(minute) + ":::";
  (*request) += m_p_ui->end_time->text();
  std::cerr << "request: " << request->toStdString() << std::endl;
  QString * response = setup_connection(request);

  if (!response->contains("ERROR")) {
    response->replace("\r\n", "");
    QStringList list = response->split('\n');

    if (list.at(0).size() == 0) {
      QMessageBox::critical(this, tr("Error"),
        QString("NO TIMES FOUND!"));
    }
    for (int i = 0; i < list.size(); i++) {
      if (list.at(i).size() == 0) {continue;}
      m_p_ui->time_list->addItem(list.at(i));
    }
  } else {
    QMessageBox::critical(this, tr("Error"), *response);
  } delete response; delete request;
}

void suggest_user_event::on_select_time()
{
  if (m_p_ui->time_list->currentItem() == NULL) {return;}
  Q_EMIT (return_time(m_p_ui->time_list->currentItem()->text()));
}
