QT += core gui widgets sql printsupport
CONFIG += c++17
TEMPLATE = app
TARGET = projet_logi

SOURCES += \
    main.cpp \
    db.cpp \
    client.cpp \
    order.cpp \
    clientdao.cpp \
    orderdao.cpp \
    mainwindow.cpp

HEADERS += \
    db.h \
    client.h \
    order.h \
    clientdao.h \
    orderdao.h \
    mainwindow.h

FORMS += \
    mainwindow.ui
