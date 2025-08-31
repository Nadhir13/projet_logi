QT += core gui widgets sql printsupport charts

CONFIG += c++17

TEMPLATE = app
TARGET = projet_logi

SOURCES += \
    main.cpp \
    db.cpp \
    logindialog.cpp \
    mainwindow.cpp \
    client.cpp \
    clientdao.cpp \
    clientcontroller.cpp \
    order.cpp \
    orderdao.cpp \
    ordercontroller.cpp \
    user.cpp \
    userdao.cpp \
    usercontroller.cpp

HEADERS += \
    db.h \
    logindialog.h \
    mainwindow.h \
    client.h \
    clientdao.h \
    clientcontroller.h \
    order.h \
    orderdao.h \
    ordercontroller.h \
    user.h \
    userdao.h \
    usercontroller.h

FORMS += \
    logindialog.ui \
    mainwindow.ui

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
    README.md \
    resources/icons/add-user.png \
    resources/icons/add.png \
    resources/icons/app_icon.png \
    resources/icons/cancel.png \
    resources/icons/category.png \
    resources/icons/check.svg \
    resources/icons/chevron-down.svg \
    resources/icons/chevron-up.svg \
    resources/icons/clients.png \
    resources/icons/database-connected.png \
    resources/icons/delete.png \
    resources/icons/edit.png \
    resources/icons/error.png \
    resources/icons/excel.png \
    resources/icons/info.png \
    resources/icons/lock.svg \
    resources/icons/logo.png \
    resources/icons/logo_white.png \
    resources/icons/orders.png \
    resources/icons/password.png \
    resources/icons/pdf.png \
    resources/icons/priority.png \
    resources/icons/refresh.png \
    resources/icons/save.png \
    resources/icons/settings.png \
    resources/icons/stats.png \
    resources/icons/success.png \
    resources/icons/user-plus.png \
    resources/icons/user-plus.svg \
    resources/icons/user.svg \
    resources/icons/users.png \
    resources/icons/warning.png

RESOURCES += \
    resources/resources.qrc
