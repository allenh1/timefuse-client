#ifndef __ACCOUNT_SETTINGS_HPP__
#define __ACCOUNT_SETTINGS_HPP__

#include <QMessageBox>
#include <QStringList>
#include <QtWidgets>
#include <QString>
#include <QtGui>

#include "ui_account_settings.h"
#include "tcp_connection.hpp"
#include "encrypt_string.hpp"

namespace Ui {
    class account_settings;
}

class account_settings : public QWidget
{
	Q_OBJECT
public:
	explicit account_settings (QWidget * _p_parent = NULL);
	virtual ~account_settings();

	QString * m_p_secret;
	QString * m_p_username;
	QString * m_p_password;
	
	Q_SLOT void save_changes_pressed();
	Q_SLOT void cancel_pressed();

	Q_SIGNAL void return_to_home_screen();

	void fill_fields();

private:
    Ui::account_settings * m_p_ui;
};

#endif
