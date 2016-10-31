#include "add_group.h"
#include "ui_add_group.h"

add_group::add_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_group)
{
    ui->setupUi(this);
}

add_group::~add_group()
{
    delete ui;
}
