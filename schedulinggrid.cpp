#include "schedulinggrid.hpp"
#include <time.h>

QFont eventFont("Segoe UI", 7);

schedulingGrid::schedulingGrid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::schedulingGrid)
{
	QPalette qpalette(QColor(102, 219, 255, 255), QColor(204, 243, 255, 255));
    this->setPalette(qpalette);
    QFont font(QString("Courier"), 10.5, QFont::Thin, false);
    this->setFont(font);

    ui->setupUi(this);
    ui->tableCalendar->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_p_username = new QString("");
    m_p_password = new QString("");
    connect(ui->back_button, &QPushButton::released,
            this, &schedulingGrid::on_back_button);

	m_p_user_occupied_days = new QMutex();
    m_p_createevent = new createevent();
    connect(ui->pushCreateEvent, &QPushButton::released,
            this, &schedulingGrid::to_create_event);
    connect(m_p_createevent, &createevent::return_to_schedule,
            this, &schedulingGrid::from_create_event);

    QDate today = QDate::currentDate();
    ui->lineMonth->setText(QString::number(today.month()));
    ui->lineYear->setText(QString::number(today.year()));
    schedulingGrid::generateCalendar();

    ui->lineMonth->hide();
    ui->lineYear->hide();
    ui->labelTest->hide();
    ui->labelTest_2->hide();
    ui->frameWeek->hide();

    QModelIndex newIndex = ui->tableCalendar->model()->index(0,0);
    ui->tableCalendar->setCurrentIndex(newIndex);

	for (int x = 1; x <= 12; ++x) user_occupied_days[x] = new QString("0\n");
    //I call colorCalendar in home_screen.cpp. doing it here doesn't work.
    //I don't know why but OK!!!
	//----- it doesn't work bc the user hasn't logged in yet when this is called
}

schedulingGrid::~schedulingGrid()
{
    delete ui;
    delete m_p_username;
    delete m_p_password;
	delete m_p_user_occupied_days;
}

void schedulingGrid::fromHome()
{
    schedulingGrid::colorCalendar();
    ui->frameWeek->hide();
    ui->frameMonth->show();
}

void schedulingGrid::set_user_occupied_days(QString text, int month)
{
	m_p_user_occupied_days->lock();
	delete user_occupied_days[month];
	user_occupied_days[month] = new QString(text);
	m_p_user_occupied_days->unlock();

	if (month == ui->lineMonth->displayText().toInt()) Q_EMIT(recolor_month());
}

uint schedulingGrid::get_year()
{
	return ui->lineYear->displayText().toInt();
}

