#include "schedulinggrid.h"


schedulingGrid::schedulingGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::schedulingGrid)
{
    ui->setupUi(this);
    ui->tableCalendar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    schedulingGrid::on_pushCalendar_clicked();

	m_p_username = new QString("");
	m_p_password = new QString("");

	connect(ui->back_button, &QPushButton::released,
			this, &schedulingGrid::on_back_button);
}

schedulingGrid::~schedulingGrid()
{
    delete ui;
	delete m_p_username;
	delete m_p_password;
}
/*
QLineEdit* schedulingGrid::month()
{
    return ui->lineMonth;
}
*/
QString months[]=
{
    "",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

QString daysOfWeek[]=
{
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday",
    "Friday",
    "Saturday"
};

// This will show how to properly color in the calender
//
// void schedulingGrid::colorCalender()
// {
// First, send in the query.

// QString * request = new QString("REQUEST_PERSONAL_MONTH_EVENTS  ");
// (*request)+=m_p_username; (*request)+=':';
// (*request)+=m_p_password; (*request)+=':';
// (*request)+=ui->lineMonth->displayText(); (*request)+=':';
// (*request)+=ui->lineYear->displayText();
// QString * response = setup_connection(request);
//
// QChar eventsAtDay;
//
// I'm tired so the rest is psuedocode
// for i = , number of days in month, i++
//  eventsAtDay = response[i-1]
//  int pos = i + daycode of the current month (how many days before the first)
//  int row = pos/7 + (daycode == 0);
//  int col = pos%7;
//  if eventsAtDay == 1
//    mark today as having an event
//    tableWidget->item(row,col)->setBackgroundColor(Qt::red);
// }

// kind of a simple way of doing it
// maybe group events can be a different color?
// maybe a day that has both personal and group events can be an even different color?





// This will show how I think we can load in the schedule itself
// void schedulingGrid::fillSchedule()
// {
// int currentRow = ui->tableCalendar->currentRow();
// int firstDay = ui->tableCalendar->item(currentRow, 0)->text();
// int lastDay = ui->tableCalendar->item(currentRow, 6)->text();
// those will give the range of days needed for the REQUEST_EVENTS query
//
// loop for all returned events:
//  get start date of event
//  add it as an item to the QListWidget with the corresponding date
// end loop:
// }
//
// obviously this is only a temporary solution, but it should be fine for now

void schedulingGrid::on_pushCalendar_clicked()
{

    //because the built in QCalendarWidget has little room for flexibility, we will be making our own calendar in a table

    bool ok;

    //get the year and month of the calendar
    int year = (ui->lineYear->displayText()).toInt(&ok,10);
    int month = (ui->lineMonth->displayText()).toInt(&ok,10);

    //do math to figure out what day of the week the year starts on
    int d1 = (year - 1.)/ 4.0;
    int d2 = (year - 1.)/ 100.;
    int d3 = (year - 1.)/ 400.;

    int daycode = (year + d1 - d2 + d3) %7;



    int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};

    //if the year is a leap year, account for that
    if( (year%4 == 0 && year%100 != 0) || year%400 == 0) {
        days_in_month[2] = 29;
    } else {
        days_in_month[2] = 28;
    }

    //what day of the week does the selected month start on?
    //might be a better way to do this
    for(int i = 1; i <= month; i++) {
        daycode = ( daycode + days_in_month[i-1] ) % 7;
    }

    //qCalendarWidget will skip a row if the month starts on a Monday, so I copy that behavior
    if (daycode == 0) {
        daycode = 7;
    }

    //set the calendar's title
    ui->label->setText(months[month] + ", " + QString::number(year));

    int currentDate = 1;

    //the only way I could figure out how to set text for a spot in a table is to use a QTableWidgetItem object.
    //I don't know how QT handles these in memory, if I should be clearing these before changing the view.
    //because 42 objects seems like a lot?

    //filler until the first day of the month
    for (int i = 0; i < daycode; i++) {

        QTableWidgetItem *twi = new QTableWidgetItem("-");
        ui->tableCalendar->setItem(0, i, twi);
    }

    //fill in the calendar
    for (int i = daycode; i < days_in_month[month] + daycode; i++) {

        //easy way to calculate where in the grid we are
        int currentDay = i%7;
        int currentWeek = i/7 + (daycode == 0);

        QTableWidgetItem *twi = new QTableWidgetItem(QString::number(currentDate));

        ui->tableCalendar->setItem(currentWeek, currentDay, twi);

        currentDate++;
    }

    //filler until the end of the calendar
    for (int i = currentDate + daycode - 1; i < 6*7; i++) {

        int currentDay = i%7;
        int currentWeek = i/7 + (daycode == 0);

        QTableWidgetItem *twi = new QTableWidgetItem("-");
        ui->tableCalendar->setItem(currentWeek, currentDay, twi);
    }

    //I don't know yet how I want to change to weekly or daily views.
    //It might be easier to just create different tables, rather than keep on trying to
    //modify the same one.


}



