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

#include "add_group.h"

add_group::add_group(QWidget * parent)
: QWidget(parent),
  ui(new Ui::add_group)
{
  QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
  this->setPalette(qpalette);
  QFont font(QString("Courier"), 10.5, QFont::Thin, false);
  this->setFont(font);

  ui->setupUi(this);

  m_p_username = new QString("");
  m_p_password = new QString("");

  ui->add_member_input->setPlaceholderText(
    tr("Enter a username"));
  ui->group_name->setPlaceholderText(tr("Group name"));

  // connect cancel button
  connect(ui->back_button, &QPushButton::released,
    this, &add_group::on_back_button);

  // connect add member button
  connect(ui->add_member, &QPushButton::released,
    this, &add_group::add_a_member);

  // connect create group button
  connect(ui->add_group_button, &QPushButton::released,
    this, &add_group::create_group);
}

add_group::~add_group() {}

void add_group::on_back_button()
{
  ui->add_member_input->setText("");
  ui->group_name->setText("");
  ui->member_list->clear();
  Q_EMIT (return_to_manage_groups());
}

void add_group::create_group()
{
  if (ui->group_name->text().size() == 0) {return;}

  QString * request = new QString("CREATE_GROUP ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += ":::";
  (*request) += ui->group_name->text();

  QString * response = setup_connection(request);

  if (response->contains("ERROR")) {
    QMessageBox::critical(this, tr("Error"), *response);
    delete response; delete request;
    return;
  } else if (response->contains("OK")) {
    std::cerr << "response: " << response->toStdString() << std::endl;

    // go through member list and to group
    for (int i = 0; i < ui->member_list->count(); i++) {
      add_user(ui->member_list->item(i)->text());
    }
    delete response; delete request;

    add_user(*m_p_username);

    // clear fields and switch back to manage groups
    ui->add_member_input->setText("");
    ui->group_name->setText("");
    ui->member_list->clear();
    Q_EMIT (return_to_manage_groups());
  }
}

void add_group::add_user(QString user)
{
  QString * request = new QString("JOIN_GROUP ");

  (*request) += m_p_username; (*request) += ":::";
  (*request) += m_p_password; (*request) += ":::";
  (*request) += ui->group_name->text(); (*request) += ":::";
  (*request) += user;

  QString * response = setup_connection(request);

  std::cerr << "response: " << response->toStdString() << std::endl;
  delete response; delete request;
}


void add_group::add_a_member()
{
  ui->member_list->addItem(ui->add_member_input->text());
  ui->add_member_input->setText("");
}
