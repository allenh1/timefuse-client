
#include "UserWindow.hpp"


UserWindow::UserWindow(QWidget *parent)
: QWidget(parent)
{
    m_p_login_button = new QPushButton(tr("Sign In"));
    m_p_create_button = new QPushButton(tr("Create Account"));
    m_p_reset_button = new QPushButton(tr("Reset Password"));
    
    m_p_user_label = new QLabel(tr("Username:"));
    m_p_password_label = new QLabel(tr("Password:"));
    
    m_p_user_edit = new QLineEdit();
    m_p_password_edit = new QLineEdit();
    
    /* set the password edit to not show text */
    m_p_password_edit->setEchoMode(QLineEdit::Password);
    m_p_password_edit->setInputMethodHints(Qt::ImhHiddenText |
                                           Qt::ImhNoPredictiveText |
                                           Qt::ImhNoAutoUppercase);
    
    m_p_main_layout = new QVBoxLayout();
    m_p_name_layout = new QHBoxLayout();
    m_p_password_layout = new QHBoxLayout();
    m_p_button_layout = new QHBoxLayout();
    
    m_p_name_layout->addWidget(m_p_user_label);
    m_p_name_layout->addWidget(m_p_user_edit);
    
    m_p_password_layout->addWidget(m_p_password_label);
    m_p_password_layout->addWidget(m_p_password_edit);    
    m_p_button_layout->addWidget(m_p_create_button);
    m_p_button_layout->addWidget(m_p_reset_button);
    m_p_button_layout->addWidget(m_p_login_button);
    
    m_p_main_layout->addLayout(m_p_name_layout);
    m_p_main_layout->addLayout(m_p_password_layout);
    m_p_main_layout->addLayout(m_p_button_layout);
    
    setLayout(m_p_main_layout);
    show();

	m_p_create_account_window = new create_account_window();
	
	connect(m_p_create_button, &QPushButton::released,
			this, &UserWindow::open_create_window);
	connect(m_p_create_account_window,
			&create_account_window::return_to_user_page,
			this, &UserWindow::hide_create);	
	
    // connect(m_p_create_button, &QPushButton::released, this, &MainWindow::handleButton);
    // connect(m_p_login_button, &QPushButton::released, this, &MainWindow::handleButton);
    // connect(m_p_reset_button, &QPushButton::released, this, &MainWindow::handleButton);
}

UserWindow::~UserWindow()
{
    delete m_p_create_button;
    delete m_p_login_button;
    delete m_p_reset_button;
    delete m_p_user_label;
    delete m_p_password_label;
    delete m_p_user_edit;
    delete m_p_password_edit;
    delete m_p_main_layout;
    delete m_p_button_layout;
    delete m_p_name_layout;
    delete m_p_password_layout;
};

void UserWindow::handleButton()
{
    /**
     * @todo create an instance
     * of a create an account
     * button and hide this view.
     */
    m_name = m_p_user_edit->text();
    m_password = m_p_password_edit->text();
    
    Q_EMIT logIn(m_name,m_password);
    
    m_p_user_edit->setText("");
    m_p_password_edit->setText("");
    this->hide();
}

void UserWindow::open_create_window()
{
   this->hide();
   m_p_create_account_window->show();
}

void UserWindow::hide_create()
{
   m_p_create_account_window->hide();
   this->show();
}

/** 
 * Connects client to master, then to worker provided by master.
 * Sends the information provided in content param to worker, and 
 * returns the workers response.  
 *
 * If the thread never starts within the method, it returns "Thread
 * did not start."
 *
 * @param QString content
 * @return QString
 */
QString* UserWindow::setup_connection(QString * content) {
  QTcpSocket * pSocket = NULL;
  QString* read, tcp_server, port_string;

  bool contin = true;
  
  for(;contin;) {
    if (pSocket != NULL) delete pSocket;
    pSocket = new QTcpSocket();

    QString host = "localhost";

/* connect to master */
    pSocket->connectToHost(host, (quint16)3224, QIODevice::ReadWrite);
    pSocket->waitForConnected(500);

    // if socket did not connect start over
    if(pSocket->state() == QAbstractSocket::UnconnectedState) {
      pSocket->abort();
      delete pSocket;
      pSocket = NULL;
      continue;
    }

    // write to master to request a worker
    pSocket->write("REQUEST_WORKER\r\n");

    // not sure if i need to do this part...
    tcp_server+= "localhost" + ':';
    port_string.setNum(3224);
    tcp_server+=port_string + "\r\n" + '\0';
    
    pSocket->write(tcp_server.toStdString().c_str());

    // for for the stuff to be written
    pSocket->waitForBytesWritten(-1);

/* wait for master to connect client to worker */
    pSocket->waitForReadyRead();

    // read from master to get worker
    for(;pSocket->canReadLine(); (*read)+= pSocket->readLine());

    // if nothing read, then start over
    if(read->size() == 0) continue;

    // get host and port
    read->replace("\r\n","");
    QStringList l = read->split(':');

/* connect to worker */
    pSocket->connectToHost(l.at(0), (quint16)l.at(1).toInt(), QIODevice::ReadWrite);
    pSocket->waitForConnected(500);
  write_to_worker:
    // if never connects to worker then start over
    if(pSocket->state() == QAbstractSocket::UnconnectedState) {
      pSocket->abort();
      delete pSocket;
      pSocket = NULL;
      read->clear();
      continue;
    }

    // write content to worker
    pSocket->write(content->toStdString().c_str());
    pSocket->waitForBytesWritten(-1);

    pSocket->waitForReadyRead();
    read->clear();
    for(;pSocket->canReadLine(); (*read)+= pSocket->readLine());

    // if nothing read, then start over
    if(read->size() == 0) goto write_to_worker;

    //clean up stuff
    pSocket->abort();
    delete pSocket;
    pSocket = NULL;
    contin = false;
  }

  return read;
}
