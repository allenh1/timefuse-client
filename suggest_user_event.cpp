#include "suggest_user_event.hpp"

suggest_user_event::suggest_user_event(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::suggest_user_event)
{
	QFont font(QString("Courier"), 12, QFont::Thin, false);
	this->setFont(font);
		
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

	m_p_ui->duration_input->setPlaceholderText(tr("in minutes"));

	// connect buttons
	connect(m_p_ui->cancel, &QPushButton::released,
			this, &suggest_user_event::on_cancel);
	connect(m_p_ui->select_time, &QPushButton::released,
			this, &suggest_user_event::on_select_time);
    connect(m_p_ui->suggest_times, &QPushButton::released,
            this, &suggest_user_event::suggest_a_time);
}

suggest_user_event::~suggest_user_event()
{
    delete m_p_ui;
	delete m_p_username;
	delete m_p_password;
}

void suggest_user_event::on_cancel()
{
	m_p_ui->duration_input->setText("");
	m_p_ui->begin_time_edit->setTime(QTime(0,0));
	m_p_ui->time_list->clear();

	Q_EMIT(return_to_event());
}

void suggest_user_event::suggest_a_time()
{
	m_p_ui->time_list->clear();
	
	int year = m_p_ui->dateEdit->date().year();
    int day = m_p_ui->dateEdit->date().day();
    int month = m_p_ui->dateEdit->date().month();
	int hour = m_p_ui->begin_time_edit->time().hour();
    int minute = m_p_ui->begin_time_edit->time().minute();

	QString * request = new QString("SUGGEST_TIMES ");
	(*request)+=*m_p_username + ":::" + *m_p_password + ":::";
	(*request)+=QString::number(year) + "-" + QString::number(month)
		+ "-" + QString::number(day) + ":::" + QString::number(hour)
		+ ":" + QString::number(minute) + ":::";
	(*request)+=m_p_ui->duration_input->text();
	std::cerr<<"request: "<<request->toStdString()<<std::endl;
	QString * response = setup_connection(request);

	if(!response->contains("ERROR")) {
		response->replace("\r\n","");
	    QStringList list = response->split('\n');

		if(list.at(0).size()==0) {
			QMessageBox::critical(this, tr("Error"),
								  QString("NO TIMES FOUND!"));
		} for(int i=0;i<list.size();i++) {
			if(i==list.size()-1) continue;
			if(list.at(i).size()==0) continue;
			m_p_ui->time_list->addItem(list.at(i));
		} 
	} else {
		QMessageBox::critical(this, tr("Error"), *response);
	} delete response; delete request;
}

void suggest_user_event::on_select_time()
{
	if(m_p_ui->time_list->currentItem() == NULL) return;
    Q_EMIT(return_time(m_p_ui->time_list->currentItem()->text()));
}
