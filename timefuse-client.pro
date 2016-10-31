QT = core gui widgets network
CONFIG += c++11

TARGET = timefuse-client
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           user.cpp \
	   create_account_window.cpp \
        reset_password_window.cpp \
	   UserWindow.cpp

HEADERS += mainwindow.hpp \
           user.hpp \
	    create_account_window.hpp \
        reset_password_window.hpp \
           UserWindow.hpp

FORMS += create_account_window.ui \
        reset_password_window.ui