void schedulingGrid::on_pushLeft_clicked()
{
    //for now these two buttons hijack the text fields.

    bool ok;
    int year = (ui->lineYear->displayText()).toInt(&ok,10);
    int month = (ui->lineMonth->displayText()).toInt(&ok,10);

    if (month != 1) {
        ui->lineMonth->setText(QString::number(month - 1));
    } else {
        ui->lineYear->setText(QString::number(year - 1));
        ui->lineMonth->setText(QString::number(12));
    }

    schedulingGrid::on_pushCalendar_clicked();
}

void schedulingGrid::on_pushRight_clicked()
{
    bool ok;
    int year = (ui->lineYear->displayText()).toInt(&ok,10);
    int month = (ui->lineMonth->displayText()).toInt(&ok,10);

    if (month != 12) {
        ui->lineMonth->setText(QString::number(month + 1));
    } else {
        ui->lineYear->setText(QString::number(year + 1));
        ui->lineMonth->setText(QString::number(1));
    }

    schedulingGrid::on_pushCalendar_clicked();
}

void schedulingGrid::on_pushGetDay_clicked()
{
    int currentRow = ui->tableCalendar->currentRow();
    int currentColumn = ui->tableCalendar->currentColumn();

    bool ok;

    int year = (ui->lineYear->displayText()).toInt(&ok,10);
    int month = (ui->lineMonth->displayText()).toInt(&ok,10);



    //QString day = ui->tableWeek->horizontalHeaderItem(ui->tableWeek->currentColumn())->text();
    //int row = ui->tableWeek->currentRow();
    //QString time = ui->tableWeek->verticalHeaderItem(ui->tableWeek->currentRow())->text();
    //QString time = "0:00";

    /*if (day == "-") {
        ui->labelCurrentDay->setText("idk man");
    } else {
        ui->labelCurrentDay->setText(daysOfWeek[currentColumn] + ", " +
                                     months[month] + " " + day + ", " +
                                     QString::number(year) + " @ " + time);
    }*/
}

void schedulingGrid::on_pushWeek_clicked()
{
    QStringList days;



    int currentRow = ui->tableCalendar->currentRow();

    for(int i = 0; i < 7; i++) {
        QString currentDay = ui->lineMonth->displayText();
        currentDay += "/";
        currentDay += ui->tableCalendar->item(currentRow, i)->text();
        days << currentDay;

    }

    ui->labelSunday->setText(days[0]);
    ui->labelMonday->setText(days[1]);
    ui->labelTuesday->setText(days[2]);
    ui->labelWednesday->setText(days[3]);
    ui->labelThursday->setText(days[4]);
    ui->labelFriday->setText(days[5]);
    ui->labelSaturday->setText(days[6]);
}

void schedulingGrid::on_pushCreateEvent_clicked()
{
    createevent ce;
	ce.m_p_username = m_p_username;
	ce.m_p_password = m_p_password;
    ce.setModal(true);
    ce.exec();
}

void schedulingGrid::on_back_button()
{
	Q_EMIT(return_to_home_screen());
}
