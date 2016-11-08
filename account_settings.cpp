#include "account_settings.hpp"

account_settings::account_settings(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::account_settings)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");
	

    /* set the password edit to not show text */
    m_p_ui->old_password_input->setEchoMode(QLineEdit::Password);
    m_p_ui->old_password_input->setInputMethodHints(Qt::ImhHiddenText |
													Qt::ImhNoPredictiveText |
													Qt::ImhNoAutoUppercase);
    m_p_ui->new_password_input->setEchoMode(QLineEdit::Password);
    m_p_ui->new_password_input->setInputMethodHints(Qt::ImhHiddenText |
													Qt::ImhNoPredictiveText |
													Qt::ImhNoAutoUppercase);


    /* connect signals */
    connect(m_p_ui->cancel_button, &QPushButton::released,
            this, &account_settings::cancel_pressed);
    connect(m_p_ui->save_changes, &QPushButton::released,
            this, &account_settings::save_changes_pressed);
}

account_settings::~account_settings()
{
    delete m_p_ui;
}

void account_settings::save_changes_pressed()
{
    QString name = m_p_ui->name_input->text();
	QString username = encrypt_string(m_p_ui->username_input->text());
    QString old_password = encrypt_string(m_p_ui->old_password_input->text());
	QString new_password = encrypt_string(m_p_ui->new_password_input->text());
    QString email = m_p_ui->email_input->text();
    QString phone = m_p_ui->phone_input->text();

    QString * request = new QString("UPDATE_ACCOUNT ");

    (*request)+=username; (*request)+=':'; (*request)+=old_password;
    (*request)+=':'; (*request)+=new_password;
	(*request)+=':'; (*request)+=name;
	(*request)+=':'; (*request)+=email;
	(*request)+=':'; (*request)+=phone; (*request)+="\r\n\0";

    QString * response = setup_connection(request);

    if(response->indexOf(tr("ERROR:")) != -1) {
        QMessageBox::critical(this, tr("Error"), *response);
    }

    delete response;
    delete request;

    m_p_ui->old_password_input->setText("");
	m_p_ui->new_password_input->setText("");
    m_p_ui->phone_input->setText("");
    m_p_ui->name_input->setText("");
    m_p_ui->email_input->setText("");

    Q_EMIT(return_to_home_screen());
}

void account_settings::cancel_pressed()
{
    Q_EMIT(return_to_home_screen());
}
