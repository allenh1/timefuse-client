#include "create_account_window.hpp"
#include "ui_create_account_window.h"

/*create_account_window::~create_account_window()
{ /* free things */ }*/

create_account_window::create_account_window(QWidget *parent) :
QWidget(parent),
ui(new Ui::create_account_window)
{
    ui->setupUi(this);
}

create_account_window::~create_account_window()
{
    delete ui;
}
