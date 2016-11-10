#include "edit_group.hpp"

edit_group::edit_group(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_group)
{
    ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");
    m_p_group = new QString("");

	ui->add_member_input->setPlaceholderText(tr("Enter a username"));
    ui->group_name->setReadOnly(true);

	// connect cancel button
	connect(ui->back_button, &QPushButton::released,
            this, &edit_group::on_back_button);

	// connect add member button
	connect(ui->add_member, &QPushButton::released,
            this, &edit_group::add_a_member);
}

edit_group::~edit_group()
{
    delete ui;
}

void edit_group::on_back_button()
{
	ui->add_member_input->setText("");
	ui->group_name->setText("");
	ui->member_list->clear();
	Q_EMIT(return_to_manage_groups());
}

void edit_group::add_a_member()
{
    if(ui->add_member_input->text()->size() == 0) return;
    QString * request = new QString("JOIN_GROUP ");

    (*request)+=m_p_username; (*request)+=':';
    (*request)+=m_p_password; (*request)+=':';
    (*request)+=ui->group_name->text(); (*request)+=':';
    (*request)+=encrypt_string(ui->add_member_input->text());

    QString * response = setup_connection(request);

    std::cerr<<"response: "<<response->toStdString()<<std::endl;

    if(response->contains("OK")) {
        ui->member_list->addItem(ui->add_member_input->text());
        ui->add_member_input->setText("");
    } else {
        QMessageBox::critical(this, tr("Error"), *response);
    }

    delete response; delete request;
}

void edit_group::fill_fields()
{
    ui->group_name->setText(*m_p_group);
}
