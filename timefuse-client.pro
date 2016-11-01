QT = core gui widgets network
CONFIG += c++11

TARGET = timefuse-client
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           user.cpp \
	   create_account_window.cpp \
           UserWindow.cpp \
           tcp_connection.cpp

HEADERS += mainwindow.hpp \
           user.hpp \
	   create_account_window.hpp \
           UserWindow.hpp \
           tcp_connection.hpp

FORMS += create_account_window.ui
