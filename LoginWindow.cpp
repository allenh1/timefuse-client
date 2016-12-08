#include "LoginWindow.hpp"

LoginWindow::LoginWindow(QWidget *parent)
	: QWidget(parent)
{
    this->setPalette(QPalette(QColor(255, 255, 255, 255), QColor(76, 76, 76, 255)));
    this->setFont(QFont(QString("Courier"), 13, QFont::Thin, false));

	m_p_login_button = new QPushButton(tr("Sign In"));
	m_p_login_button->setPalette(QPalette(QColor(86, 231, 115, 255),
										  QColor(86, 231, 115, 255)));
	
	m_p_create_button = new QPushButton(tr("Create Account"));
	m_p_create_button->setPalette(QPalette(QColor(227, 201, 69, 255),
										  QColor(227, 201, 69, 255)));
	
	m_p_reset_button = new QPushButton(tr("Reset Password"));
	m_p_reset_button->setPalette(QPalette(QColor(255, 0, 128, 255),
										  QColor(255, 0, 128, 255)));
	
	m_p_user_label = new QLabel(tr("Username:"));
    m_p_password_label = new QLabel(tr("Password:"));
    
	m_p_user_edit = new QLineEdit();
	m_p_user_edit->setPalette(QPalette(QColor(255, 255, 255, 255),
									   QColor(255, 255, 255, 255)));
	
	m_p_password_edit = new QLineEdit();
	m_p_password_edit->setPalette(QPalette(QColor(255, 255, 255, 255),
									   QColor(255, 255, 255, 255)));
    
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
	m_p_reset_password_window = new reset_password_window();
	m_p_home_screen = new home_screen();
    
	connect(m_p_reset_button, &QPushButton::released,
			this, &LoginWindow::open_reset_password_window);	
	connect(m_p_create_button, &QPushButton::released,
			this, &LoginWindow::open_create_window);
	connect(m_p_create_account_window,
			&create_account_window::return_to_user_page,
			this, &LoginWindow::hide_create);
	connect(m_p_login_button, &QPushButton::released,
			this, &LoginWindow::handleButton);
	connect(this, &LoginWindow::do_login,
			this, &LoginWindow::login);
	connect(m_p_reset_password_window,
			&reset_password_window::return_to_user_page,
			this, &LoginWindow::hide_reset);

	connect(m_p_home_screen, &home_screen::return_to_login,
            this, &LoginWindow::hide_home_screen);
}

LoginWindow::~LoginWindow() { }

void LoginWindow::handleButton()
{
	/**
	 * @todo create an instance
	 * of a create an account
	 * button and hide this view.
	 */
	m_name = m_p_user_edit->text();
	m_password = m_p_password_edit->text();

	Q_EMIT do_login(m_name,m_password);
	
	m_p_user_edit->setText("");
	m_p_password_edit->setText("");
}

void LoginWindow::open_create_window()
{
	m_p_user_edit->setText("");
	m_p_password_edit->setText("");
	this->hide();
	m_p_create_account_window->show();
}

void LoginWindow::hide_create()
{
	m_p_create_account_window->hide();
	this->show();
}

void LoginWindow::hide_reset()
{
	m_p_reset_password_window->hide();
	this->show();
}

void LoginWindow::open_reset_password_window()
{
	m_p_user_edit->setText("");
	m_p_password_edit->setText("");
	this->hide();
	m_p_reset_password_window->show();
}

void LoginWindow::login(QString username, QString password) {
	QString * request = new QString("REQUEST_LOGIN");

	// hash username and add to request
	QString res = username;
	(*request)+= " "; (*request)+=res + ":::";

	// hash password and add to request
	res.clear(); res = encrypt_string(password);
	(*request)+=res + "\r\n" + '\0';

	QString * response = setup_connection(request);
	
	if(response->size() != 0) {
		std::cerr<<response->toStdString()<<std::endl;
		if(response->contains(tr("OK"))) {
			(*(m_p_home_screen->m_p_username))=username; 
		    (*(m_p_home_screen->m_p_password))=encrypt_string(password);
			
			this->hide();
			m_p_home_screen->show();

			m_p_home_screen->kick_off_threads();
		} else {
			QMessageBox::critical(this, tr("Error"), *response);
		}
	} 

	delete request;
	delete response;
}

void LoginWindow::hide_home_screen()
{
    m_p_home_screen->hide();
	this->show();
}
