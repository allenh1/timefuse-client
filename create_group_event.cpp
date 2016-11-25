#include "create_group_event.hpp"

create_group_event::create_group_event(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::create_group_event)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

    m_p_ui->group_to_add->setPlaceholderText(tr("Enter a group name"));
	m_p_ui->duration_input->setPlaceholderText(tr("in minutes"));
	m_p_ui->title_input->setPlaceholderText(tr("Group event name"));
	m_p_ui->location_input->setPlaceholderText(tr("Group event location"));

	// connect buttons
	connect(m_p_ui->cancel, &QPushButton::released,
			this, &create_group_event::on_cancel);
	connect(m_p_ui->add_member, &QPushButton::released,
			this, &create_group_event::add_group_members);
	connect(m_p_ui->create_event, &QPushButton::released,
			this, &create_group_event::on_create_group_event);
}

create_group_event::~create_group_event()
{
    delete m_p_ui;
	delete m_p_username;
	delete m_p_password;
}

void create_group_event::on_cancel()
{
	m_p_ui->group_to_add->setText("");
	m_p_ui->title_input->setText("");
	m_p_ui->location_input->setText("");
	m_p_ui->duration_input->setText("");

	QTime def(0,0);
	m_p_ui->begin_time_edit->setTime(def);

	m_p_ui->attendees_list->clear();

	Q_EMIT(return_to_home_screen());
}

void create_group_event::add_group_members()
{
	if(m_p_ui->group_to_add->text().size()==0) return;
	
	QString * request = new QString("REQUEST_USERS ");

	(*request)+=m_p_username; (*request)+=":::";
	(*request)+=m_p_password; (*request)+=":::";
	(*request)+=m_p_ui->group_to_add->text();
	(*request)+="\r\n\0";

	QString * response = setup_connection(request);

	if(response->contains("ERROR")) {
		QMessageBox::critical(this, tr("Error"), *response);
	} else {
		response->replace("\r\n","");
	    QStringList list = response->split('\n');
		
		for(int i=0;i<list.size();i++) {
			if(i==list.size()-1) continue;
			m_p_ui->attendees_list->addItem(list.at(i));
		}
	} delete request; delete response;
}

void create_group_event::on_create_group_event()
{
    QString * request = new QString("CREATE_GROUP_EVENT ");
	
    int year = m_p_ui->dateEdit->date().year();
    int day = m_p_ui->dateEdit->date().day();
    int month = m_p_ui->dateEdit->date().month();
    int hour = m_p_ui->begin_time_edit->time().hour();
    int minute = m_p_ui->begin_time_edit->time().minute();
	
    (*request)+=m_p_username; (*request)+=":::";
    (*request)+=m_p_password; (*request)+=":::";
    (*request)+=m_p_ui->group_to_add->displayText(); (*request)+=":::";
    (*request)+=QString::number(year); (*request)+='-';
    (*request)+=QString::number(month); (*request)+='-';
    (*request)+=QString::number(day); (*request)+=":::";
    (*request)+=QString::number(hour); (*request)+=':';
    (*request)+=QString::number(minute).rightJustified(2, '0'); (*request)+=":::";
    (*request)+=m_p_ui->duration_input->displayText(); (*request)+=":::";
    (*request)+=m_p_ui->location_input->displayText(); (*request)+=":::";
    (*request)+=m_p_ui->title_input->displayText(); (*request)+="\r\n\0";

	std::cerr<<"request: "<<request->toStdString()<<std::endl;
    QString * response = setup_connection(request);
	std::cerr<<"response: "<<response->toStdString()<<std::endl;

	if(response->contains("ERROR")) {
		QMessageBox::critical(this, tr("Error"), *response);
	} else {
		m_p_ui->group_to_add->setText("");
		m_p_ui->title_input->setText("");
		m_p_ui->location_input->setText("");
		m_p_ui->duration_input->setText("");

		QTime def(0,0);
		m_p_ui->begin_time_edit->setTime(def);
		m_p_ui->attendees_list->clear();
		Q_EMIT(return_to_home_screen());
	} delete response; delete request;
}
