#include "friends_list.hpp"

manage_groups::friends_list(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::friends_list)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

    // connect buttons
	connect(m_p_ui->back_button, &QPushButton::released,
			this, &friends_list::on_back_button);
	connect(m_p_ui->create_new_group, &QPushButton::released,
			this, &friends_list::on_new_group);
    connect(m_p_ui->edit_group, &QPushButton::released,
            this, &friends_list::goto_edit_group);
    connect(m_p_ui->delete_group, &QPushButton::released,
            this, &friends_list::on_delete_group);
    connect(m_p_ui->leave_group, &QPushButton::released,
            this, &friends_list::on_leave_group);
}

manage_groups::~friends_list()
{
    delete m_p_ui;
	delete m_p_username;
	delete m_p_password;
}

void manage_groups::on_leave_group()
{
    if(m_p_ui->list_groups->currentItem() == NULL) return;
    QString * request = new QString("LEAVE_GROUP ");

    (*request)+=m_p_username; (*request)+=":::";
    (*request)+=m_p_password; (*request)+=":::";
    (*request)+=m_p_ui->list_groups->currentItem()->text(); (*request)+=":::";
    (*request)+=m_p_username;

    QString * response = setup_connection(request);

    std::cerr<<"response: "<<response->toStdString()<<std::endl;

    if(response->contains("OK")) {
        m_p_ui->list_groups->clear();
	    fill_fields();
    } else {
        QMessageBox::critical(this, tr("Error"), *response);
    }

    delete response; delete request;
}

void manage_groups::on_delete_group()
{
    if(m_p_ui->list_groups->currentItem() == NULL) return;
    QString * request = new QString("DELETE_GROUP ");

    (*request)+=m_p_username; (*request)+=":::";
    (*request)+=m_p_password; (*request)+=":::";
    (*request)+=m_p_ui->list_groups->currentItem()->text();

    QString * response = setup_connection(request);

    std::cerr<<"response: "<<response->toStdString()<<std::endl;

    if(response->contains("OK")) {
        m_p_ui->list_groups->clear();
	    fill_fields();
    } else {
        QMessageBox::critical(this, tr("Error"), *response);
    }

    delete response; delete request;
}

void manage_groups::on_back_button()
{
    m_p_ui->list_groups->clear();
	Q_EMIT(return_to_home_screen());
}

void manage_groups::goto_edit_group()
{
    if(m_p_ui->list_groups->currentItem() != NULL) {
        (*(m_p_edit_group->m_p_group))=m_p_ui->list_groups->currentItem()->text();
        m_p_edit_group->m_p_username = m_p_username;
        m_p_edit_group->m_p_password = m_p_password;

        m_p_edit_group->fill_fields();

        this->hide();
        m_p_edit_group->show();
    }
}

void manage_groups::fill_fields()
{
	m_p_ui->list_groups->clear();
	QString * request = new QString("REQUEST_GROUPS ");

    (*request)+=m_p_username; (*request)+=":::";
	(*request)+=m_p_password; (*request)+="\r\n\0";

    QString * response = setup_connection(request);

	if(!response->contains("ERROR")) {
		response->replace("\r\n","");
	    QStringList list = response->split('\n');
		
		for(int i=0;i<list.size();i++) {
			if(i==list.size()-1) continue;
			m_p_ui->list_groups->addItem(list.at(i));
		}
	} delete response; delete request;
}
