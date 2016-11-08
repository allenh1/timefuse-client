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

	QString * m_p_username;
	QString * m_p_password;

	Q_SIGNAL void return_to_manage_groups();
private:
    Ui::add_group *ui;

	Q_SLOT void on_back_button();
};

#endif // ADD_GROUP_H
