#ifndef MANAGE_GROUPS_HPP
#define MANAGE_GROUPS_HPP

#include <QWidget>

namespace Ui {
class manage_groups;
}

class manage_groups : public QWidget
{
    Q_OBJECT

public:
    explicit manage_groups(QWidget * _p_parent = NULL);
    virtual ~manage_groups();

private:
    Ui::manage_groups * m_p_ui;
};

#endif
