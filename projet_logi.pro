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
    usercontroller.cpp \
    stylemanager.cpp

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
    usercontroller.h \
    stylemanager.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

RESOURCES += \
    resources/resources.qrc \
    styles.qrc \

# Enable high DPI scaling
CONFIG += highdpi

# Enable debug information
CONFIG(debug, debug|release) {
    DEFINES += DEBUG
}

# Release configuration
CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
}

DISTFILES += \
    README_ENHANCED_UI.md \
    icons/app_icon.png \
    icons/logo.png \
    projet_logi.pro.user
