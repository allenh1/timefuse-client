#ifndef __CREATE_ACCOUNT_WINDOW_HPP__
#define __CREATE_ACCOUNT_WINDOW_HPP__
#include <QtWidgets>
#include <QtGui>

class create_account_window : public QWidget
{
   Q_OBJECT
public:
   explicit create_account_window (QWidget * _p_parent = NULL);
   virtual ~create_account_window();

   Q_SIGNAL void send_create_account(user u);
private:   
};
#endif
