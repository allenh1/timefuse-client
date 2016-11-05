#ifndef CREATEEVENT_H
#define CREATEEVENT_H


#include <QDialog>
#include <QFileDialog>

namespace Ui {
class createevent;
}

class createevent : public QDialog
{
    Q_OBJECT

public:
    explicit createevent(QWidget *parent = 0);
    ~createevent();

private slots:
    void on_pushButton_clicked();

private:
    Ui::createevent *ui;
};

#endif // CREATEEVENT_H