/* This will show how to properly color in the calender */
void schedulingGrid::colorCalendar()
{	
	/**
	 * @todo remove this request!
	 */
	/* select all groups in which a given user is a member */
	// QString * get_groups = new QString("REQUEST_GROUPS ");
	// *get_groups += *m_p_username + ":::" + *m_p_password + "\r\n\0";

	// /* split along the '\n' character */
	// QString * get_group_response = setup_connection(get_groups);
	// QStringList list = get_group_response->split("\n");

	/* ask for (every) group in the selected month */
	// for (size_t x = 0; x < list.size(); ++x) {
	// 	/* send the current group's select query */
	// 	QString * group_request = new QString("REQUEST_GROUP_MONTH_EVENTS ");
	// 	(*group_request)+=m_p_username;	(*group_request)+=":::";
	// 	(*group_request)+=m_p_password;	(*group_request)+=":::";
	// 	(*group_request)+=ui->lineMonth->displayText();	(*group_request)+=":::";
	// 	(*group_request)+=ui->lineYear->displayText() + ":::" + list[x] + "\r\n\0";
	// 	QString * group_response = setup_connection(group_request);
	// 	group_occupied_days = group_occupied_days | ((uint) group_response->split("\n")[0].toInt());
	// 	delete group_request, delete group_response;
	// }

			
	/**
	 * @todo change this to be a set color for each group
	 */	
	bool ok;
    ushort month = (ui->lineMonth->displayText()).toInt(&ok, 10);
    uint year = (ui->lineYear->displayText()).toInt(&ok,10);
	Q_EMIT (send_year(QString(ui->lineYear->displayText())));
	/* prepare these values to be colored */
	m_p_user_occupied_days->lock();
	uint user_occupied = (uint) user_occupied_days[month]->split("\n")[0].toInt();
	m_p_user_occupied_days->unlock();
	uint group_occupied = 0;

    /* do math */
    ushort C = std::floor(year / 100); ushort m = month - 2;
    if (month == 1) m = 11; else if (month == 2) m = 12;
    ushort Y = ((month == 1 || month == 2) ? year - 1 : year) - C * 100;
    /* this number is hawt yall */
    int dc = (int) (1 + std::floor(2.6 * m - 0.2) - 2 * C
                    + Y + std::floor(Y / 4.0) + std::floor(C / 4.0)) % 7;
    register uint daycode = (dc < 0) ? dc + 7 : dc;
    if (daycode == 0) daycode = 7;
    for (int x = -1; user_occupied || group_occupied;
		 user_occupied >>= 1, group_occupied >>= 1, ++x) {
        /* if the bit is set, fill the cooresponding day */
        if (user_occupied & 1) {
            ui->tableCalendar->item((x + daycode) / 7,
                                    ((x + daycode) % 7))->setBackgroundColor(Qt::blue);
            std::cerr<<"blue"<<std::endl;
        } if (group_occupied & 1) {
            ui->tableCalendar->item((x + daycode) / 7,
                                    ((x + daycode) % 7))->setBackgroundColor(Qt::yellow);
        }
    }
}


void schedulingGrid::generateCalendar()
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
    int dc = (int) (1 + std::floor(2.6 * m - 0.2) - 2 * C
                    + Y + std::floor(Y / 4.0) + std::floor(C / 4.0)) % 7;
    register uint daycode = (dc < 0) ? dc + 7 : dc;
    //if the year is a leap year, account for that
    if((!(year % 4) && (year%100)) || !(year % 400)) days_in_month[2] = 29;
    //qCalendarWidget will skip a row if the month starts on a Monday, so I copy that behavior
    if (daycode == 0) daycode = 7;
    //set the calendar's title
    ui->label->setText(months[month] + ", " + QString::number(year));
    int currentDate = 1;
    /**
     * the only way I could figure out how to set text for a spot
     * in a table is to use a QTableWidgetItem object.
     * I don't know how QT handles these in memory, if I should
     * be clearing these before changing the view.
     * because 42 objects seems like a lot?
     */
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
    } if (calls && ui->frameMonth->isVisible()) colorCalendar();
    if (!calls) calls = 1; /* needed to avoid a crash */
    initial = 1;
}

void schedulingGrid::on_pushLeft_clicked()
{
    /* for now these two buttons hijack the text fields. */
    bool ok;
    int year = (ui->lineYear->displayText()).toInt(&ok,10);
    int month = (ui->lineMonth->displayText()).toInt(&ok,10);
    if (month != 1) {
        ui->lineMonth->setText(QString::number(month - 1));
    } else {
        ui->lineYear->setText(QString::number(year - 1));
        ui->lineMonth->setText(QString::number(12));
    }
    //colorCalendar();
    schedulingGrid::generateCalendar();
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
    //colorCalendar();
    schedulingGrid::generateCalendar();
}


