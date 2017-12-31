#ifndef SUGGEST_USER_EVENT_HPP
#define SUGGEST_USER_EVENT_HPP

#include <QWidget>
#include <QTimeEdit>
#include <iostream>
#include <QTime>
#include <QMessageBox>

#include "ui_suggest_user_event.h"
#include "tcp_connection.hpp"

namespace Ui
{
class suggest_user_event;
}

class suggest_user_event : public QWidget
{
  Q_OBJECT

public:
  explicit suggest_user_event(QWidget * _p_parent = NULL);
  virtual ~suggest_user_event();

  QString * m_p_username;
  QString * m_p_password;

  Q_SIGNAL void return_to_event();
  Q_SIGNAL void return_time(QString);

private:
  Ui::suggest_user_event * m_p_ui;

  Q_SLOT void on_cancel();
  Q_SLOT void on_select_time();
  Q_SLOT void suggest_a_time();
};

#endif
