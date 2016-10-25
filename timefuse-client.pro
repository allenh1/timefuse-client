QT = core gui widgets network
CONFIG += c++11

TARGET = timefuse-client
TEMPLATE = app

SOURCES += main.cpp \
           mainwindow.cpp \
           user.cpp \
	   create_account_window.cpp \
	   UserWindow.cpp

HEADERS += mainwindow.hpp \
           user.hpp \
	   create_account_window.hpp \
           UserWindow.hpp
