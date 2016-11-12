#include "createevent.h"

createevent::createevent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createevent)
{
    ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

    //ui->labelDate->setText(schedulingGrid->month()->displayText());

}

createevent::~createevent()
{
    delete ui;
	delete m_p_username;
	delete m_p_password;
}

void createevent::on_pushButton_clicked()
{

    QString * request = new QString("CREATE_USER_EVENT ");
    int year = ui->dateEdit->date().year();
    int day = ui->dateEdit->date().day();
    int month = ui->dateEdit->date().month();
    int hour = ui->begin_time_edit_2->time().hour();
    int minute = ui->begin_time_edit_2->time().minute();

	// same thing here
	
    (*request)+=m_p_username; (*request)+=';';
    (*request)+=m_p_password; (*request)+=';';
    (*request)+=QString::number(year); (*request)+='-';
    (*request)+=QString::number(month); (*request)+='-';
    (*request)+=QString::number(day); (*request)+=';';
    (*request)+=QString::number(hour); (*request)+=':';
    (*request)+=QString::number(minute).rightJustified(2, '0'); (*request)+=';';
    (*request)+=ui->duration_input_2->displayText(); (*request)+=';';
    (*request)+=ui->location_input_2->displayText(); (*request)+=';';
    (*request)+=ui->title_input_2->displayText();

    QString * response = setup_connection(request);
    ui->label->setText(*request);
    ui->label_2->setText(*response);




    //this->hide();
}
