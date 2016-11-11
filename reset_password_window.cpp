#include "reset_password_window.hpp"
//#include "ui_reset_password_window.hpp"

reset_password_window::reset_password_window(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::reset_password_window)
{
    m_p_ui->setupUi(this);

	m_p_ui->email_input->setPlaceholderText(tr("email@domain.com"));
	m_p_ui->username_input->setPlaceholderText(tr("Enter your username"));
	m_p_ui->new_password_input->setPlaceholderText(tr("Enter new password"));

	/* set the password edit to not show text */
	m_p_ui->new_password_input->setEchoMode(QLineEdit::Password);
	m_p_ui->new_password_input->setInputMethodHints(Qt::ImhHiddenText |
										   Qt::ImhNoPredictiveText |
										   Qt::ImhNoAutoUppercase);
    
    /* connect signals */
    connect(m_p_ui->cancel_button, &QPushButton::released,
            this, &reset_password_window::cancel_pressed);
    connect(m_p_ui->reset_button, &QPushButton::released,
            this, &reset_password_window::reset_pressed);

}

reset_password_window::~reset_password_window()
{
    delete m_p_ui;
}

void reset_password_window::reset_pressed()
{
    QString * request = new QString("REQUEST_RESET ");

    (*request)+=m_p_ui->username_input->text(); (*request)+=':';
    (*request)+=m_p_ui->email_input->text(); (*request)+=':';
	(*request)+=m_p_ui->new_password_input->text();
	(*request)+="\r\n\0";

    QString * response = setup_connection(request);

    if(response->contains("ERROR")) {
		QMessageBox::critical(this, tr("Error"), *response);
		delete response; delete request;
		return;
	} delete response; delete request;
	
	m_p_ui->email_input->setText("");
	m_p_ui->username_input->setText("");
	m_p_ui->new_password_input->setText("");
    Q_EMIT(return_to_user_page());
}


void reset_password_window::cancel_pressed()
{
	m_p_ui->email_input->setText("");
	m_p_ui->username_input->setText("");
	m_p_ui->new_password_input->setText("");
    Q_EMIT(return_to_user_page());
}
