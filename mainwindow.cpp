#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    m_p_login_button = new QPushButton(tr("Sign In"), this);
    m_p_create_button = new QPushButton(tr("Create Account"), this);
    m_p_reset_button = new QPushButton("Reset Password", this);

    name = new QLabel(this);
    password = new QLabel(this);

    m_p_main_layout = new QVBoxLayout();
    m_p_name_layout = new QHBoxLayout();
    m_p_password_layout = new QHBoxLayout();


    m_p_name_layout->addWidget(name);
    m_p_name_layout->addWidget(text_name);

    m_p_password_layout->addWidget(password);
    m_p_password_layout->addWidget(text_pswd);

    m_p_main_layout->addLayout(layout);
    m_p_main_layout->addLayout(layout2);
    m_p_main_layout->addWidget(m_p_create_button);

    setLayout(m_p_main_layout);

    //creating buttons(create, login, reset)
    m_p_create_button = new QPushButton(tr("Create Account"), this);
    m_p_login_button = new QPushButton(tr("Login"), this);
    m_p_reset_button = new QPushButton(tr("Reset Password"), this);

    connect(m_p_create_button, SIGNAL(clicked()), this, SLOT(show()));

    //text boxes for name and password on login screen
    // text_name = new QLineEdit(this);
    // text_pswd = new QLineEdit(this);
    // text_email = new QLineEdit(this);

    // m_p_user_edit->setGeometry(QRect(QPoint(500, 315), QSize(200, 25)));
    // m_p_password_edit->setGeometry(QRect(QPoint(500, 390), QSize(200, 25)));

    m_p_user_label->setText(tr("Username:"));
    m_p_user_label->setGeometry(QRect(QPoint(400,275), QSize(200, 100)));

    // m_p_password_label->setText(tr("Password:"));
    // m_p_password_label->setGeometry(QRect(QPoint(400, 375), QSize(400, 50)));

    //QTextEdit *txt = new QTextEdit();

    // m_p_create_button->setGeometry(QRect(QPoint(650, 500), QSize(200, 50)));
    // m_p_login_button->setGeometry(QRect(QPoint(650, 550), QSize(200, 50)));
    // m_p_reset_button->setGeometry(QRect(QPoint(1000, 700), QSize(200, 50)));

    connect(m_p_create_button, &QPushButton::released, this, &MainWindow::handleButton);
    connect(m_p_login_button, &QPushButton::released, this, &MainWindow::handleButton);
    connect(m_p_reset_button, &QPushButton::released, this, &MainWindow::handleButton);
}

MainWindow::~MainWindow()
{
    delete m_p_create_button;
    delete m_p_login_button;
    delete m_p_reset_button;
    delete m_p_user_label;
    delete m_p_password_label;
    delete m_p_user_edit;
    delete m_p_password_edit;
};

void MainWindow::handleButton()
{
    // to change the text of the buttons
    m_p_create_button->setText("Create Account");
    m_p_login_button->setText("Login");
    m_p_reset_button->setText("Reset Password");
    // to resize buttons on clicking
    m_p_create_button->resize(200,50);
    m_p_login_button->resize(200,50);
    m_p_reset_button->resize(200,50);
}
