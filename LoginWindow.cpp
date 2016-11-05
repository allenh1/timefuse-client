#include "LoginWindow.hpp"

LoginWindow::LoginWindow(QWidget *parent)
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
			this, &LoginWindow::open_create_window);
	connect(m_p_create_account_window,
			&create_account_window::return_to_user_page,
			this, &LoginWindow::hide_create);	
	
    // connect(m_p_create_button, &QPushButton::released, this, &MainWindow::handleButton);
    // connect(m_p_login_button, &QPushButton::released, this, &MainWindow::handleButton);
    // connect(m_p_reset_button, &QPushButton::released, this, &MainWindow::handleButton);
}

LoginWindow::~LoginWindow()
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

void LoginWindow::handleButton()
{
    /**
     * @todo create an instance
     * of a create an account
     * button and hide this view.
     */
    m_name = m_p_user_edit->text();
    m_password = m_p_password_edit->text();
    
    Q_EMIT login(m_name,m_password);
    
    m_p_user_edit->setText("");
    m_p_password_edit->setText("");
    this->hide();
}

void LoginWindow::open_create_window()
{
   this->hide();
   m_p_create_account_window->show();
}

void LoginWindow::hide_create()
{
   m_p_create_account_window->hide();
   this->show();
}


void login(QString username, QString password) {
  QString * request = new QString("REQUEST_LOGIN");
/*
  // create qt hashing object
  QCrytographicHash * qhash = new QCrytographicHash(QCrytographicHash::Sha512);

  // create qt byte array object to hash username
  QByteArray qarray; qarray+=username;
  qhash->addData(qarray);

  // hash username and add to request
  QByteArray res = qhash->result();
  (*request)+= " " + res.toStdString() + ":";

  // reset hashing object
  qhash->reset();

  // clear qbytearray and add password
  qarray.clear(); qarray+=password;
  qhash->addData(qarray);

  // hash password and add to request
  QByteArray res = qhash->result();
  (*request)+= res.toStdString() + "\r\n";
*/
  QString * response = setup_connection(request);

  if(response->size() != 0) {
    std::cerr<<response->toStdString()<<std::endl;
  }

  delete request;
  //delete qhash;
  delete response;
}
