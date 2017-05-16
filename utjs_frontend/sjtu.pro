#-------------------------------------------------
#
# Project created by QtCreator 2017-05-06T19:04:49
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sjtu
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    communication.cpp \
    addtrain.cpp \
    buyticket.cpp \
    buytickets_f.cpp \
    buytickets_t.cpp \
    changetrain.cpp \
    deletetrain.cpp \
    login.cpp \
    login_f.cpp \
    login_t.cpp \
    menu_admin.cpp \
    menu_user.cpp \
    modifypswd.cpp \
    modifysell.cpp \
    modifytrain.cpp \
    mytickets.cpp \
    refund_f.cpp \
    refund_t.cpp \
    register.cpp \
    register_f.cpp \
    saletickets.cpp \
    ticketslist.cpp \
    user_info.cpp \
    viewuser.cpp \


HEADERS  += mainwindow.h \
    addtrain.h \
    buyticket.h \
    buytickets_f.h \
    buytickets_t.h \
    changetrain.h \
    deletetrain.h \
    login.h \
    login_f.h \
    login_t.h \
    menu_admin.h \
    menu_user.h \
    modifypswd.h \
    modifysell.h \
    modifytrain.h \
    mytickets.h \
    refund_f.h \
    refund_t.h \
    register.h \
    register_f.h \
    saletickets.h \
    ticketslist.h \
    user_info.h \
    viewuser.h \
    functions.h \
    communication.h \
    utjs_classes.hpp \
    exceptions.hpp \
    map.hpp \
    set.hpp \
    utility.hpp \
    utjs_stl.hpp \
    vector.hpp \
    basic_binary_class.hpp

FORMS    += mainwindow.ui \
    addtrain.ui \
    buyticket.ui \
    buytickets_f.ui \
    buytickets_t.ui \
    changetrain.ui \
    deletetrain.ui \
    login.ui \
    login_f.ui \
    login_t.ui \
    menu_admin.ui \
    menu_user.ui \
    modifypswd.ui \
    modifysell.ui \
    modifytrain.ui \
    mytickets.ui \
    refund_f.ui \
    refund_t.ui \
    register.ui \
    register_f.ui \
    saletickets.ui \
    ticketslist.ui \
    user_info.ui \
    viewuser.ui

RESOURCES += \
    pics.qrc

RC_FILE = app.rc

DISTFILES += \
    app.ico \
    app.rc \
    black.qss
