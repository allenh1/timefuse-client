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

#include "suggested_time.hpp"

suggested_time::suggested_time(QWidget * parent)
: QWidget(parent),
  m_p_ui(new Ui::suggested_time)
{
  QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
  this->setPalette(qpalette);
  QFont font(QString("Courier"), 10.5, QFont::Thin, false);
  this->setFont(font);

  m_p_ui->setupUi(this);

  m_p_username = new QString("");
  m_p_password = new QString("");

  m_p_start_date = new QString("");
  m_p_duration = new QString("");
  m_p_finish_time = new QString("");
  m_p_group_name = new QString("");

  m_p_selected_time = new QString("");

  // connect buttons
  connect(m_p_ui->back_button, &QPushButton::released,
    this, &suggested_time::on_back_button);
  connect(m_p_ui->select_time, &QPushButton::released,
    this, &suggested_time::on_selected_time);
}

suggested_time::~suggested_time() {}

void suggested_time::on_selected_time()
{
  if (m_p_ui->list_times->currentItem() == NULL) {return;}
  (*m_p_selected_time) = m_p_ui->list_times->currentItem()->text();
  on_back_button();
}

void suggested_time::on_back_button()
{
  m_p_ui->list_times->clear();
  Q_EMIT (return_to_group_event());
}

void suggested_time::fill_fields()
{
  m_p_ui->list_times->clear();

  QString * request = new QString("REQUEST_TIMES ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += ":::";
  (*request) += m_p_group_name; (*request) += ":::";
  (*request) += m_p_start_date; (*request) += ":::";
  (*request) += *m_p_finish_time + ":::";
  (*request) += m_p_duration; (*request) += "\r\n\0";
  QString * response = setup_connection(request);
  /**
   * @todo handle error responses
   */
  if (!response->contains("ERROR")) {
    response->replace("\r\n", "");
    QStringList list = response->split('\n');

    for (int i = 0; i < list.size(); i++) {
      if (list.at(i).size() == 0) {continue;}
      m_p_ui->list_times->addItem(list.at(i));
    }
  }
  delete response; delete request;
}
