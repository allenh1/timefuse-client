#ifndef ADD_GROUP_HPP
#define ADD_GROUP_HPP

#include <QWidget>

namespace Ui {
class add_group;
}

class add_group : public QWidget
{
    Q_OBJECT

public:
    explicit add_group(QWidget *parent = 0);
    ~add_group();

private:
    Ui::add_group *ui;
};

#endif // ADD_GROUP_H
