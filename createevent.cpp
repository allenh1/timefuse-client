#include "createevent.hpp"

createevent::createevent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createevent)
{
	QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
	this->setPalette(qpalette);
	QFont font(QString("Courier"), 10.5, QFont::Thin, false);
	this->setFont(font);
	
    ui->setupUi(this);

    m_p_username = new QString("");
    m_p_password = new QString("");
}

createevent::~createevent()
{
    delete ui;
    delete m_p_username;
    delete m_p_password;
}

void createevent::changeDate()
{
    ui->dateEdit->setDate(selected);
}

void createevent::on_pushButton_clicked()
{
    QString * request = new QString("CREATE_USER_EVENT ");
    int year = ui->dateEdit->date().year();
    int day = ui->dateEdit->date().day();
    int month = ui->dateEdit->date().month();
    int hour = ui->begin_time_edit_2->time().hour();
    int minute = ui->begin_time_edit_2->time().minute();

    int fixed = 1;
    if (ui->radioNegotiable->isChecked()) {
        fixed = 0;
    }

    /* create the request */
    (*request) += *m_p_username + ":::" + *m_p_password + ":::"
		+ QString::number(year) + "-" + QString::number(month)
		+ "-" + QString::number(day) + ":::" + QString::number(hour)
		+ ":" + QString::number(minute).rightJustified(2, '0')
		+ ":::" + ui->duration_input_2->displayText() + ":::"
		+ ui->location_input_2->displayText() + ":::"
		+ QString::number(ui->timezoneOffset->value())
		+ ":::" + ui->title_input_2->displayText()
		+ ":::" + QString::number(fixed);
    (*request)+=QString::number(fixed);

    QString * response = setup_connection(request);
    std::cerr<<"response: "<<response->toStdString()<<std::endl;

    if(response->contains("ERROR")) QMessageBox::critical(this, tr("Error"), *response);
	else Q_EMIT(return_to_schedule());
}

void createevent::on_pushCancel_clicked()
{
    Q_EMIT(return_to_schedule());
}
