QT = core gui widgets network
CONFIG += c++11 debug

TARGET = timefuse-client
TEMPLATE = app

SOURCES += main.cpp \
           user.cpp \
           create_account_window.cpp \
           reset_password_window.cpp \
           LoginWindow.cpp \
           tcp_connection.cpp \
           encrypt_string.cpp \
           home_screen.cpp \
           schedulinggrid.cpp \
           add_group.cpp \
           createevent.cpp \
           usercreatedevent.cpp \
           account_settings.cpp \
           manage_groups.cpp \
           create_group_event.cpp \
           edit_group.cpp

HEADERS += user.hpp \
           create_account_window.hpp \
           reset_password_window.hpp \
           LoginWindow.hpp \
           tcp_connection.hpp \
           encrypt_string.hpp \
           home_screen.hpp \
           schedulinggrid.h \
           add_group.h \
           createevent.h \
           usercreatedevent.h \
           account_settings.hpp \
           manage_groups.hpp \
           create_group_event.hpp \
           edit_group.hpp

FORMS += create_account_window.ui \
         reset_password_window.ui \
         home_screen.ui \
         schedulinggrid.ui \
         add_group.ui \
         createevent.ui \
         account_settings.ui \
         manage_groups.ui \
         create_group_event.ui \
         edit_group.ui