void schedulingGrid::generateWeek()
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

    // QStringList days;
    int startDay = -1;
    int endDay = -1;
    int startDate = -1;
    int endDate = -1;
    QString currentDay;
    // int currentRow = ui->tableCalendar->currentRow();

    bool ok;

    for(int i = 0; i < 7; i++) {
        QString dayText = ui->tableCalendar->item(currentRow, i)->text();
        if (dayText.compare("-") != 0) {
            if (startDay == -1) {
                startDate = dayText.toInt(&ok,10);
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
    endDate = startDate + (endDay-startDay);


    ui->labelSunday->setText(days[0]);
    ui->labelMonday->setText(days[1]);
    ui->labelTuesday->setText(days[2]);
    ui->labelWednesday->setText(days[3]);
    ui->labelThursday->setText(days[4]);
    ui->labelFriday->setText(days[5]);
    ui->labelSaturday->setText(days[6]);

    if (startDay != -1) { //if the current week is an actual week,
        QString * request = new QString("REQUEST_EVENTS ");
        (*request)+=m_p_username; (*request)+=":::";
        (*request)+=m_p_password; (*request)+=":::";


        ui->listSun->clear();
        ui->listMon->clear();
        ui->listTues->clear();
        ui->listWed->clear();
        ui->listThurs->clear();
        ui->listFri->clear();
        ui->listSat->clear();

        QString year = ui->lineYear->displayText();
        QString month = ui->lineMonth->displayText();
        QString day = ui->tableCalendar->item(currentRow, startDay)->text();

        (*request)+=year + "-" + month + "-" + day + ":::";

        day = ui->tableCalendar->item(currentRow, endDay)->text();

        (*request)+=year + "-" + month + "-" + day;
        ui->labelTest->setText(*request);

        QString * response = setup_connection(request);
        ui->labelTest_2->setText(*response);

        QString currentGroup = "";

        //////////////

        /* select all groups in which a given user is a member */
        QString * get_groups = new QString("REQUEST_GROUPS ");
        *get_groups += *m_p_username + ":::" + *m_p_password + "\r\n\0";

        /* split along the '\n' character */
        QString * get_group_response = setup_connection(get_groups);
        QStringList list = get_group_response->split("\n");

        /* ask for (every) group in the selected month */
        for (size_t x = 0; x < list.size() - 1; ++x) {
            /* send the current group's select query */
            QString * group_request = new QString("REQUEST_GROUP_EVENTS ");
            (*group_request)+=m_p_username;	(*group_request)+=":::";
            (*group_request)+=m_p_password;	(*group_request)+=":::";

            QString year = ui->lineYear->displayText();
            QString month = ui->lineMonth->displayText();
            QString day = ui->tableCalendar->item(currentRow, startDay)->text();

            (*group_request)+=year + "-" + month + "-" + day + ":::";

            day = ui->tableCalendar->item(currentRow, endDay)->text();

            (*group_request)+=year + "-" + month + "-" + day + ":::" + list[x] + "\r\n\0";
            std::cerr<<group_request->toStdString()<<std::endl;
            QString * group_response = setup_connection(group_request);
            if(group_response->contains("ERROR")) {
                QMessageBox::critical(this, tr("Error"), *group_response);
            } else {
                *response += list[x] + "\n";
                *response += *group_response;
            }
        }

        //////////////


        QStringList weekEvents = response->split("\n",QString::SkipEmptyParts);

        for (int i = 0; i<weekEvents.size(); ++i) {

            if (weekEvents.at(i).contains(":::") == false) {
                currentGroup = weekEvents.at(i);
            } else {

                QStringList event = (weekEvents.at(i)).split(":::");
                QStringList date = event.at(0).split("-");
                int day = date.at(2).toInt(&ok,10);
                QString eventInfo;
                //eventInfo += "d";
                QString time = event.at(1);
                QString name = event.at(4);
                QString loc = event.at(3);
                eventInfo += time += "\n";
                eventInfo += name += "\n";
                eventInfo += "@ ";
                eventInfo += loc += "\n";
                eventInfo += currentGroup;

                int location = day - startDate + startDay;
                //ui->labelTest->setText(QString::number(location));

                QListWidgetItem * newEvent = new QListWidgetItem;
                newEvent->setText(eventInfo);
                newEvent->setFont(eventFont);


                switch(location) {
                case 0: ui->listSun->addItem(newEvent);
                    break;
                case 1: ui->listMon->addItem(newEvent);
                    break;
                case 2: ui->listTues->addItem(newEvent);
                    break;
                case 3: ui->listWed->addItem(newEvent);
                    break;
                case 4: ui->listThurs->addItem(newEvent);
                    break;
                case 5: ui->listFri->addItem(newEvent);
                    break;
                case 6: ui->listSat->addItem(newEvent);
                    break;
                }
            }

        }

    }

}

void schedulingGrid::on_pushCreateEvent_clicked()
{
    /*
    createevent ce;
    ce.m_p_username = m_p_username;
    ce.m_p_password = m_p_password;
    ce.setModal(true);
    ce.exec();
    */
    //m_p_createevent->
}

void schedulingGrid::to_create_event()
{
    m_p_createevent->m_p_username = m_p_username;
    m_p_createevent->m_p_password = m_p_password;

    bool ok;
    int year = (ui->lineYear->displayText()).toInt(&ok,10);
    int month = (ui->lineMonth->displayText()).toInt(&ok,10);
    int day = (ui->tableCalendar->item(ui->tableCalendar->currentRow(),ui->tableCalendar->currentColumn())->text()).toInt(&ok,10);

    QDate * selected = new QDate(year,month,day);
    m_p_createevent->selected = *selected;
    m_p_createevent->changeDate();

    m_p_createevent->show();
    this->hide();
}

void schedulingGrid::from_create_event()
{
    schedulingGrid::colorCalendar();
    m_p_createevent->hide();
    this->show();
}

void schedulingGrid::on_back_button()
{
    Q_EMIT(return_to_home_screen());
}


void schedulingGrid::on_tableCalendar_currentCellChanged(int, int, int, int)
{
    //schedulingGrid::generateWeek();
}

void schedulingGrid::on_PushSwitchViews_clicked()
{
    if (ui->frameMonth->isHidden()) {
        schedulingGrid::colorCalendar();
        ui->frameMonth->show();
        ui->frameWeek->hide();
    } else {
        ui->frameMonth->hide();
        schedulingGrid::generateWeek();
        ui->frameWeek->show();

    }
}

void schedulingGrid::on_pushRightW_clicked()
{

    if (ui->tableCalendar->currentRow() != 5) {
        QModelIndex newIndex = ui->tableCalendar->model()->index(ui->tableCalendar->currentRow() + 1, ui->tableCalendar->currentColumn());
        ui->tableCalendar->setCurrentIndex(newIndex);
    } else {
        schedulingGrid::on_pushRight_clicked();
        QModelIndex newIndex = ui->tableCalendar->model()->index(0, ui->tableCalendar->currentColumn());
        ui->tableCalendar->setCurrentIndex(newIndex);
    }
    if ((ui->tableCalendar->item(ui->tableCalendar->currentRow(), 0))->text() == (ui->tableCalendar->item(ui->tableCalendar->currentRow(), 6))->text()) {
        schedulingGrid::on_pushRightW_clicked();
    }
    schedulingGrid::generateWeek();
}

void schedulingGrid::on_pushLeftW_clicked()
{
    if (ui->tableCalendar->currentRow() != 0) {
        QModelIndex newIndex = ui->tableCalendar->model()->index(ui->tableCalendar->currentRow() - 1, ui->tableCalendar->currentColumn());
        ui->tableCalendar->setCurrentIndex(newIndex);
    } else {
        schedulingGrid::on_pushLeft_clicked();
        QModelIndex newIndex = ui->tableCalendar->model()->index(5, ui->tableCalendar->currentColumn());
        ui->tableCalendar->setCurrentIndex(newIndex);
    }

    if ((ui->tableCalendar->item(ui->tableCalendar->currentRow(), 0))->text() == (ui->tableCalendar->item(ui->tableCalendar->currentRow(), 6))->text()) {
        schedulingGrid::on_pushLeftW_clicked();
    }
    schedulingGrid::generateWeek();
}
