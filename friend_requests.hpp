#ifndef FRIEND_REQUESTS_HPP
#define FRIEND_REQUESTS_HPP

#include <QMessageBox>
#include <QStringList>
#include <iostream>
#include <QWidget>
#include <QTest>
#include "ui_friend_requests.h"
#include "tcp_connection.hpp"

namespace Ui
{
class friend_requests;
}

class friend_requests : public QWidget
{
  Q_OBJECT

public:
  explicit friend_requests(QWidget * _p_parent = NULL);
  virtual ~friend_requests();

  QString * m_p_username;
  QString * m_p_password;

  Q_SIGNAL void return_to_friends();
  void fill_fields();

private:
  Ui::friend_requests * m_p_ui;

  Q_SLOT void on_delete_friend();
  Q_SLOT void on_add_friend();
  Q_SLOT void on_back_button();
};

#endif
