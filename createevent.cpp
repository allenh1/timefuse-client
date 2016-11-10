#include "createevent.h"

createevent::createevent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createevent)
{
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

void createevent::on_pushButton_clicked()
{

    userCreatedEvent newEvent;
    newEvent.name = ui->lineTitle->displayText();
    newEvent.location = ui->lineLocation->displayText();
    newEvent.beginTime = ui->timeBegin->time();
    newEvent.endTime = ui->timeEnd->time();
    newEvent.timeNegotiable = ui->radioFixed->isChecked();

    QFile *file;

    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Save Event File"), "",
           tr("Event File (*.evt);;All Files (*)"));

    file = new QFile(fileName);
    file->open(QIODevice::WriteOnly);
    file->flush();

    if (!file->open(QIODevice::ReadOnly)) {
                ui->labelText->setText("can't do it");
                return;
    }

    QDataStream out(file);
    out.setVersion(QDataStream::Qt_4_5);
    out << newEvent.name;
    out << newEvent.location;
    out << newEvent.beginTime;
    out << newEvent.endTime;
    out << newEvent.timeNegotiable;



    this->hide();
}
