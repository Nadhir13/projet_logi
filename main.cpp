#include <QApplication>
#include "mainwindow.h"
#include "db.h"
#include "logindialog.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Connect to database
    if (!Db::instance().open("localhost", 1521, "XE", "system", "admin")) {
        qFatal("DB open failed: %s", qPrintable(Db::instance().lastError()));
        return 1;
    }

    // Show login dialog (image is loaded automatically in constructor)
    LoginDialog loginDialog;

    if (loginDialog.exec() != QDialog::Accepted) {
        return 0; // Exit if login cancelled or failed
    }

    // Create and show main window with user info
    MainWindow w(loginDialog.getUserId(), loginDialog.getUsername(), loginDialog.getRole());
    w.show();

    return a.exec();
}
