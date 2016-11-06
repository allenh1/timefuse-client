QT = core gui widgets network
CONFIG += c++11 debug

TARGET = timefuse-client
TEMPLATE = app

SOURCES += main.cpp \
           user.cpp \
           create_account_window.cpp \
           reset_password_window.cpp \
           LoginWindow.cpp \
           tcp_connection.cpp 

HEADERS += user.hpp \
           create_account_window.hpp \
           reset_password_window.hpp \
           LoginWindow.hpp \
           tcp_connection.hpp 

FORMS += create_account_window.ui \
         reset_password_window.ui
