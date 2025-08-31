#include <QApplication>
#include "mainwindow.h"
#include "db.h"
#include "logindialog.h"
#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Set application style for better look
    a.setStyle("Fusion");

    // Connect to database
    if (!Db::instance().open("localhost", 1521, "XE", "system", "admin")) {
        QMessageBox::critical(nullptr, "Erreur de base de données",
                              "Impossible de se connecter à la base de données:\n" + Db::instance().lastError());
        return 1;
    }

    // Application loop
    while (true) {
        // Show login dialog
        LoginDialog loginDialog;

        if (loginDialog.exec() != QDialog::Accepted) {
            break; // Exit application if login cancelled
        }

        // Create and show main window with user info
        MainWindow w(loginDialog.getUserId(), loginDialog.getUsername(), loginDialog.getRole());
        w.show();

        // Start event loop for main window
        a.exec();

        // When main window closes, we'll show login dialog again
        // unless the application is exiting
    }

    return 0;
}
