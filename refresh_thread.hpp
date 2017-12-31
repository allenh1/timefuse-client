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

#ifndef __REFRESH_THREAD_HPP__
#define __REFRESH_THREAD_HPP__
#include <QTcpSocket>
#include <QString>
#include <QMutex>
#include <iostream>

typedef unsigned int uint;

class refresh_thread : public QObject
{
  Q_OBJECT

public:
  explicit refresh_thread(QObject * _p_parent = NULL);
  virtual ~refresh_thread();

  virtual bool init() {return false;}

  virtual Q_SLOT void run() {}
  virtual Q_SLOT void run_once(QString, QString) {}
  virtual Q_SLOT void run_method() {}

  QString * setup_connection(QString *);
};

#endif
