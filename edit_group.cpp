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

#include "edit_group.hpp"

edit_group::edit_group(QWidget * parent)
: QWidget(parent),
  ui(new Ui::edit_group)
{
  QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
  this->setPalette(qpalette);
  QFont font(QString("Courier"), 10.5, QFont::Thin, false);
  this->setFont(font);

  ui->setupUi(this);

  m_p_username = new QString("");
  m_p_password = new QString("");
  m_p_group = new QString("");

  ui->add_member_input->setPlaceholderText(tr("Enter a username"));
  ui->group_name->setReadOnly(true);

  // connect cancel button
  connect(ui->back_button, &QPushButton::released,
    this, &edit_group::on_back_button);

  // connect add member button
  connect(ui->add_member, &QPushButton::released,
    this, &edit_group::add_a_member);
}

edit_group::~edit_group() {}

void edit_group::on_back_button()
{
  ui->add_member_input->setText("");
  ui->group_name->setText("");
  ui->member_list->clear();
  Q_EMIT (return_to_manage_groups());
}

void edit_group::add_a_member()
{
  if (ui->add_member_input->text().size() == 0) {return;}
  QString * request = new QString("JOIN_GROUP ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += ":::";
  (*request) += ui->group_name->text(); (*request) += ":::";
  (*request) += ui->add_member_input->text();

  QString * response = setup_connection(request);

  std::cerr << "response: " << response->toStdString() << std::endl;

  if (response->contains("OK")) {
    ui->member_list->addItem(ui->add_member_input->text());
    ui->add_member_input->setText("");
  } else {
    QMessageBox::critical(this, tr("Error"), *response);
  }

  delete response; delete request;
}

void edit_group::fill_fields()
{
  ui->group_name->setText(*m_p_group);

  QString * request = new QString("REQUEST_USERS ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += ":::";
  (*request) += *m_p_group;
  (*request) += "\r\n\0";

  QString * response = setup_connection(request);

  if (response->contains("ERROR")) {
    QMessageBox::critical(this, tr("Error"), *response);
  } else {
    response->replace("\r\n", "");
    QStringList list = response->split('\n');

    for (int i = 0; i < list.size(); i++) {
      if (i == list.size() - 1) {continue;}
      ui->member_list->addItem(list.at(i));
    }
  } delete request; delete response;
}
