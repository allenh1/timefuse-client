#include "schedulinggrid.hpp"

schedulingGrid::schedulingGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::schedulingGrid)
{
    ui->setupUi(this);
    ui->tableCalendar->setEditTriggers(QAbstractItemView::NoEditTriggers);
    schedulingGrid::on_pushCalendar_clicked();
    //ui->tableWeek->horizontalHeaderItem(0)->setText("Whatever");

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

/* This will show how to properly color in the calender */

void schedulingGrid::colorCalender()
{
	/* First, send in the query. */
	
	QString * request = new QString("REQUEST_PERSONAL_MONTH_EVENTS ");
	(*request)+=m_p_username; (*request)+=':';
	(*request)+=m_p_password; (*request)+=':';
	(*request)+=ui->lineMonth->displayText(); (*request)+=':';
	(*request)+=ui->lineYear->displayText(); bool ok;
	QString * response = setup_connection(request);
	ushort month = (ui->lineYear->displayText()).toInt(&ok, 10);
	uint year = (ui->lineYear->displayText()).toInt(&ok,10);
	int occupied_days = response->split("\n")[0].toInt();

	/* convert response to an int */
	ushort C = std::floor(year / 100); ushort m = month - 2;
	if (month == 1) m = 11; else if (month == 2) m = 12;
	ushort Y = ((month == 1 || month == 2) ? year - 1 : year) - C * 100;
	/* this number is hot yall */
	std::cout<<"(C, Y, m) = ("<<C<<","<<Y<<","<<m<<")"<<std::endl;
    int dc = (int) (1 + std::floor(2.6 * m - 0.2) - 2 * C
			  + Y + std::floor(Y / 4.0) + std::floor(C / 4.0)) % 7;	
	register uint daycode = (dc < 0) ? dc + 7 : dc;
	for (int x = daycode; occupied_days; occupied_days >>= 1, ++x) {
		/* if the bit is set, fill the cooresponding day */
		if (occupied_days & 1) {
			ui->tableCalendar->item((x + daycode) / 7,
									((x + daycode) % 7))->setBackgroundColor(Qt::red);
		}
	}
// I'm tired so the rest is psuedocode
// for i = , number of days in month, i++
//  eventsAtDay = response[i-1]
//  int pos = i + daycode of the current month (how many days before the first)
//  int row = pos/7 + (daycode == 0);
//  int col = pos%7;
//  if eventsAtDay == 1
//    mark today as having an event
//    tableWidget->item(row,col)->setBackgroundColor(Qt::red);
}

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
//
//
// obviously this is only a temporary solution, but it should be fine for now

void schedulingGrid::on_pushCalendar_clicked()
{
    /**
	 * because the built in QCalendarWidget has little room for
	 * flexibility, we will be making our own calendar in a table
	 */

    bool ok; static int calls = 0;

    //get the year and month of the calendar
    uint year = (ui->lineYear->displayText()).toInt(&ok,10);
    ushort month = (ui->lineMonth->displayText()).toInt(&ok,10);
	ushort days_in_month[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    //do math to figure out what day of the week the year starts on
	ushort C = std::floor(year / 100); ushort m = month - 2;
	if (month == 1) m = 11; else if (month == 2) m = 12;
	ushort Y = ((month == 1 || month == 2) ? year - 1 : year) - C * 100;
	/* this number is hot yall */
	std::cout<<"(C, Y, m) = ("<<C<<","<<Y<<","<<m<<")"<<std::endl;
    int dc = (int) (1 + std::floor(2.6 * m - 0.2) - 2 * C
			  + Y + std::floor(Y / 4.0) + std::floor(C / 4.0)) % 7;	
	register uint daycode = (dc < 0) ? dc + 7 : dc;
	std::cout<<"Daycode: "<<daycode<<std::endl;
    //if the year is a leap year, account for that
    if((!(year % 4) && (year%100)) || !(year % 400)) days_in_month[2] = 29;

    //qCalendarWidget will skip a row if the month starts on a Monday, so I copy that behavior
    if (daycode == 0) daycode = 7;

    //set the calendar's title
    ui->label->setText(months[month] + ", " + QString::number(year));

    int currentDate = 1;

    //the only way I could figure out how to set text for a spot in a table is to use a QTableWidgetItem object.
    //I don't know how QT handles these in memory, if I should be clearing these before changing the view.
    //because 42 objects seems like a lot?

    //filler until the first day of the month
    for (uint i = 0; i < daycode; i++) {
        QTableWidgetItem *twi = new QTableWidgetItem("-");
        ui->tableCalendar->setItem(0, i, twi);
    }

    //fill in the calendar
    for (uint i = daycode; i < days_in_month[month] + daycode; i++) {

        //easy way to calculate where in the grid we are
        int currentDay = i % 7;
        int currentWeek = i / 7 + (daycode == 0);

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
    } if (calls) colorCalender();
	++calls;
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
	colorCalender();
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
	colorCalender();
    schedulingGrid::on_pushCalendar_clicked();
}

void schedulingGrid::on_pushGetDay_clicked()
{
    /* int currentRow = ui->tableCalendar->currentRow(); */
    /* int currentColumn = ui->tableCalendar->currentColumn(); */

    /* bool ok; */

    /* int year = (ui->lineYear->displayText()).toInt(&ok,10); */
    /* int month = (ui->lineMonth->displayText()).toInt(&ok,10); */



    // QString day = ui->tableWeek->horizontalHeaderItem(ui->tableWeek->currentColumn())->text();
    // int row = ui->tableWeek->currentRow();
    // QString time = ui->tableWeek->verticalHeaderItem(ui->tableWeek->currentRow())->text();
    // QString time = "0:00";
}

void schedulingGrid::on_pushWeek_clicked()
{
    QStringList days;
    int startDay = -1;
    int endDay = -1;

    QString currentDay;
    int currentRow = ui->tableCalendar->currentRow();
    //days << "K" << "E" << "N" << "D" << "A" << "L" << "L" ;

    for(int i = 0; i < 7; i++) {
        QString dayText = ui->tableCalendar->item(currentRow, i)->text();
        if (dayText.compare("-") != 0) {
            if (startDay == -1) {
                startDay = i;
            }
            if (i == 6) {
                endDay = 6;
            }
        }
        if (dayText.compare("-") == 0 && endDay == -1) {
            endDay = i-1;
        }

        QString currentDay;
        if (dayText.compare("-") != 0) {
            currentDay += ui->lineMonth->displayText();
            currentDay += "/";
            currentDay += dayText;
        }
        days << currentDay;

    }

    ui->labelStart->setText(QString::number(startDay));
    ui->labelEnd->setText(QString::number(endDay));

    ui->labelSunday->setText(days[0]);
    ui->labelMonday->setText(days[1]);
    ui->labelTuesday->setText(days[2]);
    ui->labelWednesday->setText(days[3]);
    ui->labelThursday->setText(days[4]);
    ui->labelFriday->setText(days[5]);
    ui->labelSaturday->setText(days[6]);

    if (startDay != -1) { //if the current week is an actual week,
        QString * request = new QString("REQUEST_EVENTS ");
        (*request)+=m_p_username; (*request)+=';';
        (*request)+=m_p_password; (*request)+=';';


        QString year = ui->lineYear->displayText();
        QString month = ui->lineMonth->displayText();
        QString day = ui->tableCalendar->item(currentRow, startDay)->text();

        (*request)+=year; (*request)+='-';
        (*request)+=month; (*request)+='-';
        (*request)+=day; (*request)+=';';

        day = ui->tableCalendar->item(currentRow, endDay)->text();

        (*request)+=year; (*request)+='-';
        (*request)+=month; (*request)+='-';
        (*request)+=day;

        ui->labelTest->setText(*request);


        QString * response = setup_connection(request);
        ui->labelTest_2->setText(*response);
    }
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
