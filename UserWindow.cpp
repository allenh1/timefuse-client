
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
    
    connect(m_p_create_button, &QPushButton::released, this, &MainWindow::handleButton);
    connect(m_p_login_button, &QPushButton::released, this, &MainWindow::handleButton);
    connect(m_p_reset_button, &QPushButton::released, this, &MainWindow::handleButton);
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
}
