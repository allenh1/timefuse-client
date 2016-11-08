#include "manage_groups.hpp"


manage_groups::manage_groups(QWidget *parent) :
    QWidget(parent),
    m_p_ui(new Ui::manage_groups)
{
    m_p_ui->setupUi(this);

	m_p_username = new QString("");
	m_p_password = new QString("");

	connect(m_p_ui->back_button, &QPushButton::released,
			this, &manage_groups::on_back_button);
}

manage_groups::~manage_groups()
{
    delete m_p_ui;
}

void manage_groups::on_back_button()
{
	Q_EMIT(return_to_home_screen());
}
