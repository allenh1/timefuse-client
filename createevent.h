#ifndef CREATEEVENT_H
#define CREATEEVENT_H

#include <QDialog>
#include <QString>
#include <QFileDialog>

#include "ui_createevent.h"
#include "usercreatedevent.h"

namespace Ui {
class createevent;
}

class createevent : public QDialog
{
    Q_OBJECT

public:
    explicit createevent(QWidget *parent = 0);
    ~createevent();

	QString * m_p_username;
	QString * m_p_passowrd;

private slots:
    void on_pushButton_clicked();

private:
    Ui::createevent *ui;
};

#endif // CREATEEVENT_H
