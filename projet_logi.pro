QT += core gui widgets sql printsupport charts

CONFIG += c++17

TEMPLATE = app
TARGET = projet_logi

SOURCES += \
    logindialog.cpp \
    main.cpp \
    db.cpp \
    client.cpp \
    order.cpp \
    clientdao.cpp \
    orderdao.cpp \
    mainwindow.cpp \
    clientcontroller.cpp \
    ordercontroller.cpp \
    usercontroller.cpp

HEADERS += \
    db.h \
    client.h \
    logindialog.h \
    order.h \
    clientdao.h \
    orderdao.h \
    mainwindow.h \
    clientcontroller.h \
    ordercontroller.h \
    usercontroller.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

RESOURCES += \
    resources/resources.qrc
