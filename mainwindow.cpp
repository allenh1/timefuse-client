#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
	m_p_login_button = new QPushButton(tr("Sign In"), this);
	m_p_create_button = new QPushButton(tr("Create Account"), this);

    // Create the button, make "this" the parent
    m_p_login_button = new QPushButton("Log In", this);
    m_p_create_button = new QPushButton("Create Account", this);
    m_p_reset_button = new QPushButton("Reset Password", this);

    name = new QLabel(this);
    password = new QLabel(this);

    text_name = new QLineEdit(this);
    text_pswd = new QLineEdit(this);


    text_name->setGeometry(QRect(QPoint(500, 315), QSize(200, 25)));
    text_pswd->setGeometry(QRect(QPoint(500, 390), QSize(200, 25)));




    name->setText("Username:");
    name->setGeometry(QRect(QPoint(400,275), QSize(200, 100)));
    password->setText("Password:");
    password->setGeometry(QRect(QPoint(400, 375), QSize(400, 50)));



    //QTextEdit *txt = new QTextEdit();

    m_p_create_button->setGeometry(QRect(QPoint(650, 500), QSize(200, 50)));
    m_p_login_button->setGeometry(QRect(QPoint(650, 550), QSize(200, 50)));
    m_p_reset_button->setGeometry(QRect(QPoint(1000, 700), QSize(200, 50)));

    // Connect button signal to appropriate slot
    connect(m_p_create_button, &QPushButton::released, this, &MainWindow::handleButton);
    connect(m_p_login_button, &QPushButton::released, this, &MainWindow::handleButton);
    connect(m_p_reset_button, &QPushButton::released, this, &MainWindow::handleButton);
}

MainWindow::~MainWindow()
{
    delete m_p_create_button;
    delete m_p_login_button;
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







