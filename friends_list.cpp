#include "friends_list.hpp"

friends_list::friends_list(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::friends_list)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

    // connect buttons
	connect(m_p_ui->back_button, &QPushButton::released,
			this, &friends_list::on_back_button);
	connect(m_p_ui->add_friend, &QPushButton::released,
			this, &friends_list::on_add_friend);
    connect(m_p_ui->requests, &QPushButton::released,
            this, &friends_list::goto_friend_requests);
    connect(m_p_ui->delete_friend, &QPushButton::released,
            this, &friends_list::on_delete_friend);
}

friends_list::~friends_list()
{
    delete m_p_ui;
	delete m_p_username;
	delete m_p_password;
}

void friends_list::on_add_friend()
{
    if(m_p_ui->username_input->text().size() == 0) return;
    QString * request = new QString("CREATE_FRIENDSHIP ");

    (*request)+=m_p_username; (*request)+=":::";
    (*request)+=m_p_password; (*request)+=":::";
    (*request)+=m_p_ui->username_input->text();

    QString * response = setup_connection(request);

    std::cerr<<"response: "<<response->toStdString()<<std::endl;

    if(response->contains("OK")) {
        m_p_ui->list_friends->clear();
	    fill_fields();
    } else {
        QMessageBox::critical(this, tr("Error"), *response);
    }

    delete response; delete request;
}

void friends_list::on_delete_friend()
{
    if(m_p_ui->list_friends->currentItem() == NULL) return;
    QString * request = new QString("DELETE_FRIEND ");

    (*request)+=m_p_username; (*request)+=":::";
    (*request)+=m_p_password; (*request)+=":::";
    (*request)+=m_p_ui->list_friends->currentItem()->text();

    QString * response = setup_connection(request);

    std::cerr<<"response: "<<response->toStdString()<<std::endl;

    if(response->contains("OK")) {
        m_p_ui->list_friends->clear();
	    fill_fields();
    } else {
        QMessageBox::critical(this, tr("Error"), *response);
    }

    delete response; delete request;
}

void friends_list::on_back_button()
{
    m_p_ui->list_friends->clear();
	Q_EMIT(return_to_home_screen());
}

void friends_list::goto_friend_requests() {}

void friends_list::fill_fields()
{
	m_p_ui->list_friends->clear();
	QString * request = new QString("REQUEST_FRIENDS ");

    (*request)+=m_p_username; (*request)+=":::";
	(*request)+=m_p_password; (*request)+="\r\n\0";

    QString * response = setup_connection(request);

	if(!response->contains("ERROR")) {
		response->replace("\r\n","");
	    QStringList list = response->split('\n');
		
		for(int i=0;i<list.size();i++) {
			if(i==list.size()-1) continue;
			m_p_ui->list_friends->addItem(list.at(i));
		}
	} delete response; delete request;
}
