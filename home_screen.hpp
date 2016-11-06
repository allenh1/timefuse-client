#ifndef HOME_SCREEN_HPP
#define HOME_SCREEN_HPP

#include <QWidget>
#include <QtGui>


namespace Ui {
class home_screen;
}

class home_screen : public QWidget
{
    Q_OBJECT

public:
    explicit home_screen(QWidget *_p_parent = NULL);
    virtual ~home_screen();

private:
    Ui::home_screen *m_p_ui;
};

#endif // HOME_SCREEN_H
