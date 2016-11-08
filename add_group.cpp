#include "add_group.h"
#include "ui_add_group.h"

add_group::add_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_group)
{
    ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

	connect(ui->back_button, &QPushButton::released,
			this, &add_group::on_back_button);
}

add_group::~add_group()
{
    delete ui;
}

void add_group::on_back_button()
{
	Q_EMIT(return_to_manage_groups());
}
