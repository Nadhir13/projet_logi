#include <QApplication>
#include "mainwindow.h"
#include "db.h"

    int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Connect once for the whole app
    if (!Db::instance().open("localhost", 1521, "XE", "system", "admin")) {
        qFatal("DB open failed: %s", qPrintable(Db::instance().lastError()));
    }

    MainWindow w;
    w.show();
    return a.exec();
}

